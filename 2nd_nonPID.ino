
#include <PWM.h> /// nonpid

#define enA 9  //Motor pulse width modulation pin for (left) wheel
#define in1 8
#define in2 7 

#define enB 6 //Motor pulse width modulation pin for (right) wheel
#define in3 5
#define in4 4

//Photoreflector setup
#define Sensor_R A0
#define Sensor_L A1

const int sensor_threshold = 100;                                                                                                                                                                                                                                                                                                                                                                                                                ;  //100>sensor:white 
int motorSpeedA = 0;
int motorSpeedB = 0;
const int Max_speed = 50;


int error_value_to_speed = 0;
long right = 0;
long left = 0;

// const double Kp = 1;
// const double Ki = 3;
// const double Kd = 0.2; 

void setup()
{
  Serial.begin(9600);


  pinMode(enA, OUTPUT);  //Pin Settings
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop()
{
  
  right=analogRead(A0);  
  left =analogRead(A1);
  
  Serial.print(" right:");
  Serial.print(right);
  Serial.print(" left:");
  Serial.println(left);
  Serial.println("\n");
  
  calc_rotoation();   // sensor feedback control and calibration of motor_speed  
    
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B

  Serial.print(" motorSpeed_left(A): ");
  Serial.print(motorSpeedA);
  Serial.print(" motorSpeed_right(B) ");
  Serial.print(motorSpeedB);
  Serial.println("\n\n");
  
  delay(10); // delay(0.01s)

}

void calc_rotoation()
{ 
       if (right <= sensor_threshold && left <= sensor_threshold)
 {
     digitalWrite(in1, LOW);   
     digitalWrite(in2, HIGH);
     digitalWrite(in3, LOW);
     digitalWrite(in4, HIGH);
    motorSpeedA = Max_speed;  //l
    motorSpeedB = Max_speed;  //r
    
 }else if (right > sensor_threshold && left < sensor_threshold)     // right curve
 {
      digitalWrite(in3, LOW);   
      digitalWrite(in4, HIGH);
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      motorSpeedA = 255;  //l
    motorSpeedB = 255; 
     delay(500);
    
    
 }else if(right < sensor_threshold && left > sensor_threshold)  // left curve
 {  
      digitalWrite(in1, LOW);   
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
        motorSpeedA = 255;  //l
    motorSpeedB = 255; 
     delay(500);

 }else if(right >= sensor_threshold && left >= sensor_threshold)  
 {
 
stop();
 }
}

void stop()
{
   digitalWrite(in1, LOW);   
     digitalWrite(in2, HIGH);
     digitalWrite(in3, LOW);
     digitalWrite(in4, HIGH);
    motorSpeedA = 50;  //l
    motorSpeedB = 50;  //r
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
    delay(1700);
    motorSpeedA = 0;  //l
    motorSpeedB = 0;  //
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
   
    delay(10000);
    
  }
