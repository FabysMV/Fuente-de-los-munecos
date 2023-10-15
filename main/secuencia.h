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

//Declaración de los motores
#include "motor_mov.h"
motor_mov girl;
motor_mov boy;

///////////////////////////////////////////////////////////////////////
class accion{
  
  private:
      //posiciones iniciales de los niños
      //:: NOTA--> la niña está girada ligeramente hacia su hermano
      int n_g = 0;
      int n_b = 0;
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

  void baile()
  {
    Serial.println("baile");
    }


  void lamento()
  {
    Serial.println("lamento");
    }


  void canto()
  {
    Serial.println("canto");
    
    }


   /// secuencia para cuando hay señal ///
  void g_alto()
  {
      Serial.println("Niña alto");
      delay(2000);
      girl.izq(); //gira a la izquierda
      boy.neutro(n_b);
      Audio.play("Susurros.wav"); //!!importante llamar así el audio
      do{Serial.println("susurros");}while(Audio.isPlaying()==1);
      girl.neutro(n_g);
      boy.derecha(); //voltea a ver a su hermana
      delay(1000);  //espera 1 segundo
      //podemos tener otros posibles, por mientras solo 1
      Audio.play("Por_ella1.wav");
      do{Serial.println("Por ella");  
         boy.speak();}while(Audio.isPlaying()==1); //secuencia solo mientras habla
      boy.neutro(n_b);//regresa a posición inicial
      girl.neutro(n_g);
    }///Niña se voltea y le habla a su hermano, él responde por ella


  void g_bajo()
  {
      Serial.println("Niña bajo");
      delay(2000);
      girl.derecha();
      delay(500);
      boy.derecha();
      Audio.play("Yo_igual.wav");
      do{Serial.println("Yo igual");  
         }while(Audio.isPlaying()==1);
      boy.neutro(n_b);//regresa a posición inicial
      girl.neutro(n_g);
    } // El hermano se intriga por lo que andan susurrando

    
  void b_alto()
  {
      int aleatorio;
      Serial.println("Niño alto");
      delay(2000);
      girl.derecha();
      boy.derecha();

      aleatorio = random(1,3);
      switch(aleatorio)
      { case 1: Audio.play("funfact1.wav"); break;
        case 2: Audio.play("funfact2.wav"); break;
        case 3: Audio.play("funfact3.wav"); break;}
      
      do{Serial.println("funfact"); 
          girl.izq(); 
          boy.secuencia();
         }while(Audio.isPlaying()==1);
      boy.neutro(n_b);//regresa a posición inicial
      girl.neutro(n_g);
      
    } //El hermano da algún dato curioso sobre ellos

    
  void b_bajo()
  {
      Serial.println("Niño bajo");
      delay(2000);
      boy.derecha();
      delay(1000);
      boy.izq();
      Audio.play("ella_no_oye.wav");
      do{Serial.println("ella no escuchó"); 
            
           }while(Audio.isPlaying()==1);
       boy.neutro(n_b);//regresa a posición inicial
       girl.neutro(n_g);
    } //Voltea a ver a su hermana y piden que hablen más fuerte que ella no escuchó


  void ambos_alto()
  {
      Serial.println("Ambos alto");
      girl.derecha();
      boy.izq();
      delay(500);
      girl.izq();
      boy.derecha();
      delay(1000);
      boy.neutro(n_b);//regresa a posición inicial
      girl.neutro(n_g);
      Audio.play("felices.wav");
      do{Serial.println("estamos felices"); 
            
           }while(Audio.isPlaying()==1);
      delay(2000);
    } //Felices, dicen algún dato curioso

  void ambos_g()
  {
    Serial.println("Ambos, pero niña más alto");
    delay(2000);
    } //Voltea a ver a su izquierda, después a su hermana y se queja de que no escuchó bien

    
  void ambos_b()
  {
    Serial.println("Ambos, pero niño más alto");
    delay(2000);
    } //Voltea a ver a su hermana, después voltea a ver a quien le habló y le dice un dato curioso.

    
  void ambos_bajo()
  {
    Serial.println("Ambos bajo");
    delay(2000);
    } //Los dos hermanos se voltean a ver, y dicen que están felices

  };
