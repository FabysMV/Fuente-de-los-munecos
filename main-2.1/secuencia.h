//va a dar la orden del movimiento de las cabezas dependiendo de lo que se haya escuchado en el microfono
//necesitamos la clase de la SD para poder rerpoducir todo
//******** CONFIGURACIÓN PARA SD Y AUDIO  *************//

//Declaración de los motores
#include "motor_mov.h"
motor_mov girl;
motor_mov boy;
int rapidez = 200; //rapidez con la que hace la negación en milisegundos
//PINES DE LOS MOTORES
int m_g = 12;
int m_b = 13;
///////////////////////////////////////////////////////////////////////
//---- CONTADOR -----//
unsigned long tiempo = 0;
unsigned long last_t = 0;
unsigned long cont = 0;
unsigned long limite = 0;


class accion{
  
  private:
      //posiciones iniciales de los niños
      //:: NOTA--> la niña está girada ligeramente hacia su hermano
      int n_g = 45;
      int n_b = 90;
      int S = 0;
  public:

  

  /// secuencia para cuando no hay señal de microfono por 1 minuto ///

  int getS(){return S;}
  
  void baile() //audio9
  { Serial.println("9");
    limite = 37000;
    tiempo = millis();
    do{Serial.println("baile"); 
          last_t = tiempo;
          tiempo = millis();
          cont = cont + (tiempo - last_t);
          boy.no(m_b); delay(15);
          girl.no(m_g);delay(15);
         }while(cont <= limite);
    cont = 0;
    delay(100); S = 1;}


  void risa() //audio 12 canto2
  {
    Serial.println("12");
    limite = 9000; tiempo = millis();
    do{Serial.println("RISA"); 
          last_t = tiempo;
          tiempo = millis();
          cont = cont + (tiempo - last_t);
          boy.izq(m_b);
          delay(15);
          girl.no(m_g);
          delay(500);
          boy.derecha(m_b);
         }while(cont <= limite);
    cont = 0;
    Serial.println("lamento");
    S = 2;
    }


  void canto() //audio 10
  {
    Serial.println("10");
    limite = 58000; tiempo = millis();
      do{Serial.println("CANTO"); 
          last_t = tiempo;
          tiempo = millis();
          cont = cont + (tiempo - last_t);
          boy.no(m_b); delay(15);
          girl.no(m_g); delay(15);
         }while(cont <= limite);
    cont = 0;
    Serial.println("canto"); S = 0;}


