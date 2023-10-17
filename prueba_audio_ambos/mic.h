//const int sensorPIN = A0;
const int sampleWindow = 50; // Ancho ventana en mS (50 mS = 20Hz)
boolean check = false;
unsigned long cont_sh = 0;
unsigned long last_sh = 0;
unsigned long time_sh = 0;
int tiempo_silencio = 3000;
double volts = 0;


class mic{
  private:
  boolean check = 0;
  double volts = 0;
  int ancho = 0;
  int last_ancho = 0;
  int pico = 0;
  char state;
  public:


  
  void microfono(int sensorPIN ){
      unsigned long startMillis= millis();
      unsigned int signalMax = 0;
      unsigned int signalMin = 1024;
     // Recopilar durante la ventana
      unsigned int sample;
       while (millis() - startMillis < sampleWindow)
       {  sample = analogRead(sensorPIN);
          if (sample < 1024)
          {
             if (sample > signalMax)
             {
                signalMax = sample;  // Actualizar máximo
             }
             else if (sample < signalMin)
             {
                signalMin = sample;  // Actualizar mínimo
             }
          }
       }
       unsigned int peakToPeak = signalMax - signalMin;  // Amplitud del sonido
      volts = (peakToPeak * 5.0) / 1024;  // Convertir a tensión
  }

  double getVolts()
  {return volts;}


  void evaluar()
  {   if(volts >= 3.0){Serial.println("detectado alto?");
          ancho++;
          cont_sh = 0;
          if(ancho > last_ancho){last_ancho = ancho;}    
        }//voltaje alto
       
      
       else if(volts < 3.0)
          {
            if(ancho != 0)
              {pico++; Serial.println("PICOOOO");}
            //inicio contador
            last_sh = time_sh;
            time_sh = millis();
            Serial.print("cont_sh: ");  Serial.println(cont_sh);
            cont_sh = cont_sh + (time_sh - last_sh);
            if(cont_sh >= tiempo_silencio){check = false; cont_sh = 0;}
            ancho = 0;
              
            }//voltaje bajo
    }
  
  boolean getCheck(){return check;}

  
  void SetCheck(){check = true;}


 void SetState(){
      Serial.print("picos: ");  Serial.print(pico); Serial.print("\t");
      Serial.print("ancho: ");  Serial.println(last_ancho);
      if(last_ancho >=10){Serial.println("ALTO"); state = 'a';}
      else if (1 <= last_ancho < 10 )
        {
          if(pico >= 1){Serial.println("susurro"); state = 's';}
          }

      if (last_ancho < 3)
      {Serial.println("NADA"); state = 'n';}
      //reseteamos valores
      pico = 0;
      last_ancho = 0;
      ancho = 0;}


  char getState(){return state;}
  
  
  };
