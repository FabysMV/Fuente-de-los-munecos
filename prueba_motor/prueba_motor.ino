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
  Serial.println("NO");
  motor.derecha(Pin);
  delay(15);
 
  Serial.println("NO");
  motor.no(Pin, 50);
  delay(2000);
  
  // put your main code here, to run repeatedly:

}
