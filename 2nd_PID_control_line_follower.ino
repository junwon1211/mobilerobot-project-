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

const long sensor_threshold = 100.0; 
const long sensor_init_value = 300.0; // need to be practiced

int motorSpeedA = 0;
int motorSpeedB = 0;
const int Max_speed = 80;


int integral = 0;
int proportional = 0;
int derivative = 0;
int last_proportional = 0;
int error_value = 0;
int error_value_to_speed = 0;
long right = 0.0;
long left = 0.0;

const double Kp = 1;
const double Ki = 9.0;
const double Kd = 0.2; 

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
  digitalWrite(in1, LOW);   
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  calc_rotoation();   // sensor feedback control and calibration of motor_speed  
    
  analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
  analogWrite(enB, motorSpeedB); // Send PWM signal to motor B

  Serial.print("motorSpeedA&B:");
  Serial.print(motorSpeedA);
  Serial.print(" , ");
  Serial.print(motorSpeedB);
  Serial.println("\n");
  
  delay(100); // delay(0.01s)

}

long sensor_calc(long right, long left)
{
  long location=(1000.0*(left*1.0+right*2.0))/(left+right); //sensor calibration
    
  return location;
}

long init_location(long sensor_init_value)
{
  long init_loca=(1000.0*(sensor_init_value*1.0+sensor_init_value*2.0))/(sensor_init_value); 
  
  return init_loca;
}

void pid_calc()
{ 

proportional = int(init_location(sensor_init_value) - sensor_calc(right, left));

integral = integral + proportional;
derivative = proportional - last_proportional;
last_proportional = proportional;

error_value = int(proportional * Kp + integral * Ki + derivative * Kd);          //PID controller
// error_value_to_speed = map(error_value,0,sensor_threshold-setpoint,0,255);      // Transitting Error vaule of position to speed value (max 8cm->v:255 0cm->v:0)

}

void calc_rotoation()
{ 
       if (right >= sensor_threshold && left >= sensor_threshold)
 {
    motorSpeedA = Max_speed;
    motorSpeedB = Max_speed;
    
    
 }else if ( right > sensor_threshold && left < sensor_threshold)     // right curve
 {
  
    motorSpeedA =  Max_speed;     
    motorSpeedB =  Max_speed-error_value;
    
 }else if(right < sensor_threshold && left > sensor_threshold)  // left curve
 {
    motorSpeedA =  Max_speed-error_value;
    motorSpeedB =  Max_speed;     

 }else if(right <= sensor_threshold && left <= sensor_threshold)  
 {
  
    motorSpeedA = 0;
    motorSpeedB = 0;
    
 }
}
