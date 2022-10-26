#include "IRremote.h"
//-----( Declare Constants )-----
int receiver = 12;
//-----( Declare objects )-----
IRrecv irrecv(receiver);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'
//-----( Declare Variables )-----


#include <TimerOne.h>           // Avaiable from http://www.arduino.cc/playground/Code/Timer1

volatile int i=0;               // Variable to use as a counter
volatile boolean zero_cross=0;  // Boolean to store a "switch" to tell us if we have crossed zero
int AC_pin = 3;                 // Output to Opto Triac
int dim2 = 0;                   // led control
int dim = 128;                  // Dimming level (0-128)  0 = on, 128 = 0ff
int pas = 10;                   // step for count;
int pas2 = 5;

int freqStep = 75;    // This is the delay-per-brightness step in microseconds.

char incomingByte;  // incoming data from serial 9bluetooth)

void setup() {  // Begin setup

  Serial.begin(9600); // initialization
 
  irrecv.enableIRIn(); // Start the IR receiver (classic remote)

  pinMode(AC_pin, OUTPUT);                          // Set the Triac pin as output
                      
  attachInterrupt(0, zero_cross_detect, RISING);    // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);     
  // Use the TimerOne Library to attach an interrupt

}

void zero_cross_detect() {   
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i=0;
  digitalWrite(AC_pin, LOW);
}                                

// Turn on the TRIAC at the appropriate time
void dim_check() {                  
  if(zero_cross == true) {             
    if(i>=dim) {                    
      digitalWrite(AC_pin, HIGH);  // turn on light      
      i=0;  // reset time step counter                        
      zero_cross=false;    // reset zero cross detection
    }
    else {
      i++;  // increment time step counter                    
    }                               
  }   
}                                     


//-----( Declare User-written Functions )-----
void translateIR() // takes action based on IR code received

{
  switch(results.value)
  {
 
   
case 1086265575:
 
    dim=128;
    break;
   
case 1086294135: 
    dim=120;
    break;

case 1086277815: 
    dim=105;
    break;

case 1086310455: 
    dim=90;
    break;
   
case 1086313005: 
    dim=75;
    break;

case 1086269655: 
    dim=60;
    break;

case 1086302295: 
    dim=45;
    break;

case 1086285975: 
    dim=30;
    break;

case 1086283935: 
    dim=15;
    break; 
   
case 1086318615: 
    dim=00;
    break;  


  case 1086292095: 
    {
    if (dim<127) 
   {
    dim = dim + pas;
    if (dim>127)
    {
     dim=128;
    }
    }
    }
    break;

  case 1086259455: 
    {
      {
  if (dim>5) 
  {
     dim = dim - pas;
  if (dim<0)
    {
      dim=0;  // in vechiul sketch era 1
    }
   }
   }
   }
    break;


   case 1086308415: 
    {
    if (dim<127) 
   {
    dim = dim + pas2;
    if (dim>127)
    {
     dim=128;
    }
    }
    }
    break;

  case 1086275775: 
    {
      {
  if (dim>5) 
  {
     dim = dim - pas2;
  if (dim<0)
    {
      dim=0;  // in vechiul sketch era 1
    }
   }
   }
   }
    break;
  
    default:
    Serial.println(results.value);
  }

}


void loop() { 

// remote
   if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); // receive the next value
  } 

 delay (100);
}
