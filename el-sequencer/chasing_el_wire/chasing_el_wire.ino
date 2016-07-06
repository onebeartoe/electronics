/**
 * This demontration of cchasing_el_wire/
Latest commit 8e2eff1  on Jan 21￼ onebeartoe This is the code for flowing/chasing EL wire, of the 3 channel variety.
..   
chasing_el_wire.ino hchasing_el_wire/
Latest commit 8e2eff1  on Jan 21￼ onebeartoe This is the code for flowing/chasing EL wire, of the 3 channel variety.
..    
chasing_el_wire.ino asing EL wire uses the following hardware compontents:
 *
 *      microcontroller: https://www.sparkfun.com/products/12781
 *              pigtail: https://www.sparkfun.com/products/12934
 *      3 EL wire stand: https://www.sparkfun.com/products/12931 (or similar)
 *    
 *      Dance magic dance!
 *    
 * Wiring
 * 
 *    wire the JST connector with yellow and white wires to slot F on the EL Sequencer
 *    wire the JST connector with a black wire to slot G on the EL Sequencer
 *    wire the JST connector with a red wire to slot H on the EL Sequencer
 */

#define MODES_ALL_ON 1
#define MODES_MOTION_DETECTED 2
#define MODES_RANDOM 3

#define A  2
#define B  3
#define C  4
#define D  5
#define E  6
#define FF  7
#define G  8
#define H  9

int currentMode = MODES_ALL_ON;

unsigned long previousMillis = 0;        // will store last time LED was updated

const long interval = 60;//300;//100;//500;           // interval at which to blink (milliseconds)

int wireCount = 3;
int currentElWire = 1;

boolean wireStati [] = {0,0,0};

void loop()
{   
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) 
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    for(int i=0; i < wireCount; i++)
    {
       if(i == currentElWire-1)
       {
          wireStati[i] = true;
       }
       else
       {
          wireStati[i] = false;
       }
    }

     digitalWrite(FF, wireStati[0]); 
     digitalWrite(G, wireStati[1]); 
     digitalWrite(H, wireStati[2]);    

     currentElWire++;
     if(currentElWire > wireCount)
     {
//TODO: have this variable be zero based      
        currentElWire = 1;
     }
  }
}

void setup() 
{
  pinMode(A0, INPUT);
  randomSeed( analogRead(A5) );

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(FF, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(H, OUTPUT);
  
  digitalWrite(A, HIGH); 
  digitalWrite(B, HIGH); 
  digitalWrite(C, HIGH); 
  digitalWrite(D, HIGH); 
  digitalWrite(E, HIGH);  
  
  // initialize serial communication:
  Serial.begin(9600);
}
