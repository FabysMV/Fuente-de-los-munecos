//Documento que efectúa el control de todo el sistema
//Aquí se reciben la señales de los micrófonos, se da la orden de movimiento y se indica qué canción reproducir de la SD

//******CONFIGURACIÓN Y CALIBRACIÓN DEL MICRÓFONO**********************
//PINES que indican los pines de entrada ANALÓGICOS del micrófono
//cambiar al numero de pin de A0---pin nene
//                            A1---pin nena
// Micrófonos
#include "mic.h"
mic mic_g;
mic mic_b;
int MicPin_g = A1;
int MicPin_b = A0;
boolean check = false;
//////////////////////////////////////////////////////////////////////
//Variables de pines de botones y ESTADOS
int b_Up;
int b_Sleep;
// estados  //
boolean Sleep = false;
boolean Up = false;

// Pines de los LED ///////////////////////////////////////////////////
int Led_g = 1;
int Led_b = 2;
///////////////////////////////////////////////////////////////////////
//#include "secuencia.h"
//hacemos el objeto de las acciones de los niños
//accion nenes;
// Variables para controlar las acciones, pra que no se haga un ciclo
int s = 0; //secuencia que se va a realizar
//int last_s = 10; //ultima secuencia realizada
//boolean flag_s = false;
//unsigned long tiempo = 0;
//unsigned long tiempo_prev = 0;
//unsigned long cont_s = 0;
///////////////////////////////////////////////////////////////////////
// Variables y cositas para el contador que iniciará la secuencia automática
boolean flag = false;
unsigned long t_Sec = 0;
unsigned long last_ts = 0;
unsigned long delta_sec = 0;
int in = 0; //para las veces que ha entrado en un ruido && ruido

//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

/*ELEMENTOS CLASE SECUENCIA*/
//////////////////////////////////////////////////////////////////////////
//va a dar la orden del movimiento de las cabezas dependiendo de lo que se haya escuchado en el microfono
//necesitamos la clase de la SD para poder rerpoducir todo
//******** CONFIGURACIÓN PARA SD Y AUDIO  *************//
//La tarjeta SD debe de estar formateada en FAT32
#include <SD.h>                //Se inclye la libreria SD
#include <SPI.h>               //Se incluye la libreria para la comunicacion SPI
#include <TMRpcm.h>            //Se incluye la libreria para reproducir .WAV

#define SD_ChipSelectPin 53  // Selecciona la tarjeta SD. Puede ser cualquier pin que NO se esté utilizando ya. 

TMRpcm Audio;   // Se crea un objeto para usar las funciones de la libreria TMRpcm
//****************************************************************************************
/*  C O N E X I O N E S   S P I 

Arduino MEGA ---------> SD Card
50-------------------> MISO
51-------------------->MOSI
52 -------------------->SCK
53---------------------->CS
11---------------------->Speaker
GND ------------------>GND
5V ------------------> VCC */
//Declaración de los motores
#include "motor_mov.h"
motor_mov girl;
motor_mov boy;
int rapidez = 200; //rapidez con la que hace la negación en milisegundos
//PINES DE LOS MOTORES
int m_g = 12;
int m_b = 13;

int n_g = 45;
int n_b = 90;
int S = 0;
///////////////////////////////////////////////////////////////////////

/*FIN ELEMENTOS CLASE SECUENCIA*/

void setup() {
  Serial.begin(9600);
  //INICIALIZAR LAS FUNCIONES DE LA CLASE SECUENCIA
   
  delay(500);
  //inicializar audio
  //  
  //entradas--botones
  pinMode(b_Up, INPUT);
  pinMode(b_Sleep, INPUT);
  //salidas--LED
  pinMode(Led_g, OUTPUT);
  pinMode(Led_b, OUTPUT);
  /////////////////////////////
//parameter value of 1000 is fully counter-clockwise, 2000 is fully clockwise, and 1500 is in the middle.
//-----------------Revisión del movimiento de los motores------------
  /////INIT_AUDIO//////
  Audio.speakerPin = 11; //Selecciona la salida de audio: pin 9 Arduino UNO
      Audio.quality(1); // Mejoramos la calidad de sonido (puede ser 0 o 1)
      Audio.setVolume(5); // Se selecciona el volumen: valor entre 0 y 7. Solo funciona bien si la calidad del audio está a 1. 
                          //En caso de que no se oiga nada o se  oiga mal, bajar volumen o borrar la función
      
      if (!SD.begin(SD_ChipSelectPin)) {  // Comprueba si la tarjeta SD se ha inicializado correctamente
          Serial.println("Fallo de la tarjeta SD");  
          return;   // Si la tarjeta SD falla, el programa termina
        }
        else{
          Serial.println("SD inicializada correctamente!");
            }
//--------------------------------------------------------------------  
}

