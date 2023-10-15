#include <Servo.h>
//PINES DE LOS MOTORES
int m_g = 12;
int m_b = 13;
//posiciones iniciales de los niños
//:: NOTA--> la niña está girada ligeramente hacia su hermano
int pos_i_g = 0;
  int pos_i_b = 0;

class motor_mov{
  private:
  
  Servo servo;
  
  public:
////// aqui van los métodos /////
    void SetUp(int pin){  //aqui ponemos los pines correspondientes para la esp32 relacionados con los motores
      servo.attach(pin);
      }


  
    
      

  };
