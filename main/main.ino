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
// Variables para controlar las acciones, pra que no se haga un ciclo
int s = 0; //secuencia que se va a realizar
int last_s = 10; //ultima secuencia realizada
boolean flag_s = false;
unsigned long tiempo = 0;
unsigned long tiempo_prev = 0;
unsigned long cont_s = 0;
///////////////////////////////////////////////////////////////////////
// Variables y cositas para el contador que iniciará la secuencia automática
boolean flag = false;
unsigned long tiempo_set = 0;
unsigned long delta_sec = 0;
int in = 0; //para las veces que ha entrado en un ruido && ruido

//////////////////////////////////////////////////////////////////////////
// Estados escuchando y automatico




////////////////////////////////////////////////////////////////////////

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
  
//--------------------------------------------------------------------  
}

void loop() {

  
  if(digitalRead(Up) == HIGH)
  {
    Up = true;
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
            //// COMIENZO O SIGO EL CONTEO//////////
            if(flag == false){in = 0;}
            if(in == 0){tiempo_set = millis();}
            delta_sec = millis() - tiempo_set;
            in ++;
            if(delta_sec >= 60000){flag = true;
                                   tiempo_set = 0;}
            ////// NADA ////////////////////////////
            
            
            }//end if ruido nena
    
          else if(0 < analogRead(A1) < bajo) // le hablan bajo EXCLUSIVAMENTE a la nena
          {
            flag = false;
            // movimientos amables de explicación
            }//end if bajo a nena
    
          else if(alto < analogRead(A1)< max)
          {
             flag = false;
            //movimientos agresivos de protección
            
            }//end if alto a nena
      
      }//end if ruido a nene-----------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////
     else if(bajo<analogRead(A1)<alto) //el microfono de la nena tiene ruido?
    {

     //---------------------------------------------------------------------------------- 
          if(0 < analogRead(A0) < bajo) // le hablan bajo EXCLUSIVAMENTE a nene
          {
            flag = false;
            // niño habla / explica algo amable
            }//end if bajo a nene
    
          else if(alto < analogRead(A0)< max) // le hablan bajo EXCLUSIVAMENTE a nene AGRESIVO
          {
              flag = false;
            //movimientos agresivos defensa
            
            }//end if alto a nene
      
      }//end if ruido a nena-------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------
///      CUANDO NO HAY RUIDO --> LE HABLAN A LOS DOS    ///

      //a la nena le hablan alto?
      else if(alto < analogRead(A1)< max)
      {   flag = false;
          if(alto < analogRead(A0)< max)
          {//acciones AMBOS AGRESIVOS
            }//le hablan alto al nene?
          else if(0 < analogRead(A0) < bajo)
          {//HABLAN A NENA PROTECTOR Y PIDE QUE LO DEJEN A ÉL
            } // le hablan bajo al nene?
          
        }//end if nena alta 

        //a nena le hablan bajo?
      else if(0 < analogRead(A1) < bajo)
      {
        flag = false;
        if(alto < analogRead(A0)< max)
          {//agresivo por él, pide de favor que se eleje de ella
            }//le hablan alto al nene?
            
          else if(0 < analogRead(A0) < bajo)
          {//ambos hablan amables y él habla en plural
            } // le hablan bajo al nene?
        
        }//end if hablan bajo a nena
//////////////////////////////////////////////////////////////////////////////////////////
//------------ ya pasó el tiempo necesario para empezar las secuencias??-----------------
//veamos: lo sabremos con una flag que activará siempre esto
      if(flag == true)
      {
          //cálculos para el timer
          tiempo_prev = tiempo;
          tiempo = millis();
          cont_s = cont_s + tiempo - tiempo_prev; //incrementa el conteo en delta
          
          if(last_s != s)
          {
              switch(s){
              case 0:
                nenes.baile();
                break;
              case 1:
                nenes.lamento();
                break;
              case 2:
                nenes.canto();
                break;
              }//end switch s
            }// end if last_s

          if(cont_s >= 30000)//el límite debe de ser la duración del audio + 30 segundos
          {
            //ahora se cambia la secuencia
            Serial.println("cambio de secuencia");
            s = random(0,2);
            Serial.println(s);
            cont_s = 0;
            }
            
          last_s = s;
        //elegir una secuencia 1.-baile  2.-lamento  3.-canto 
       }//end if flag true --> que el contador ya llegó al limite
 /////////////////////////////////////////////////////////////////////////////////////////
    }// en up==true

   else{}


}//end loop