void loop() {

 /* 
  if(digitalRead(Up) == HIGH)//si se presionó el botón, despertarán los muñecos
  {
    Up = true;
    }
 
  if(digitalRead(Sleep) == HIGH && digitalRead(Up)== LOW)//si se presionó el botón de dormir
  { delta_sec = 0;
    Up = false;
    Serial.println("mimido");
       //vemos que no se haya dado la indicación de que despierten
        if(digitalRead(Up) == HIGH)
        {Up = true; Serial.println("despertando...");
        delay(100);}//si es así, cambiamos el estado de Up a activo
      }while(Up == false); //cuando Up esté activo, salimos del ciclo
    }*/

    //estado para pruebas
    Up = true;
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(Up == true) //se ha apretado el botón que despierta a los niños
  {
    Serial.println("despierto!!");// Procedemos a revisar el estado el micrófono
    
    Serial.println("revisando micrófonos...");// /------------
    mic_g.microfono(A1);
    mic_b.microfono(A0);
    Serial.print(mic_g.getVolts()); Serial.print("\t"); Serial.println(mic_b.getVolts());

    //se ha detectado un sonido


   if(mic_g.getVolts() >= 3.0 || mic_b.getVolts() >= 3.0){
    Serial.println("detectado");

    check = true;
    
    mic_g.SetCheck();
    mic_b.SetCheck(); //set check = true
    

      do{
      Serial.println("MUESTRA");
      //vamos a tomar la muestra de ambos micrófonos
      if (mic_g.getCheck() == true){mic_g.microfono(A1); Serial.print("Volts_g: ");  Serial.println(mic_g.getVolts());
                                    mic_g.evaluar();} //lo hará mientras no haya terminado de contar

                                    Serial.println("***********************"); 
                                    Serial.println("***********************"); 
      if (mic_b.getCheck() == true){mic_b.microfono(A0); Serial.print("Volts_b: ");  Serial.println(mic_b.getVolts());
                                    mic_b.evaluar();}//lo hará mientras no haya terminado de contar
         
        //si uno termina de escuchar y su timer se desborda, ya no tomaremos la muestra, eso se logra con una variable booleana
        if(mic_g.getCheck() == false && mic_b.getCheck() == false){check = false;}  //si AMBOS terminan de muestrear, entonces check cambia a estado FALSO
       
      }while(check == true); //si check cambia a falso, salimos del ciclo

      
      // evaluación de lo escuchado
     mic_g.SetState();
     mic_b.SetState();
   }
   else{mic_g.none(); mic_b.none();}

   Serial.print("Estado niña: ");  Serial.print(mic_g.getState()); Serial.print("\t"); Serial.print("Estado niño: "); Serial.println(mic_b.getState());

     
    Serial.println("----------------------------------"); 

  //---- ASIGNACIÓN DE ACCIÓN POR ESTADOS ----  
    if(mic_b.getState() == 'n') //el microfono del nene tiene ruido?
    {//---------------------------------------------------------------------------------- 
          if(mic_g.getState() == 'n') //tiene ruido la nena?
          {//// COMIENZO O SIGO EL CONTEO//////////
            last_ts = t_Sec;
            t_Sec = millis();
            
            delta_sec = delta_sec + (t_Sec - last_ts);
            in ++;
            if(delta_sec >= 60000){flag = true;
                                   delta_sec = 0;}
             Serial.print("**********"); Serial.print(delta_sec); Serial.println("**********");
            ////// NADA ////////////////////////////
            }//end if ruido nena
          else if(mic_g.getState() == 's') // le hablan bajo EXCLUSIVAMENTE a la nena
          { flag = false;
            g_bajo();
            }//end if bajo a nena
          else if(mic_g.getState() == 'a')
          { flag = false;
             
            g_alto();}//end if alto a nena  
      }//end if ruido a nene-----------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
     else if(mic_g.getState() == 'n') //el microfono de la nena tiene ruido?
    {//---------------------------------------------------------------------------------- 
          if(mic_b.getState() == 's') // le hablan bajo EXCLUSIVAMENTE a nene
          { flag = false;
             b_bajo();}//end if bajo a nene
          else if(mic_b.getState() == 'a') // le hablan alto EXCLUSIVAMENTE a nene 
          {   flag = false;
               b_alto();}//end if alto a nene
      }//end if ruido a nena-------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
///      CUANDO NO HAY RUIDO --> LE HABLAN A LOS DOS    ///
      //¿a la nena le hablan alto?
      else if(mic_g.getState() == 'a')
      {   flag = false;
          if(mic_b.getState() == 'a')
          {//acciones AMBOS alto
             ambos_alto();}//le hablan alto al nene?
          else if(mic_b.getState() == 's')
          { ambos_g();//le hablan más alto a la nena, el se quiere incluir
            } // le hablan bajo al nene? 
        }//end if nena alta 
        //¿a nena le hablan bajo?
      else if(mic_g.getState() == 's')
      { flag = false;
        if(mic_b.getState() == 'a')
          {  ambos_b();}//le hablan alto al nene?  
        else if(mic_b.getState() == 's')
          { ambos_bajo();} // le hablan bajo al nene?
       }//end if hablan bajo a nena
       
//////////////////////////////////////////////////////////////////////////////////////////
//------------ ya pasó el tiempo necesario para empezar las secuencias??-----------------
//veamos: lo sabremos con una flag que activará siempre esto
      if(flag == true)
      {
          //cálculos para el timer
         /* tiempo_prev = tiempo;
          tiempo = millis();
          cont_s = cont_s + tiempo - tiempo_prev; //incrementa el conteo en delta */
          switch(s){case 0:  baile(); flag = false;
                              Serial.println("acabe"); break;
                      case 1:  risa(); flag = false; break;
                      case 2:  canto();  flag = false; break;}//end switch s
            
          s = getS();
         /* if(cont_s >= 30000)//el límite debe de ser la duración del audio + 30 segundos
          {//ahora se cambia la secuencia
            Serial.println("cambio de secuencia");
            s = random(0,2);//elegir una secuencia 1.-baile  2.-lamento  3.-canto 
            Serial.println(s);
            cont_s = 0;}
          last_s = s;*/
       }//end if flag true --> que el contador ya llegó al limite
 /////////////////////////////////////////////////////////////////////////////////////////
    }// en up==true

   else{}


} //end loop

