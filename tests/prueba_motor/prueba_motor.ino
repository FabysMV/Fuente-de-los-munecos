#include "motor_mov.h"

motor_mov motor;
int Pin = 9;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
 motor.SetUp(9);
}

void loop() {

  Serial.println("izquierDa");
  motor.izq(Pin);
  delay(2000);
  Serial.println("derecha");
  motor.derecha(Pin);
  delay(2000);
  Serial.println("NO");
  //for(int i = 0; i<=30; i++){ motor.no(Pin, 50); delay(1000);}
  motor.no(Pin, 50);
  delay(2000);
 // for(int i = 0; i<=30; i++){  motor.speak(Pin); delay(1000);}
  Serial.println("sepak");
motor.speak(Pin);
  delay(2000);
  //for(int i = 0; i<=30; i++){ motor.secuencia(Pin, 50); delay(1000);}
  Serial.println("sec");
 motor.secuencia(Pin, 50);
  delay(2000);
  //for(int i = 0; i<=30; i++){ motor.secuencia2(Pin, 50, 75); delay(1000);}
  Serial.println("sec2");
 motor.secuencia2(Pin, 50, 75); 
  delay(2000);
  
  
  // put your main code here, to run repeatedly:

}
