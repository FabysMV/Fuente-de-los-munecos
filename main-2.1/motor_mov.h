#include <Servo.h>

class motor_mov{
  private:
  boolean ang = false;
  boolean ang2 = false;
  boolean ang3 = false;
  int pos = 0;
  int pos_s1 = 0;
  int pos_s2 = 0;
  Servo servo;
  
  public:
////// aqui van los métodos /////
    void SetUp(int pin){  //aqui ponemos los pines correspondientes para la esp32 relacionados con los motores
      servo.attach(pin);
      }

    void izq(int pin)
    {
      servo.attach(pin);
      servo.write(0);
      delay(15);
      }

    void derecha(int pin){
      servo.attach(pin);
      servo.write(180);
      delay(15);
      }

    void neutro(int pos, int pin){
      servo.attach(pin);
      servo.write(pos);
      delay(15);}

    void speak(int pin)
    {
      servo.attach(pin);
      servo.write(30);
      delay(1000);
      servo.write(90);
      delay(1000);
      servo.write(150);
      delay(500);
      //Movimiento de 45° a la izquierda, después 90° a la derecha. 
      }

    void secuencia(int pin, int rapidez){
      servo.attach(pin);
      for(int i = 0; i<=90; i++)
      {
        if(ang2 == false){pos_s1 = 44; pos_s1 ++;}
        else{pos_s1--;}
        if(pos_s1>134){ang2 = true;}
        servo.attach(pin);
        servo.write(pos_s1);
        delay(15);
        delay(rapidez);        
        }}

    void secuencia2(int pin,int rapidez, int inicio){
      servo.attach(pin);
      for(int i = 0; i<=90; i++)
      {
        if(ang3 == false){pos_s2 = inicio; pos_s2 ++;}
        else{pos_s2--;}
        if(pos_s2 > 134){ang3 = true;}
        servo.attach(pin);
        servo.write(pos_s2);
        delay(15);
        //delay(rapidez);        
        }} //voltea a varios lados

    void no(int pin){
      int i=0;
      do{ servo.attach(pin);
          servo.write(45);
          delay(800);
          servo.attach(pin);
          servo.write(135);
          delay(800); i++; }while(i<3);
     
      }//movimiento de negación

      void no2(int pin){
      int i=0;
      do{ servo.attach(pin);
          servo.write(45);
          delay(400);
          servo.attach(pin);
          servo.write(135);
          delay(400); i++; }while(i<2);
      }
  
    
      

  };