   /// secuencia para cuando hay señal ///
  void g_alto()
  {
      Serial.println("Niña alto");
      girl.izq(m_g); //gira a la izquierda
      boy.neutro(n_b, m_b);
      //***************
     // Audio.play("Susurros.wav"); //!!importante llamar así el audio
     //***********************************
     //susurro es audio 11
     Serial.println("11");
     limite = 5000; tiempo = millis();
      do{Serial.println("susurros");
          last_t = tiempo;
          tiempo = millis();
          cont = cont + (tiempo - last_t);}while(cont <= limite);
      cont = 0;
      girl.neutro(n_g, m_g);
      delay(15); boy.derecha(m_b); //voltea a ver a su hermana
      delay(1000);  //espera 1 segundo
     Serial.println("1"); 
     limite = 9000; tiempo = millis();
      do{Serial.println("audio1");  
          last_t = tiempo;
          tiempo = millis();
          cont = cont + (tiempo - last_t);
         boy.speak(m_b); delay(15);}while(cont <= limite); //secuencia solo mientras habla
      cont = 0;
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);
      delay(15);
    }///Niña se voltea y le habla a su hermano, él responde por ella


  void g_bajo()
  {
      Serial.println("Niña bajo");
      delay(2000);
      girl.derecha(m_g);
      delay(500);
      boy.derecha(m_b);
      delay(15);
     Serial.println("2");
     limite = 25000; tiempo = millis();
      do{Serial.println("audio2");  
          last_t = tiempo;
          tiempo = millis();
          cont = cont + (tiempo - last_t);
         }while(cont <= limite);
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);
      delay(15);
    } // El hermano se intriga por lo que andan susurrando

    
  void b_alto()
  {
      Serial.println("Niño alto");
      girl.derecha(m_g); delay(15);
      boy.derecha(m_b);
      Serial.println("3");
      limite = 6000; tiempo = millis();
      do{Serial.println("audio3"); 
          last_t = tiempo;
          tiempo = millis();
          cont = cont + (tiempo - last_t);
          girl.izq(m_g); delay(15);
          boy.speak(m_b); delay(15);
         }while(cont <= limite);
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);
      delay(15);
    } //El hermano da algún dato curioso sobre ellos

    
  void b_bajo()
  {
      Serial.println("Niño bajo");
      boy.derecha(m_b);
      delay(1000);
      boy.izq(m_b);
      delay(15);
      Serial.println("4");
      limite = 6000; tiempo = millis();
      do{Serial.println("audio4"); 
          last_t = tiempo;
          tiempo = millis();
          cont = cont + (tiempo - last_t);
            boy.speak(m_b);
           }while(cont <= limite);
       boy.neutro(n_b, m_b);//regresa a posición inicial
       delay(15);
       girl.neutro(n_g, m_g); delay(15);
    } //Voltea a ver a su hermana y piden que hablen más fuerte que ella no escuchó


  void ambos_alto()
  {
      Serial.println("Ambos alto");
      girl.derecha(m_g); delay(15);
      boy.izq(m_b); delay(500);
      girl.izq(m_g); delay(15);
      boy.derecha(m_b); delay(1000);
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);
      Serial.println("5");
      limite = 11000; tiempo = millis();
      do{Serial.println("audio5"); 
          last_t = tiempo;
          tiempo = millis();
          cont = cont + (tiempo - last_t);
          boy.speak(m_b); delay(15);}while(cont <= limite);
    } //Felices, dicen algún dato curioso

  void ambos_g()
  {
      Serial.println("Ambos, pero niña más alto"); 
      boy.derecha(m_b); delay(500);
      girl.izq(m_g); delay(500);
      Serial.println("6");
      limite = 5000; tiempo = millis();
      do{Serial.println("audio6"); 
          last_t = tiempo;
          tiempo = millis();
          cont = cont + (tiempo - last_t);
              boy.no(m_b); delay(15);
             }while(cont <= limite);
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g); delay(15);
    } //Voltea a ver a su izquierda, después a su hermana y se queja de que no escuchó bien
    
    
  void ambos_b()
  {
      Serial.println("Ambos, pero niño más alto");
      boy.derecha(m_b); delay(1000);
      boy.izq(m_b);     delay(15);
      girl.izq(m_g);    delay(15);
      Serial.println("7");
      limite = 9000; tiempo = millis();
      do{Serial.println("audio7"); 
          last_t = tiempo;
          tiempo = millis();
          cont = cont + (tiempo - last_t);
          boy.speak(m_b);  delay(800);
          boy.speak(m_b);  delay(500);
         }while(cont <= limite);
      boy.neutro(n_b, m_b);//regresa a posición inicial
      delay(15);
      girl.neutro(n_g, m_g);  delay(15);
     } //Voltea a ver a su hermana, después voltea a ver a quien le habló y le dice un dato curioso.

    
  void ambos_bajo()
  {
    Serial.println("Ambos bajo");
    boy.derecha(m_b);  delay(15);
    girl.izq(m_g);     delay(1500);
     boy.neutro(n_b, m_b);//regresa a posición inicial
     delay(15);
     girl.neutro(n_g, m_g); delay(15);
    Serial.println("8");
    limite = 9000; tiempo = millis();
    do{Serial.println("a8"); 
          last_t = tiempo;
          tiempo = millis();
          cont = cont + (tiempo - last_t);
          
         }while(cont <= limite);
    
    } //Los dos hermanos se voltean a ver, y dicen que están felices

  };
