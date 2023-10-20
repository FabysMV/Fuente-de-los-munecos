//La tarjeta SD debe de estar formateada en FAT32
#include <SD.h>                      // Se inclye la libreria SD
#include <SPI.h>              // Se incluye la libreria para la comunicacion SPI
#include <TMRpcm.h>           //  Se incluye la libreria para reproducir .WAV

#define SD_ChipSelectPin 53  // Selecciona la tarjeta SD. Puede ser cualquier pin que NO se esté utilizando ya. 

TMRpcm Audio;   // Se crea un objeto para usar las funciones de la libreria TMRpcm

bool boton_A = 0; //Variable que guarda el estado del pulsador de cambiar de cancion
bool boton_B = 0; //Variable que guarda el estado del pulsador de pausar
int song = 1; //Se inician en 0 para que cuando se incremente la cancion al principio se reproduzca la cancion 1
int last_song = 0; //Almacena el número de la ultima cancion

/*  C O N E X I O N E S   S P I 

Arduino Nano/Arduino UNO
12 -------------------> MISO
11 -------------------->MOSI
13 -------------------->SCK
4 ---------------------->CS
9 ---------------------->Speaker
GND ------------------>GND
5V ------------------> VCC

Arduino MEGA ---------> SD Card
50-------------------> MISO
51-------------------->MOSI
52 -------------------->SCK
53---------------------->CS
11---------------------->Speaker
GND ------------------>GND
5V ------------------> VCC
 */



void setup(){

  Audio.speakerPin = 11; //Selecciona la salida de audio: pin 9 Arduino UNO
  Audio.quality(1); // Mejoramos la calidad de sonido (puede ser 0 o 1)
  Audio.setVolume(5); // Se selecciona el volumen: valor entre 0 y 7. Solo funciona bien si la calidad del audio está a 1. 
                      //En caso de que no se oiga nada o se  oiga mal, bajar volumen o borrar la función
  
  pinMode(3,INPUT); // Declara el boton de pasar de cancion como entrada
  pinMode(2,INPUT); // Declara el boton de pausar la cancion

  Serial.begin(9600); //Se inicializa el puerto serie
  Serial.println("Inicializando");
  
  if (!SD.begin(SD_ChipSelectPin)) {  // Comprueba si la tarjeta SD se ha inicializado correctamente
    Serial.println("Fallo de la tarjeta SD");  
    return;   // Si la tarjeta SD falla, el programa termina
  }
  else{
    Serial.println("SD inicializada correctamente!");
      }

}

void loop(){  
  Serial.println(Audio.isPlaying());
  boton_A = digitalRead(3); //Se lee el boton de pasar de cancion
  boton_B = digitalRead(2); //Se lee el boton de pausa

    if(boton_A == 1){ // Si pulsas el pulsador se incrementa la cancion a reproducir
      if(song <= 2)
          song++; // Se incrementa la cancion a reproducir
      else
          song = 1; // Si se ha llegado a la ultima cancion, vuelve a la cancion numero 1
      while(boton_A == 1){   boton_A = digitalRead(3); } //Espera a que levantes el dedo del pulsador para continuar
    }

    if(boton_B == 1){
        Audio.pause(); //Pausa la cancion que está sonando
        Serial.println("Cancion pausada o renaudada");
        while(boton_B == 1){   boton_B = digitalRead(2); } //Espera a que levantes el dedo del pulsador para continuar
      }


if(song != last_song){ //Reproduce el audio una unica vez siempre que se haya cambiado de cancion

   switch(song)
   {
      case 1: Audio.play("audio3.wav"); Serial.println("No te acerques"); break;
      case 2: Audio.play("audio2.wav"); Serial.println("barrio de Xonaca"); break;
      case 3: Audio.play("audio3.wav"); Serial.println("Morimos yendo a la escuela"); break;
   }

last_song = song;
}
     
  // NOTA: si llamamos a la función Audio. play() todo el rato nunca oiremos la canción ya que se resetea y estará todo el tiempo
  //en el minuto 0:00. Hay que llamarla una única vez, por ello tenemos la condición if que solo se ejecuta una única 
  //vez si la canción ha cambiado. 

    
 

}