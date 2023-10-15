#include <Servo.h>
//PINES DE LOS MOTORES
int m_g = 12;
int m_b = 13;


class motor_mov{
  private:
  
  Servo servo;
  
  public:
////// aqui van los métodos /////
    void SetUp(int pin){  //aqui ponemos los pines correspondientes para la esp32 relacionados con los motores
      servo.attach(pin);
      }

    void izq(){}

    void neutro(int pos){}

    void speak()
    {
      //Movimiento de 45° a la izquierda, después 90° a la derecha. 
      }

    void secuencia(){}
  
    
      

  };
