//va a dar la orden del movimiento de las cabezas dependiendo de lo que se haya escuchado en el microfono
//necesitamos la clase de la SD para poder rerpoducir todo
//******** CONFIGURACIÓN PARA SD Y AUDIO  *************//
//La tarjeta SD debe de estar formateada en FAT32
#include <SD.h>                //Se inclye la libreria SD
#include <SPI.h>               //Se incluye la libreria para la comunicacion SPI
#include <TMRpcm.h>            //Se incluye la libreria para reproducir .WAV

#define SD_ChipSelectPin 4  // Selecciona la tarjeta SD. Puede ser cualquier pin que NO se esté utilizando ya. 

TMRpcm Audio;   // Se crea un objeto para usar las funciones de la libreria TMRpcm
//****************************************************************************************
/*  C O N E X I O N E S   S P I 

Arduino Nano/Arduino UNO
12 -------------------> MISO
11 -------------------->MOSI
13 -------------------->SCK
4 ---------------------->CS
9 ---------------------->Speaker
GND ------------------>GND
5V ------------------> VCC*/
//Declaración de los motores
#include "motor_mov.h"
motor_mov girl;
motor_mov boy;
int rapidez = 200; //rapidez con la que hace la negación en milisegundos
//PINES DE LOS MOTORES
int m_g = 12;
int m_b = 13;
///////////////////////////////////////////////////////////////////////
class accion{
  
  private:
      //posiciones iniciales de los niños
      //:: NOTA--> la niña está girada ligeramente hacia su hermano
      int n_g = 45;
      int n_b = 90;
      int S = 0;
  public:

  void init_audio(){
      Audio.speakerPin = 9; //Selecciona la salida de audio: pin 9 Arduino UNO
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
    }//end init_audio

  /// secuencia para cuando no hay señal de microfono por 1 minuto ///

  int getS(){return S;}
  
  void baile()
  {
    Audio.play("canto1.wav");  
      
      do{Serial.println("baile"); 
         /* girl.secuencia2(m_g); 
          boy.secuencia(m_b);*/
          boy.no(m_b);
          delay(15);
          girl.no(m_g);
          delay(15);
         }while(Audio.isPlaying()==1);
    Serial.println("baile");
    S = 1;
    }


  void risa()
  {
    Audio.play("risa.wav");  
      
      do{Serial.println("RISA"); 
         /* girl.secuencia2(m_g); 
          boy.secuencia(m_b);*/
          boy.izq(m_b);
          delay(15);
          girl.no(m_g);
          delay(500);
          boy.derecha(m_b);
         }while(Audio.isPlaying()==1);
    Serial.println("lamento");
    S = 2;
    }


  void canto()
  {
   Audio.play("canto2.wav");  
      
      do{Serial.println("CANTO"); 
         /* girl.secuencia2(m_g); 
          boy.secuencia(m_b);*/
          boy.no(m_b);
          delay(15);
          girl.no(m_g);
          delay(15);
         }while(Audio.isPlaying()==1);
    Serial.println("canto");
    S = 0;
    
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
      do{Serial.println("susurros");}while(Audio.isPlaying()==1);
      girl.neutro(n_g, m_g);
      delay(15);
      boy.derecha(m_b); //voltea a ver a su hermana
      delay(1000);  //espera 1 segundo
      //podemos tener otros posibles, por mientras solo 1
     //*******************************
     // Audio.play("Por_ella1.wav");
     //************************************
     Audio.play("audio1.wav"); 
      do{Serial.println("audio1");  
         boy.speak(m_b);}while(Audio.isPlaying()==1); //secuencia solo mientras habla
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);
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
      do{Serial.println("a2");  
         }while(Audio.isPlaying()==1);
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);
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
      do{Serial.println("funfact"); 
          girl.izq(m_g); 
          delay(15);
          boy.speak(m_b);
          delay(15);
         // boy.secuencia(m_b);
         }while(Audio.isPlaying()==1);
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);
      delay(15);
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
      do{Serial.println("a4"); 
            boy.speak(m_b);
           }while(Audio.isPlaying()==1);
       boy.neutro(n_b, m_b);//regresa a posición inicial
       delay(15);
       girl.neutro(n_g, m_g);
       delay(15);
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
      do{Serial.println("a5"); boy.speak(m_b); delay(15);}while(Audio.isPlaying()==1);
      
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
      do{Serial.println("a6"); 
              boy.no(m_b);
              delay(15);
             }while(Audio.isPlaying()==1);
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
        girl.neutro(n_g, m_g);
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
      
      do{Serial.println("a7"); 
         /* girl.secuencia2(m_g); 
          boy.secuencia(m_b);*/
          boy.speak(m_b);
          delay(800);
          boy.speak(m_b);
          delay(500);
         }while(Audio.isPlaying()==1);
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);
      delay(15);
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
    do{Serial.println("a8"); 
          
         }while(Audio.isPlaying()==1);
     boy.neutro(n_b, m_b);//regresa a posición inicial
     delay(15);
     girl.neutro(n_g, m_g);
     delay(15);
    } //Los dos hermanos se voltean a ver, y dicen que están felices

  };
