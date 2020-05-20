#include<IRremote.h>
const int RECV_PIN=8;
IRrecv irrecv(RECV_PIN);
decode_results results;


#define Fan 9
#define Light 10
#define TV 4

int i=0,j=0,k=0,n=0;

void setup()
{
  Serial.begin(9600);
  
  pinMode(Fan, OUTPUT);
  pinMode(Light, OUTPUT);
  pinMode(TV, OUTPUT);
  //digitalWrite(13,HIGH);
  
 
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  
}

void loop() 
{
  if (irrecv.decode(&results)) 
   {
     Serial.println(results.value,DEC);
     delay(100);
     lcd.setCursor(0,0);
     lcd.print("Fan   Light  TV"); 
     if(results.value==0x1FE50AF)
     {
        i++;
        int x=i%2;
        digitalWrite(Fan, x);
        lcd.setCursor(0,1);
        if(x)
        lcd.print("ON  ");
        else
        lcd.print("OFF ");
       // delay(200);
     }
    
     else if(results.value==0x1FEE01F)    //  key 1 

     {
        j++;
        int x=j%2;
        digitalWrite(Light, x);
        lcd.setCursor(6,1);
        if(x)
        lcd.print("ON   ");
        else
        lcd.print("OFF  ");
       // delay(200);
     }
   
     if(results.value==0x1FE9867)
     {
        k++;
        int x=k%2;
        digitalWrite(TV, x);
        lcd.setCursor(13,1);
        if(x)
        lcd.print("ON ");
        else
        lcd.print("OFF");
       // delay(200);
       }
       
        if(results.value==0x6A68351E)
       {
        n++;
        int x=n%2;
        digitalWrite(TV, x);
        digitalWrite(Fan,x);
        digitalWrite(Light,x);
        lcd.setCursor(0,1);
        if(x)
        lcd.print("ON     ON    ON ");
        else
        lcd.print("OFF    OFF   OFF");
        //delay(200);
       }
     irrecv.resume(); // Receive the next value
     //delay(100);
   }
}
