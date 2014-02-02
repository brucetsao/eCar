
#include <IRremote.h>


#define RECV_PIN  12
#define LED_PIN  10



IRrecv irrecv(RECV_PIN);


decode_results results;
long IR_key = -1;


void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT); 
  irrecv.enableIRIn(); // Start the receiver
  digitalWrite(LED_PIN,LOW); 
  Serial.println("Program Start here" );

}


void loop() {
  
   IR_key = IRcheck() ;
   
      if ((IR_key == (long)(-1)) or (IR_key == (long)(-2)))
      {
          digitalWrite(LED_PIN,LOW); 
      }
      else
      { 
        digitalWrite(LED_PIN,HIGH); 
        Serial.println(IR_key);
      }
  delay(400);
}

long  IRcheck()
{
  // irrecv.enableIRIn(); // Start the receiver
  long tmp = -2 ;
    if (irrecv.decode(&results)) {
  //  Serial.print("recdeive data is :");
  //  Serial.println(results.value);
 //   dump(&results);
       tmp = IRencode(&results) ;
    irrecv.resume(); // Receive the next value
    return (tmp) ;
   
  }
  else
  {
    irrecv.resume(); // Receive the next value
    return (tmp);
  }
} 
long IRencode(decode_results *code)
{
  long encodeno = -1 ;
  long   cc = code->value ; 
  switch (cc)
  {
   case 16738455 :   // for button "0" code
     encodeno = 0 ;   
       break ;
       
   case 16724175 :    // for button "1" code
     encodeno = 1 ;
       break ;
       
   case 16718055 :    // for button "2" code
     encodeno = 2 ;
       break ;
       
   case 16743045 :    // for button "3" code
     encodeno = 3 ;
       break ;
       
   case 16716015 :    // for button "4" code
     encodeno = 4 ;
       break ;
   case 16726215 :    // for button "5" code
     encodeno = 5 ;
       break ;
   case 16734885 :    // for button "6" code
     encodeno = 6 ;
       break ;
   case 16728765 :    // for button "7" code
     encodeno = 7 ;
       break ;
   case 16730805 :    // for button "8" code
     encodeno = 8 ;
       break ;
   case 16732845 :    // for button "9" code
     encodeno = 9 ;
       break ;
   case 16748655 :    // for button "EQ" code for set timer
     encodeno = 11 ;
       break ;
   case 16754775 :    // for button "+" code for increase time 30 minutes
     encodeno = 12 ;
       break ;
   case 16769055 :    // for button "-" code code for decrease time 30 minutes
     encodeno = 13 ;
       break ;
   case 16736925 :    // for button "CH" code code for show 　溫度與濕度
     encodeno = 20 ;
       break ;
  default:
     encodeno = cc ;
  
  }
  return (encodeno) ;
  
} 


