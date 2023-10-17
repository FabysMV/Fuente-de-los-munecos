const int sensorPIN = A0;
const int sampleWindow = 50; // Ancho ventana en mS (50 mS = 20Hz)
double volts;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
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
  Serial.println(volts);
  // put your main code here, to run repeatedly:

}
