/* 
This is a demo of different features of the Calliope mini 3: 
- 5x5 LED Matrix
- Buttons A & B
- 3 internal RGB leds
- Motor driver DRV8835
- Microphone
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
  pixels.show(); // Initialize all pixels to 'off'

  // Set up motor driver for mini V3
  pinMode(PIN_M_MODE, OUTPUT); 
  pinMode(PIN_M0_DIR, OUTPUT); 
  pinMode(PIN_M0_SPEED, OUTPUT);
  pinMode(PIN_M1_DIR, OUTPUT);
  pinMode(PIN_M1_SPEED, OUTPUT);
  digitalWrite(PIN_M_MODE, 1); // Sets motor driver into correct mode (PHASE/ENABLE)
  digitalWrite(PIN_M0_DIR, 0); // Sets motor M0 into forward direction 
  analogWrite(PIN_M0_SPEED, 200); //Sets speed of M0 to 200/1024
  digitalWrite(PIN_M1_DIR, 1); // Sets motor M0 into backward direction 
  analogWrite(PIN_M1_SPEED, 200); // Sets speed of M1 to 200/1024

  // Set up microphone
  pinMode(28, OUTPUT); // activates micro:phone by pulling RUN_MIC high
  digitalWrite(28, HIGH);
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
    analogWrite(PIN_M0_SPEED, 500); // Raise speed to 500/1024
    analogWrite(PIN_M1_SPEED, 500); // Raise speed to 500/1024
    pixels.setPixelColor(1, pixels.Color(0, 50, 0)); pixels.show();
  }
  if (! digitalRead(PIN_BUTTON_B)) 
  {
    Serial.println("Button B pressed");
    analogWrite(PIN_M0_SPEED, 0); // Turn off motor
    analogWrite(PIN_M1_SPEED, 0); // Turn off motor
    pixels.setPixelColor(1, pixels.Color(0, 0, 0)); pixels.show();
  }
  
  // Microphone Measurement: get maximum value over 1000 measurements
  int maxVol = 0;
  for (int i = 0; i < 1000; ++i) {
    int mic = analogRead(PIN_A6);
    maxVol = max(maxVol, mic);
  }
  Serial.print("Volume:");
  Serial.println(maxVol);
  calliope.print(map(maxVol,0,150,0,9)); // Prints maximum volume on led matrix

  delay(100); // 
  
}
