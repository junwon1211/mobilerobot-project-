#include <IRremote.h>
#include <Servo.h> // Timer1 pwm signal is unavailable   (9,10->timer1 3,11->timer2 5,6->timer0) 
#include <PWM.h>

#define enB 5 //Motor pulse width modulation pin for (left) wheel
#define in4 8
#define in3 7 

#define enA 6 //Motor pulse width modulation pin for (right) wheel
#define in2 4
#define in1 9

#define receiver 11 // IRreciever

#define m_f 3  // pin for 1st link
#define m_s 10 // pin for 2nd link

Servo mya;  // description of Servo
Servo myb;

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

int motorSpeedA;          
int motorSpeedB;
const int Max_speed = 60;
const int turn_speed  = 50;

const int grip_angle = 10;
const int ungrip_angle = 40;


void forward(){Serial.println("go forward\n\n"); 
     digitalWrite(in1, LOW);   
     digitalWrite(in2, HIGH);
     digitalWrite(in3, LOW);
     digitalWrite(in4, HIGH);
    motorSpeedA = Max_speed;  //l
    motorSpeedB = Max_speed;  //r
     Serial.println("forward");
      
     //delay(100);
     }
     
void back(){Serial.println("back\n\n"); 
     digitalWrite(in2, LOW);   
     digitalWrite(in1, HIGH);
     digitalWrite(in4, LOW);
     digitalWrite(in3, HIGH);
    motorSpeedA = Max_speed;  //l
    motorSpeedB = Max_speed;  //r
  
     Serial.println("back");
     }
     
void left(){  Serial.println("turn left\n\n"); 
      digitalWrite(in1, LOW);   
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    motorSpeedA = turn_speed;  //l
    motorSpeedB = turn_speed;  //r

     Serial.println("left");
     }
     
void right(){ Serial.println("turn right\n\n"); 
     digitalWrite(in3, LOW);   
     digitalWrite(in4, HIGH);
     digitalWrite(in1, HIGH);
     digitalWrite(in2, LOW);
    motorSpeedA = turn_speed;  //l
    motorSpeedB = turn_speed;  //r
     
     Serial.println("right");
     }
     
void fast_stop(){
  Serial.println("stop\n\n"); 
     digitalWrite(in1, LOW);   
     digitalWrite(in2, LOW);
     digitalWrite(in4, LOW);
     digitalWrite(in3, LOW);
    motorSpeedA = 0;  
    motorSpeedB = 0; 

     Serial.println("stop");
}

void grip(){  
    myb.write(10);
    Serial.println("grip");        
    
  }
  
void ungrip(){
    myb.write(180);   
    Serial.println("ungrip"); 
  }
  
void up(){        
  
  mya.write(40);  
  
  Serial.println("up");
  }
  
void down(){    
  
  mya.write(170);  

  Serial.println("down");
  }
  

void init_manipulator(){
  
  mya.write(40);
  myb.write(180);

}

void translateIR() {

  switch(results.value)

  {

  case 0xFFA25D: Serial.println("POWER"); break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); break;
  case 0xFF629D: Serial.println("VOL+"); break;
  case 0xFF22DD: Serial.println("FAST BACK"); ungrip();   break;
  case 0xFF02FD: Serial.println("PAUSE");    break;
  case 0xFFC23D: Serial.println("FAST FORWARD"); grip();  break;
  case 0xFFE01F: Serial.println("DOWN");  down();  break;
  case 0xFFA857: Serial.println("VOL-");    break;
  case 0xFF906F: Serial.println("UP");   up(); break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  case 0xFF6897: Serial.println("0");    break;

  
  case 0xFF30CF: Serial.println("1\n");    
    
   
  break;

  case 0xFF18E7: Serial.println("2\n");   
     
   
   forward();
   break;

  case 0xFF7A85: Serial.println("3\n");   
     
  break;

  case 0xFF10EF: Serial.println("4\n");  
     right();
   break;

  case 0xFF38C7: Serial.println("5\n");  
    fast_stop();
   break;


  case 0xFF5AA5: Serial.println("6");   
    left();
  break;  

  case 0xFF42BD: Serial.println("7");  
  
  break;

  case 0xFF4AB5: Serial.println("8");   
  back();
  break;

  case 0xFF52AD: 
  ungrip();
  Serial.println("9");    break;

  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button  ");
     fast_stop();
     break;

   delay(1500);
  }
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enB, motorSpeedB); // Send PWM signal to motor B

  irrecv.resume(); 

} 

void setup()   
{
  pinMode(enA, OUTPUT);  //Pin Settings
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);   // Serial start in 9600 channel
  irrecv.enableIRIn();
  mya.attach(3);  // attaches the servo on pin to the servo object
  myb.attach(10);
}


void loop()  
{
  Serial.println(results.value, HEX); 
  if (irrecv.decode(&results))   // decode the IRsignal in HEX

  {
    translateIR();
     
    irrecv.resume();   //initalize the IRreciever
  }  
}
