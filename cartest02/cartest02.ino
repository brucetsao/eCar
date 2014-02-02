#include <IRremote.h>
//　---- ddefine IR led use
#define RECV_PIN  12
#define LED_PIN  10
//------define L298N use
const int motor1 = 7;
const int motor2 = 6;
const int motor3 = 5;
const int motor4 = 4;


//　---- ddefine IR led Object use
IRrecv irrecv(RECV_PIN);
decode_results results;
long IR_key = -1;

void initall()
{
  pinMode(LED_PIN,OUTPUT);   // init IR Led Display
  irrecv.enableIRIn(); // Start the receiver
  digitalWrite(LED_PIN,LOW);     // init IR Led Display off
//----- motor set  ----
  pinMode(motor1,OUTPUT);   // init Car pin for output 
  pinMode(motor2,OUTPUT);   // init Car pin for output 
  pinMode(motor3,OUTPUT);   // init Car pin for output 
  pinMode(motor4,OUTPUT);   // init Car pin for output 
  carMiddle();
  carStop();
  
}

void setup()
{
  Serial.begin(9600);    // init serial speed
  Serial.println("Program Start here" );    // Show program start status
  initall();
}


void loop() {
  
   IR_key = IRcheck() ;    // Check IR Receiver
   
      if ((IR_key == (long)(-1)) or (IR_key == (long)(-2)))
      {
        // no IR Sender Signal
          digitalWrite(LED_PIN,LOW);     // IR Led Display off
      }
      else
      { 
        // Receive IR Sender Signal
        digitalWrite(LED_PIN,HIGH);     // IR Led Display on
        Serial.println(IR_key);
        IRControlCar((int)IR_key);
      }
  delay(400);
}
void IRControlCar(int ctl)
{
switch (ctl)
  {
   case 2 :   // Car go forward
     carForward() ;   
       break ;

   case 8 :   // Car go backward
     carBackward() ;   
       break ;
       
   case 6 :   // Car go right
     carRight() ;   
       break ;
       
   case 4 :   // Car go left
     carLeft() ;   
       break ;
       
   case 5 :   // Car go Stop
     carStop() ;   
       break ;
       
   case 1 :   // Car go strait
     carMiddle() ;   
       break ;
       
  }
    
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

void carForward()
{
  digitalWrite(motor1,HIGH);
  digitalWrite(motor2,LOW);
}

void carBackward()
{
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,HIGH);
}

void carRight()
{
  digitalWrite(motor3,HIGH);
  digitalWrite(motor4,LOW);
}

void carLeft()
{
  digitalWrite(motor3,LOW);
  digitalWrite(motor4,HIGH);
}

void carMiddle()
{
  digitalWrite(motor3,LOW);
  digitalWrite(motor4,LOW);
}

void carStop()
{
  digitalWrite(motor1,LOW);
  digitalWrite(motor2,LOW);
}


