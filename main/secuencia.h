//va a dar la orden del movimiento de las cabezas dependiendo de lo que se haya escuchado en el microfono
//necesitamos la clase de la SD para poder rerpoducir todo


//Declaración de los motores
#include "motor_mov.h"
motor_mov cuello_g;
motor_mov cuello_b;

///////////////////////////////////////////////////////////////////////
class accion{
  
  private:
  
  public:

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
    }//hablan a la niña, contesta protector agresivo

  void g_bajo()
  {
    Serial.println("Niña bajo");
    delay(2000);
    } // hablan a la niña, explica amable

  void b_bajo()
  {
    Serial.println("Niño bajo");
    delay(2000);
    } //hablan a niño, amable
  
  void b_alto()
  {
    Serial.println("Niño alto");
    delay(2000);
    } //hablan a niño, agresivo

  void ambos_alto()
  {
    Serial.println("Ambos alto");
    delay(2000);
    } // se defienden, el niño habla en plural

  void ambos_g()
  {
    Serial.println("Ambos, pero niña más alto");
    delay(2000);
    } //hablan a ambos, le hablan más bajo al niño pero a la niña le gritan---el niño la defiende

  void ambos_b()
  {
    Serial.println("Ambos, pero niño más alto");
    delay(2000);
    } //le hablan a ambos, pero le hablan más fuerte al niño por lo que se enoja y pide de favor que se alejen de su hermana

  void ambos_bajo()
  {
    Serial.println("Ambos bajo");
    delay(2000);
    } //hablan tranquilos sobre algo

  };
