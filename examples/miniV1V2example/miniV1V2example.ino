/* 
This is a simple demo of different features of the Calliope mini 1 & 2: 
- 5x5 LED Matrix
- Buttons A & B
- Microphone
- Serial 
*/

#include <Calliope_Arduino.h>
Calliope_Matrix calliope;


void setup() {  
  
  // Set up serial
  Serial.begin(9600);
  
  // Set up buttons
  pinMode(PIN_BUTTON_A, INPUT);  
  pinMode(PIN_BUTTON_B, INPUT);  

  // Set up microphone
  pinMode(PIN_A0, INPUT); 

  // Set up LED matrix
  calliope.begin();
  Serial.println("calliope mini demo is ready!");
  
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
  }
  if (! digitalRead(PIN_BUTTON_B)) 
  {
    Serial.println("Button B pressed");
    calliope.print("B");
  }
  // Microphone Measurement: get maximum value over 1000 measurements
  int maxVol = 0;
  for (int i = 0; i < 1000; ++i) {
    int mic = analogRead(PIN_A0)-511;
    maxVol = max(maxVol, mic);
  }
  Serial.print("Volume:");
  Serial.println(maxVol);
  

  calliope.drawLine(4,0,4,4, LED_OFF); //turns off mic volume column
  calliope.drawLine(4,4,4,map(maxVol,0,510,4,0), LED_ON); // draws a line with the length of the normalized mic volume on the 4th column
  delay(100); // 
  
}
