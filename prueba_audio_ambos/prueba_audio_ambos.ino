#include "mic.h"
mic mic_g;
mic mic_b;
int MicPin_g = A1;
int MicPin_b = A0;
boolean check = false;

void setup() 
{
   Serial.begin(9600);
}

void loop() 
{
   mic_g.microfono(A1);
   mic_b.microfono(A0);
   Serial.print(mic_g.getVolts()); Serial.print("\t"); Serial.println(mic_b.getVolts());

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

   Serial.print("Estado niña: ");  Serial.print(mic_g.getState()); Serial.print("\t"); Serial.print("Estado niño: "); Serial.println(mic_b.getState());

     
    Serial.println("----------------------------------");    
}