/*FUNCIONES DE LA CLASE SECUENCIA*/

  int getS(){return S;}
  
  void baile()
  {
     
    Audio.play("canto1.wav");  
      delay(50);
      Serial.println("baile"); 
         /* girl.secuencia2(m_g); 
          boy.secuencia(m_b);*/
          boy.no(m_b);
          delay(15);
          girl.no(m_g);
          delay(15);
    Serial.println("baile");
    S = 1;
    delay(1000);
    return 0;
    }


  void risa()
  {
     
    Audio.play("risa.wav");  
      delay(50);
      Serial.println("RISA"); 
         /* girl.secuencia2(m_g); 
          boy.secuencia(m_b);*/
          boy.izq(m_b);
          delay(15);
          girl.no(m_g);
          delay(500);
          boy.derecha(m_b);
    Serial.println("lamento");
    S = 2;
    delay(1000);
    return 0;
    }


  void canto()
  {
   Audio.play("canto2.wav");  
      delay(50);
        Serial.println("CANTO"); 
         /* girl.secuencia2(m_g); 
          boy.secuencia(m_b);*/
          boy.no(m_b);
          delay(15);
          girl.no(m_g);
          delay(15);
          
    Serial.println("canto");
    S = 0;
    delay(1000);
    return 0;
    }


   /// secuencia para cuando hay señal ///
  void g_alto()
  {
      Serial.println("Niña alto");
      delay(2000);
      girl.izq(m_g); //gira a la izquierda
      boy.neutro(n_b, m_b);
      //***************
     // Audio.play("Susurros.wav"); //!!importante llamar así el audio
     //***********************************
     Audio.play("sussuro.wav"); 
     delay(50);
        Serial.println("susurros"); 
      girl.neutro(n_g, m_g);
      delay(15);
      boy.derecha(m_b); //voltea a ver a su hermana
      delay(1000);  //espera 1 segundo
      //podemos tener otros posibles, por mientras solo 1
     //*******************************
     // Audio.play("Por_ella1.wav");
     //************************************
     Audio.play("audio1.wav"); 
        Serial.println("audio1");  
         boy.speak(m_b);  //secuencia solo mientras habla
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);
      delay(1000);
    return 0;
    }///Niña se voltea y le habla a su hermano, él responde por ella


  void g_bajo()
  {
      Serial.println("Niña bajo");
      delay(2000);
      girl.derecha(m_g);
      delay(500);
      boy.derecha(m_b);
      delay(15);
      //**************************
     // Audio.play("Yo_igual.wav");
     //*************************************
     Audio.play("audio2.wav"); 
     delay(50);
        Serial.println("a2");  
          
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);
      delay(1000);
    return 0;
    } // El hermano se intriga por lo que andan susurrando

    
  void b_alto()
  {
      int aleatorio;
      Serial.println("Niño alto");
      delay(2000);
      girl.derecha(m_g);
      boy.derecha(m_b);
      //***************************
      //Audio.play("funfact1.wav"); 
       //******************
      Audio.play("audio3.wav");
      delay(50);
        Serial.println("a3"); 
          girl.izq(m_g); 
          delay(15);
          boy.speak(m_b);
          delay(15);
         // boy.secuencia(m_b);
          
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);
      delay(15);
      delay(1000);
    return 0;
    } //El hermano da algún dato curioso sobre ellos

    
  void b_bajo()
  {
      Serial.println("Niño bajo");
      delay(2000);
      boy.derecha(m_b);
      delay(1000);
      boy.izq(m_b);
      delay(15);
      //************************
      //Audio.play("ella_no_oye.wav");
      //*************************
      Audio.play("audio4.wav"); 
      delay(50);
        Serial.println("a4"); 
            boy.speak(m_b);
            
       boy.neutro(n_b, m_b);//regresa a posición inicial
       delay(15);
       girl.neutro(n_g, m_g);
       delay(15);
       delay(1000);
    return 0;
    } //Voltea a ver a su hermana y piden que hablen más fuerte que ella no escuchó


  void ambos_alto()
  {
      Serial.println("Ambos alto");
      delay(2000);
      girl.derecha(m_g);
      boy.izq(m_b);
      delay(500);
      girl.izq(m_g);
      boy.derecha(m_b);
      delay(1000);
      boy.neutro(n_b, m_b);//regresa a posición inicial
      girl.neutro(n_g, m_g);
      //***************************
      //Audio.play("felices.wav");
      //*******************************
      Audio.play("audio5.wav"); 
      delay(50);
        Serial.println("a5"); boy.speak(m_b); delay(15); 
      delay(1000);
    return 0;
    } //Felices, dicen algún dato curioso

  void ambos_g()
  {
     
      Serial.println("Ambos, pero niña más alto");
      delay(2000);
      boy.derecha(m_b);
      delay(500);
      girl.izq(m_g);
      delay(500);
      //**********************************
      //Audio.play("no_oigo.wav");
      //************************************
      Audio.play("audio6.wav"); 
      delay(50);
        Serial.println("a6"); 
              boy.no(m_b);
              delay(15);
              
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
        girl.neutro(n_g, m_g);
        delay(1000);
    return 0;
    } //Voltea a ver a su izquierda, después a su hermana y se queja de que no escuchó bien
    
    
  void ambos_b()
  {
     
      int aleatorio;
      Serial.println("Ambos, pero niño más alto");
      delay(2000);
//      /---
      boy.derecha(m_b);
      delay(1000);
      boy.izq(m_b);
      delay(15);
      girl.izq(m_g);
      delay(15);
      //************************************
     /*aleatorio = random(1,3);
      switch(aleatorio)
      { case 1: Audio.play("funfact1.wav"); break;
        case 2: Audio.play("funfact2.wav"); break;
        case 3: Audio.play("funfact3.wav"); break;}*/
     //*************************
     Audio.play("audio7.wav"); 
      delay(50);
        Serial.println("a7"); 
         /* girl.secuencia2(m_g); 
          boy.secuencia(m_b);*/
          boy.speak(m_b);
          delay(800);
          boy.speak(m_b);
          delay(500);
          
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);
      delay(15);
      delay(1000);
    return 0;
     } //Voltea a ver a su hermana, después voltea a ver a quien le habló y le dice un dato curioso.

    
  void ambos_bajo()
  {
     
    Serial.println("Ambos bajo");
    delay(2000);

    boy.derecha(m_b);
    delay(15);
    girl.izq(m_g);
    delay(1500);
    //***********************************
    //Audio.play("susurro_feliz.wav");
    //****************************************
    Audio.play("audio8.wav"); 
    delay(50);
      Serial.println("a8"); 
          
          
     boy.neutro(n_b, m_b);//regresa a posición inicial
     delay(15);
     girl.neutro(n_g, m_g);
     delay(15);
     delay(1000);
    return 0;
    } //Los dos hermanos se voltean a ver, y dicen que están felices

/*FIN FUNCIONES DE LA CLASE SECUENCIA*/
