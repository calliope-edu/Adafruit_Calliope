// This is a 'low level' demo showing how to use timer 2 (the only available timer really)
// to blink an LED. This code turned into the matrix handler, so you cant use it and the 
// Calliope library at the same time but maybe its useful!


#ifdef _VARIANT_CALLIOPE_MINI_
const int COL1 = 4;     // Column #1 control (mini 1 &2)
const int LED = 13;     // 'row 1' led (mini 1 & 2)
#endif

#ifdef _CALLIOPE_MINI_V3_
const int COL1 = 4;     // Column #1 control (mini3)
const int LED = 21;     // 'row 1' led (mini3)
#endif

void start_timer(void)
{    
  NRF_TIMER2->MODE = TIMER_MODE_MODE_Timer;              // Set the timer in Counter Mode
  NRF_TIMER2->TASKS_CLEAR = 1;                           // clear the task first to be usable for later
  NRF_TIMER2->PRESCALER   = 8;  
  NRF_TIMER2->BITMODE = TIMER_BITMODE_BITMODE_16Bit;     //Set counter to 16 bit resolution
  NRF_TIMER2->CC[0] = 32000;                               //Set value for TIMER2 compare register 0
  NRF_TIMER2->CC[1] = 5;                                   //Set value for TIMER2 compare register 1
    
  // Enable interrupt on Timer 2, both for CC[0] and CC[1] compare match events
  NRF_TIMER2->INTENSET = (TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos) | (TIMER_INTENSET_COMPARE1_Enabled << TIMER_INTENSET_COMPARE1_Pos);
  NVIC_EnableIRQ(TIMER2_IRQn);
    
  NRF_TIMER2->TASKS_START = 1;               // Start TIMER2
}

    
/** TIMTER2 peripheral interrupt handler. This interrupt handler is called whenever there it a TIMER2 interrupt
 * Don't mess with this line. really.
 */
 extern "C"  { void TIMER2_IRQHandler(void) { timer_pal();  } }

void timer_pal(void) {
  if ((NRF_TIMER2->EVENTS_COMPARE[0] != 0) && ((NRF_TIMER2->INTENSET & TIMER_INTENSET_COMPARE0_Msk) != 0))
  {
    NRF_TIMER2->EVENTS_COMPARE[0] = 0;         //Clear compare register 0 event 
    digitalWrite(LED, HIGH);
  }
  
  if ((NRF_TIMER2->EVENTS_COMPARE[1] != 0) && ((NRF_TIMER2->INTENSET & TIMER_INTENSET_COMPARE1_Msk) != 0))
  {
    NRF_TIMER2->EVENTS_COMPARE[1] = 0;         //Clear compare register 1 event
    digitalWrite(LED, LOW);
  }
}



void setup() {  
  Serial.begin(9600);
  Serial.println("calliope is ready!");

  // because the LEDs are multiplexed, we must ground the opposite side of the LED
  pinMode(COL1, OUTPUT);
  digitalWrite(COL1, LOW); 
   
  pinMode(LED, OUTPUT);  

  start_timer();
}

void loop(){
  Serial.println("blink!");
  delay(500);
}
