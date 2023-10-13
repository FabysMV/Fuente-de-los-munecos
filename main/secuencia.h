//va a dar la orden del movimiento de las cabezas dependiendo de lo que se haya escuchado en el microfono
//necesitamos la clase de la SD para poder rerpoducir todo


//Declaración de los motores
#include "motor_mov.h"
motor_mov cuello_g;
motor_mov cuello_b;
//PINES DE LOS MOTORES
int m_g = 12;
int m_b = 13;
///////////////////////////////////////////////////////////////////////
class accion{
  
  private:
  
  public:

  /// secuencia para cuando no hay señal de microfono por 1 minuto ///

  void baile(){}


  void lamento(){}


  void canto(){}


   /// secuencia para cuando hay señal ///
  void g_protect_a(){}//hablan a la niña, contesta protector agresivo

  void g_exp_b(){} // hablan a la niña, explica amable

  void b_amable_b(){} //hablan a niño, amable
  
  void b_agresivo_a(){} //hablan a niño, agresivo

  void ambos_agresivo(){} // se defienden, el niño habla en plural

  void ambos_g(){} //hablan a ambos, le hablan más bajo al niño pero a la niña le gritan---el niño la defiende

  void ambos_b(){} //le hablan a ambos, pero le hablan más fuerte al niño por lo que se enoja y pide de favor que se alejen de su hermana

  void ambos_amable(){} //hablan tranquilos sobre algo

  };
