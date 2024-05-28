#ifdef _VARIANT_CALLIOPE_MINI_
const int COL1 = 4;     // Column #1 control (mini 1 &2)
const int LED = 13;     // 'row 1' led (mini 1 & 2)
#endif

#ifdef _CALLIOPE_MINI_V3_
const int COL1 = 4;     // Column #1 control (mini3)
const int LED = 21;     // 'row 1' led (mini3)
#endif

void setup() {  
  Serial.begin(9600);
  
  Serial.println("calliope is ready!");

  // because the LEDs are multiplexed, we must ground the opposite side of the LED
  pinMode(COL1, OUTPUT);
  digitalWrite(COL1, LOW); 
   
  pinMode(LED, OUTPUT);   
}

void loop(){
  Serial.println("blink!");
  
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}
