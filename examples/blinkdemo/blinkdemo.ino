const int COL1 = 4;     // Column #1 control (mini3)
const int LED = 21;     // 'row 1' led (mini3)

void setup() {  
  Serial.begin(9600);
  
  Serial.println("calliope is ready!");

  // because the LEDs are multiplexed, we must ground the opposite side of the LED
  pinMode(COL1, OUTPUT);
  digitalWrite(COL1, HIGH); 
   
  pinMode(LED, OUTPUT);   
}

void loop(){
  Serial.println("blink!");
  
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}
