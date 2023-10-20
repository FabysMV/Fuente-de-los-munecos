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
#include "secuencia.h"
//hacemos el objeto de las acciones de los niños
accion nenes;
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

void setup() {
  Serial.begin(9600);
  //inicializar audio
 
  //entradas--botones
  pinMode(b_Up, INPUT);
  pinMode(b_Sleep, INPUT);
  nenes.neutro();
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
    do{ //vemos que no se haya dado la indicación de que despierten
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
    //Serial.println("despierto!!");// Procedemos a revisar el estado el micrófono
    
    //Serial.println("revisando micrófonos...");// /------------
    mic_g.microfono(A1);
    mic_b.microfono(A0);
   // Serial.print(mic_g.getVolts()); Serial.print("\t"); Serial.println(mic_b.getVolts());

    //se ha detectado un sonido


   if(mic_g.getVolts() >= 3.0 || mic_b.getVolts() >= 3.0){
   // Serial.println("detectado");

    check = true;
    
    mic_g.SetCheck();
    mic_b.SetCheck(); //set check = true
    

    do{
      //Serial.println("MUESTRA");
      //vamos a tomar la muestra de ambos micrófonos
      if (mic_g.getCheck() == true){mic_g.microfono(A1); /*Serial.print("Volts_g: ");  Serial.println(mic_g.getVolts());*/
                                    mic_g.evaluar();} //lo hará mientras no haya terminado de contar

                                   /* Serial.println("***********************"); 
                                    Serial.println("***********************"); */
      if (mic_b.getCheck() == true){mic_b.microfono(A0); /*Serial.print("Volts_b: ");  Serial.println(mic_b.getVolts());*/
                                    mic_b.evaluar();}//lo hará mientras no haya terminado de contar
         
        //si uno termina de escuchar y su timer se desborda, ya no tomaremos la muestra, eso se logra con una variable booleana
        if(mic_g.getCheck() == false && mic_b.getCheck() == false){check = false;}  //si AMBOS terminan de muestrear, entonces check cambia a estado FALSO
       
      }while(check == true); //si check cambia a falso, salimos del ciclo

      
      // evaluación de lo escuchado
     mic_g.SetState();
     mic_b.SetState();
   }
   else{mic_g.none(); mic_b.none();}

  // Serial.print("Estado niña: ");  Serial.print(mic_g.getState()); Serial.print("\t"); Serial.print("Estado niño: "); Serial.println(mic_b.getState());

     
   // Serial.println("----------------------------------"); 

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
            // Serial.print("**********"); /*Serial.print(delta_sec);*/ Serial.println("**********");
            ////// NADA ////////////////////////////
            }//end if ruido nena
          else if(mic_g.getState() == 's') // le hablan bajo EXCLUSIVAMENTE a la nena
          { flag = false; delta_sec = 0;
            nenes.g_bajo();}//end if bajo a nena
          else if(mic_g.getState() == 'a')
          { flag = false; delta_sec = 0;
            nenes.g_alto();}//end if alto a nena  
      }//end if ruido a nene-----------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
     else if(mic_g.getState() == 'n') //el microfono de la nena tiene ruido?
    {//---------------------------------------------------------------------------------- 
          if(mic_b.getState() == 's') // le hablan bajo EXCLUSIVAMENTE a nene
          { flag = false; delta_sec = 0;
            nenes.b_bajo();}//end if bajo a nene
          else if(mic_b.getState() == 'a') // le hablan alto EXCLUSIVAMENTE a nene 
          {   flag = false; delta_sec = 0;
              nenes.b_alto();}//end if alto a nene
      }//end if ruido a nena-------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
///      CUANDO NO HAY RUIDO --> LE HABLAN A LOS DOS    ///
      //¿a la nena le hablan alto?
      else if(mic_g.getState() == 'a')
      {   flag = false; delta_sec = 0;
          if(mic_b.getState() == 'a')
          {//acciones AMBOS alto
            nenes.ambos_alto();}//le hablan alto al nene?
          else if(mic_b.getState() == 's')
          {nenes.ambos_g();//le hablan más alto a la nena, el se quiere incluir
            } // le hablan bajo al nene? 
        }//end if nena alta 
        //¿a nena le hablan bajo?
      else if(mic_g.getState() == 's')
      { flag = false; delta_sec = 0;
        if(mic_b.getState() == 'a')
          { nenes.ambos_b();}//le hablan alto al nene?  
        else if(mic_b.getState() == 's')
          {nenes.ambos_bajo();} // le hablan bajo al nene?
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
          switch(s){case 0: nenes.baile(); flag = false;
                            delta_sec = 0; break;
                      case 1: nenes.risa(); flag = false;  
                              delta_sec = 0; break; 
                      case 2: nenes.canto();  flag = false; 
                              delta_sec = 0; break;}//end switch s
            
          s = nenes.getS();
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


}//end loop
