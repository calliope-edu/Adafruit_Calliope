// Slow die temperature reader for piping to Adafruit IO

#include <Adafruit_Calliope.h>

Adafruit_Calliope calliope;

void setup()
{
  Serial.begin(115200);
  
  Serial.println("nRF5x Die Temperature Plotting");

  calliope.BTLESerial.setLocalName("calliope");
  calliope.BTLESerial.begin();

  // Start LED matrix driver after radio (required)
  calliope.begin();
}

#define OVERSAMPLE 50

void loop() {
  calliope.BTLESerial.poll();

  // Take 'OVERSAMPLES' measurements and average them!
  float avgtemp = 0;
  for (int i = 0; i < OVERSAMPLE; i++) {
    int32_t temp;
    do {
      temp = calliope.getDieTemp();
    } while (temp == 0);  // re run until we get valid data
    avgtemp += temp;
    delay(1);
  }
  avgtemp /= OVERSAMPLE;
  
  Serial.print("Temperature (C): ");
  Serial.println(avgtemp);  // Float value since temp is in 0.25°C steps

  // Send just the raw reading over bluetooth
  calliope.BTLESerial.println(avgtemp);

  delay(5000);
}

