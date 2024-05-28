/* 
This is a simple demo of different features of the Calliope mini 3: 
- 5x5 LED Matrix
- Buttons A & B
- 3 internal RGB leds
- Motor driver DRV8835
- Microphone
- Serial
*/

#include <Adafruit_Calliope.h>
#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(3, PIN_RGB, NEO_GRB + NEO_KHZ800);

Adafruit_Calliope_Matrix calliope;

void setup() {  
  // Set up serial
  Serial.begin(9600);
  
  // Set up buttons
  pinMode(PIN_BUTTON_A, INPUT);  
  pinMode(PIN_BUTTON_B, INPUT);  

  // Set up 3 internal RGB leds
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(50, 0, 50)); // red + blue   = magenta
  pixels.setPixelColor(1, pixels.Color(50, 50, 0)); // red + green  = yellow
  pixels.setPixelColor(2, pixels.Color(0, 50, 50)); // green + blue = cyan
  pixels.show();

  // Set up motor driver for mini V3
  pinMode(PIN_M_MODE, OUTPUT); 
  pinMode(PIN_M0_DIR, OUTPUT); 
  pinMode(PIN_M0_SPEED, OUTPUT);
  pinMode(PIN_M1_DIR, OUTPUT);
  pinMode(PIN_M1_SPEED, OUTPUT);
  digitalWrite(PIN_M_MODE, 1); // Sets motor driver into correct mode (PHASE/ENABLE)
  digitalWrite(PIN_M0_DIR, 0); // Sets motor M0 into forward direction 
  digitalWrite(PIN_M1_DIR, 1); // Sets motor M1 into backward direction 

  // Set up microphone
  pinMode(28, OUTPUT);
  digitalWrite(28, HIGH);  // activates micro:phone by pulling RUN_MIC high
  pinMode(PIN_A6, INPUT); 

  // Set up LED matrix
  calliope.begin();
  Serial.println("calliope mini 3 demo is ready!");
  
  // draw a heart
  calliope.show(calliope.HEART);
  delay(1000);

  // draw a yes check
  calliope.show(calliope.YES);
  delay(1000);

  // clear display  
  calliope.clear();
}
    
void loop(){
  if (! digitalRead(PIN_BUTTON_A)) 
  {
    Serial.println("Button A pressed");
    calliope.print("A");
    analogWrite(PIN_M0_SPEED, 500); // Raise speed to 500/1024
    analogWrite(PIN_M1_SPEED, 500); // Raise speed to 500/1024
    pixels.fill(pixels.Color(0, 30, 0)); // Sets neopixels to green
    pixels.show();
  }
  if (! digitalRead(PIN_BUTTON_B)) 
  {
    Serial.println("Button B pressed");
    calliope.print("B");
    analogWrite(PIN_M0_SPEED, 0); // Turn off motor
    analogWrite(PIN_M1_SPEED, 0); // Turn off motor
    pixels.fill(pixels.Color(30, 0, 0)); // Sets neopixels to red
    pixels.show();
  }
  
  // Microphone Measurement: get maximum value over 1000 measurements
  int maxVol = 0;
  for (int i = 0; i < 1000; ++i) {
    int mic = analogRead(PIN_A6);
    maxVol = max(maxVol, mic);
  }
  Serial.print("Volume:");
  Serial.println(maxVol);

  calliope.drawLine(4,0,4,4, LED_OFF); // removes the mic volume column
  calliope.drawLine(4,4,4,map(maxVol,0,170,4,0), LED_ON); // draws a line with the length of the normalized mic volume on the 4th column
  
  delay(100); 

}
