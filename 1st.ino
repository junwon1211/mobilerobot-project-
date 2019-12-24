#include <PWM.h>

#define enA 9  //Motor pulse width modulation pin for (left) wheel
#define in1 8
#define in2 7 

#define enB 6 //Motor pulse width modulation pin for (right) wheel
#define in3 5
#define in4 4

#define SONAR_OUT 2// SR-04 signal OUT
#define SONAR_IN 3// SR-04 signal IN

const long sensor_threshold = 10.5; // %%%%%%%%%%%%changable 11~10
//const long sensor_threshold = 9.3;
//const long sensor_threshold = 10.5;
int motorSpeedA ;
int motorSpeedB ;

void setup()
{
  Serial.begin(9600);
  pinMode(2,OUTPUT); // SR-04 Trig pin
  pinMode(3,INPUT); // SR-04 Echo pin

  pinMode(enA, OUTPUT);  //Pin Settings
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop()
{
  long duration, cm;

  digitalWrite(2,HIGH);  // Trig on
  delayMicroseconds(10); // delay(10us) 
  digitalWrite(2,LOW); // Trig off

  duration = pulseIn(3,HIGH); // Echo pin: HIGH->Low
  cm = microsecondsToCentimeters(duration); // trasformaion of length

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  Serial.println("\n");
  
  if(cm > sensor_threshold){

    digitalWrite(in1, LOW);   // Go forward
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    motorSpeedA = 255;   //fastest speed
    motorSpeedB = 255;

  }else{

    

    motorSpeedA = 0;     //stop
    motorSpeedB = 0;

  }
  
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B

  Serial.print("motorSpeedA&B:");
  Serial.print(motorSpeedA);
  Serial.print(" , ");
  Serial.print(motorSpeedB);
  Serial.println("\n");
  
  delay(10); // delay(0.01s)

}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
