#include<IRremote.h>
const int RECV_PIN=8;
IRrecv irrecv(RECV_PIN);
decode_results results;


#define load1 A5
#define load2 A4
#define load3 A3
#define load4 A2
#define load5 A1
#define load6 A0
#define load7 A3
#define load3 A3


int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,n=0;

void setup()
{
  Serial.begin(9600);
  
  pinMode(load1, OUTPUT);
  pinMode(load2, OUTPUT);
  pinMode(load3, OUTPUT);
  //digitalWrite(13,HIGH);
  
 
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  
}

void loop() 
{
  if (irrecv.decode(&results)) 
   {
     Serial.println(results.value,HEX);
     delay(100);
     
      
     if(results.value==0x1FE50AF)
     {
        i++;
        int x=i%2;
        digitalWrite(load1, x);
     }
    
     else if(results.value==0x1FEE01F)    

     {
        j++;
        int x=j%2;
        digitalWrite(load2, x);
     }
   
     if(results.value==0x1FE9867)
     {
        k++;
        int x=k%2;
        digitalWrite(load3, x);
        
       }
       
        if(results.value==0x6A68351E)
       {
        n++;
        int x=n%2;
        digitalWrite(load2, x);
        digitalWrite(load1,x);
        digitalWrite(load3,x);

       }
     irrecv.resume(); // Receive the next value
     //delay(100);
   }
}
