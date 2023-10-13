//Documento que efectúa el control de todo el sistema
//Aquí se reciben la señales de los micrófonos, se da la orden de movimiento y se indica qué canción reproducir de la SD

//******CONFIGURACIÓN Y CALIBRACIÓN DEL MICRÓFONO**********************
//PINES que indican los pines de entrada ANALÓGICOS del micrófono
//cambiar al numero de pin de A0---pin nene
//                            A1---pin nena
int bajo = 0; //limite de lo que considero bajo
int alto = 0; // limite en donde empiezo a considerar que es alto
int max = 255; //valor máximo al que llega el micrófono
//////////////////////////////////////////////////////////////////////
//Variables de pines de botones y ESTADOS
int b_Up;
int b_Sleep;
// estados  //
boolean Sleep = false;
boolean Up = false;

// Pines de los LED ///////////////////////////////////////////////////
int Led_g = 1;
int Led_b = 2;
///////////////////////////////////////////////////////////////////////
#include "secuencia.h"
//hacemos el objeto de las acciones de los niños
accion nenes;
int s = 0; //secuencia que se va a realizar
///////////////////////////////////////////////////////////////////////
// Variables y cositas para el contador que iniciará la secuencia automática
boolean flag = false;
unsigned long tiempo = 0;
unsigned long tiempo_set = 0;
unsigned long delta_sec = 0;
int in = 0; //para las veces que ha entrado en un ruido && ruido

////////////////////////////////////////////////////////////////////////////


void setup() {
  Serial.begin(9600);
  //entradas--botones
  pinMode(b_Up, INPUT);
  pinMode(b_Sleep, INPUT);
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

  tiempo = millis();
  if(digitalRead(Up) == HIGH)
  {
    Up == true;
    }
 
  if(digitalRead(Sleep) == HIGH && digitalRead(Up)== LOW)//si se presionó el botón de dormir
  {
    delta_sec = 0;
    Up = false;
    Serial.println("mimido");
    do{
       //vemos que no se haya dado la indicación de que despierten
        if(digitalRead(Up) == HIGH)
        {Up = true;
        Serial.println("despertando...");
        delay(100);}//si es así, cambiamos el estado de Up a activo
      }while(Up == false); //cuando Up esté activo, salimos del ciclo
    
    }

  if(Up == true) //se ha apretado el botón que despierta a los niños
  {
    Serial.println("despierto!!");
    //
    // Procedemos a revisar el estado el micrófono
    Serial.println("revisando micrófonos...");
    if(bajo<analogRead(A0)<alto) //el microfono de la nene tiene ruido?
    {

     //---------------------------------------------------------------------------------- 
      if(bajo<analogRead(A1)<alto) //tiene ruido la nena?
      {
        if(flag == false){in = 0;}
        if(in == 0){tiempo_set = millis();}
        delta_sec = millis() - tiempo_set;
        in ++;
        if(delta_sec >= 60000){flag = true;
                               tiempo_set = 0;
                               }
        ////// NADA //////////
        //// COMIENZO O SIGO EL CONTEO////
        
        }//end if ruido nena

      if(0 < analogRead(A1) < bajo) // le hablan bajo EXCLUSIVAMENTE a la nena
      {
        flag == false;
        // movimientos amables de explicación
        }//end if bajo a nena

      if(alto < analogRead(A1)< max)
      {
         flag == false;
        //movimientos agresivos de protección
        
        }//end if alto a nena
      
      }//end if ruido a nene-----------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
       if(bajo<analogRead(A1)<alto) //el microfono de la nena tiene ruido?
    {

     //---------------------------------------------------------------------------------- 
      

      if(0 < analogRead(A0) < bajo) // le hablan bajo EXCLUSIVAMENTE a nene
      {
        flag == false;
        // niño habla / explica algo amable
        }//end if bajo a nene

      if(alto < analogRead(A0)< max) // le hablan bajo EXCLUSIVAMENTE a nene AGRESIVO
      {
          flag == false;
        //movimientos agresivos defensa
        
        }//end if alto a nene
      
      }//end if ruido a nena-------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
///      CUANDO NO HAY RUIDO --> LE HABLAN A LOS DOS    ///

      //a la nenta le hablan alto?
      if(alto < analogRead(A1)< max)
      {   flag == false;
          if(alto < analogRead(A0)< max)
          {//acciones AMBOS AGRESIVOS
            }//le hablan alto al nene?
          if(0 < analogRead(A0) < bajo)
          {//HABLAN A NENA PROTECTOR Y PIDE QUE LO DEJEN A ÉL
            } // le hablan bajo al nene?
          
        }//end if nena alta 

        //a nena le hablan bajo?
      if(0 < analogRead(A1) < bajo){
        flag == false;
        if(alto < analogRead(A0)< max)
          {//agresivo por él, pide de favor que se eleje de ella
            }//le hablan alto al nene?
            
          if(0 < analogRead(A0) < bajo)
          {//ambos hablan amables y él habla en plural
            } // le hablan bajo al nene?
        
        }//end if hablan bajo a nena
//////////////////////////////////////////////////////////////////////////////////////////
//------------ ya pasó el tiempo necesario para empezar las secuencias??-----------------
//veamos: lo sabremos con una flag que activará siempre esto
      if(flag == true)
      {
        switch(s){
          case 0:
            accion.baile();
            s++;
            break;
          case 1:
            accion.lamento();
            s++;
            break;
          case 2:
            accion.canto();
            s = 0;
            break;
          
          }
        
        //elegir una secuencia 1.-baile  2.-lamento  3.-canto 
       }
 /////////////////////////////////////////////////////////////////////////////////////////
    }// en up==1

   else{}


}
