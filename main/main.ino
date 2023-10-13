//Documento que efectúa el control de todo el sistema
//Aquí se reciben la señales de los micrófonos, se da la orden de movimiento y se indica qué canción reproducir de la SD

//PINES que indican los pines de entrada ANALÓGICOS del micrófono
//cambiar al numero de pin de A0---pin nene
//                            A1---pin nena

//////////////////////////////////////////////////////////////////////
//Variables de pines de botones y ESTADOS
int b_Up;
int b_Sleep;
// estados  //
int Sleep = 0;
int Up = 0;

// Pines de los LED ///////////////////////////////////////////////////
int Led_g = 1;
int Led_b = 2;
///////////////////////////////////////////////////////////////////////
//Declaración de los motores
#include "motor.h"
motor_mov cuello_g;
motor_mov cuello_b;
//PINES DE LOS MOTORES
int m_g = 12;
int m_b = 13;
///////////////////////////////////////////////////////////////////////



void setup() {
  Serial.begin(9600);
  //entradas--botones
  pinMode(b_Up);
  pinMode(b_Sleep);
  //salidas--LED
  pinMode(Led_g, OUTPUT);
  pinMode(Led_b, OUTPUT);
  /////////////////////////////
//parameter value of 1000 is fully counter-clockwise, 2000 is fully clockwise, and 1500 is in the middle.
//-----------------Revisión del movimiento de los motores------------
  cuello_g.mov(m_g, 1200);
  cuello_b.mov(m_b, 1200);
  delay(100);
  cuello_g.Stop(m_g);
  cuello_b.Stop(m_b);
  cuello_g.mov(m_g, 1700);
  cuello_b.mov(m_b, 1700);
  delay(100);
  cuello_g.Stop(m_g);
  cuello_b.Stop(m_b);
//--------------------------------------------------------------------  
}

void loop() {
  if(digitalRead(Sleep) == HIGH)//si se presionó el botón de dormir
  {
    Serial.println("mimido");
    do{
      digitalRead(Up) //vemos que no se haya dado la indicación de que despierten
      if(digitalRead == HIGH
      {Up = 1;
      Serial.println("despertando...");
      delay(100);}//si es así, cambiamos el estado de Up a activo
    }while(Up != 1); //cuando Up esté activo, salimos del ciclo
    
    }

  if(digitalRead(Up)== HIGH) //se ha apretado el botón que despierta a los niños
  {
    Serial.println("despierto!!");
    // Procedemos a revisar el estado el micrófono
    }


}
