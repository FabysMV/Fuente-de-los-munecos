const int sensorPIN = A0;
const int sampleWindow = 50; // Ancho ventana en mS (50 mS = 20Hz)
int ancho = 0;
int last_ancho = 0;
int pico = 0;
boolean check = false;
unsigned long cont_sh = 0;
unsigned long last_sh = 0;
unsigned long time_sh = 0;
int tiempo_silencio = 3000;
double volts = 0;
   
void setup() 
{
   Serial.begin(9600);
}

void loop() 
{
   microfono();
   Serial.println(volts);

   if(volts >= 3.0){
    Serial.println("detectado");

    check = true;

    do{
      Serial.println("MUESTRA");
         microfono();
      Serial.print("Volts: ");  Serial.print(volts);
        if(volts >= 3.0){Serial.println("detectado alto?");
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

      }while(check == true);
      // evaluación de lo escuchado
      
      Serial.print("picos: ");  Serial.println(pico);
      Serial.print("ancho: ");  Serial.println(last_ancho);
      if(last_ancho >=10){Serial.println("ALTO");}
      else if (1 <= last_ancho < 10 )
        {
          if(pico >= 1){Serial.println("susurro");}
          }

      if (last_ancho < 3)
      {Serial.println("NADA");}
      

      //reseteamos valores
      pico = 0;
      last_ancho = 0;
      ancho = 0;
   }
      
      
    Serial.println("----------------------------------");    
}


void microfono(){
  unsigned long startMillis= millis();
  unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
   
 

   // Recopilar durante la ventana
   unsigned int sample;
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(sensorPIN);
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
