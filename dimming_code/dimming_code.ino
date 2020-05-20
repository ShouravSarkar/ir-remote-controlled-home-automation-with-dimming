#include "IRremote.h"

int receiver = 12; 
IRrecv irrecv(receiver);           
decode_results results;            



#include <TimerOne.h>           
volatile int i=0,j=0;               // Variable to use as a counter
volatile boolean zero_cross=0,zero_cross_2=0;  // Boolean to store a "switch" to tell us if we have crossed zero
int AC_pin = 5;                 // Output to Opto Triac
int AC_pin2 = 6;

int dim2 = 128;                   // led control
int dim = 128;                  // Dimming level (0-128)  0 = on, 128 = 0ff                  
int freqStep = 75;    // This is the delay-per-brightness step in microseconds.

void setup() {   
  irrecv.enableIRIn(); // Start the IR receiver (classic remote)
  pinMode(AC_pin, OUTPUT);                          // Set the Triac pin as output
  pinMode(AC_pin2, OUTPUT);
  attachInterrupt(0, zero_cross_detect, RISING);    // Attach an Interupt to Pin 2 (interupt 0) for Zero Cross Detection
  attachInterrupt(1, zero_cross_detect_2, RISING);
  Timer1.initialize(freqStep);                      // Initialize TimerOne library for the freq we need
  Timer1.attachInterrupt(dim_check, freqStep);      
}

void zero_cross_detect() 
{    
  zero_cross = true;               // set the boolean to true to tell our dimming function that a zero cross has occured
  i=0;

  digitalWrite(AC_pin, LOW);

}
void zero_cross_detect_2() 
{    
  zero_cross_2 = true;               // set the boolean to true to tell our dimming function that a zero cross has occured

  j=0;
  
  digitalWrite(AC_pin2, LOW);
}                                      
// Turn on the TRIAC at the appropriate time

void dim_check() 
{                   
  if(zero_cross == true) {              
    if(i>=dim) {                     
      digitalWrite(AC_pin, HIGH);  // turn on light       
      i=0;  // reset time step counter                         
      //zero_cross=false;    // reset zero cross detection
    } 
  else {
      i++;  // increment time step counter                     
      }
     }
  if(zero_cross_2 == true) {              
    if(j>=dim2) {                     
      digitalWrite(AC_pin2, HIGH);  // turn on light       
      j=0;  // reset time step counter                         
     // zero_cross=false;    // reset zero cross detection
    } 
  else {
      j++;  // increment time step counter                     
      }
     }


}                                      


void translateIR() // takes action based on IR code received
{
  switch(results.value)
  {
  case 33464415:  
    {
   
    if (dim<127)  
   {
    dim = dim + 8;
    if (dim>127) 
    {
      dim=128; // in vechiul sketch era 127
    }
    }}
    
    break;

  case 33448095:  
    {
    
      {
  if (dim>5)  
  {
     dim = dim - 8;
  if (dim<0) 
    {
      dim=0;  // in vechiul sketch era 1
    } }}}
    break;
  
  
  
  case 33439935:  
    {
   
    if (dim2<127)  
   {
    dim2 = dim2 + 8;
    if (dim2>127) 
    {
      dim2=128; // in vechiul sketch era 127
    }
    }}
    
    break;

  case 33472575:  
    {
    
      {
  if (dim2>5)  
  {
     dim2 = dim2 - 8;
  if (dim2<0) 
    {
      dim2=0;  // in vechiul sketch era 1
    } }}}
    break;
  }}
  
void loop() {  
 if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  

}
