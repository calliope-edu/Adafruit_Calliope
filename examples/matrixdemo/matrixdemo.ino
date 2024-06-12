// This is a demo of the matrix driver code
// works with Adafruit GFX commands - its just
// a really small screen!
// https://learn.adafruit.com/adafruit-gfx-graphics-library

#include <Calliope_Arduino.h>

Calliope_Matrix calliope;

const uint8_t
  smile_bmp[] =
  { B00000,
    B01010,
    B00000,
    B10001,
    B01110, };
    
void setup() {  
  Serial.begin(9600);
  
  Serial.println("calliope matrix demo is ready!");

  calliope.begin();
}
    
void loop(){
  // Fill screen
  calliope.fillScreen(LED_ON);
  delay(1000);

  // draw a heart
  calliope.show(calliope.HEART);
  delay(1000);

  // draw a no cross
  calliope.show(calliope.NO);
  delay(1000);

  // draw a yes check
  calliope.show(calliope.YES);
  delay(1000);

  // draw a custom made bitmap face
  calliope.show(smile_bmp);
  delay(1000);
  
  calliope.clear();
  // Draw a line 'by hand'
  calliope.drawPixel(0, 0, LED_ON);
  calliope.drawPixel(1, 1, LED_ON);
  calliope.drawPixel(2, 2, LED_ON);
  calliope.drawPixel(3, 3, LED_ON);
  calliope.drawPixel(4, 4, LED_ON);
  // draw the 'opposite' line with drawline (easier!)
  calliope.drawLine(0, 4, 4, 0, LED_ON);

  delay(1000);

  // erase screen, draw a square
  calliope.clear();
  calliope.drawRect(0,0, 5, 5, LED_ON); // top left corner @ (0,0), 5 by 5 pixels size

  delay(1000);

  // erase screen, draw a circle
  calliope.clear();
  calliope.drawCircle(2,2, 2, LED_ON); // center on 2, 2, radius 2

  delay(1000);

  // erase screen, draw a filled triangle
  calliope.clear();
  calliope.fillTriangle(0,4, 2,0, 4,4, LED_ON); 

  delay(1000);

  // scroll some text the 'easy' way
  calliope.print("HELLO WORLD");

  // count up!
  for (int i=0; i<10; i++) {
    calliope.print(i);
    delay(500);
  }

  calliope.print(3.1415, 4);  // pi time, 4 digits of precision!!

}
