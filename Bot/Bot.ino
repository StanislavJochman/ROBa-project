#include <Wire.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include "define_nano.h"
#include <PID_v1.h>
#include <Servo.h>
/////////////////////////////////////////////////////////
double RP, Output;
double Setpoint = 0;

double Kp=60, Ki=0, Kd=5;
PID pid(&RP, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

/////////////////////////////////////////////////////////
Servo servo;
/////////////////////////////////////////////////////////
int speed = 127;//127
/////////////////////////////////////////////////////////

int sensorValues[] = {0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t buttonValues[] = {0,0,0,0};

int state = 1;
int treashold = 0;
int value = 0;
int speedA;
int speedB;
/////////////////////////////////////////////////////////
long pulseA = 0;
long pulseB = 0;
long gyro_angle;
long gyro_angle_start;
/////////////////////////////////////////////////////////
void setup() {
  servo.attach(servo_pin);
  Serial.begin(115200);
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-speed,speed);
  Wire.begin();
  pinMode(button,INPUT_PULLUP);
  pinMode(INA1,OUTPUT);
  pinMode(INA2,OUTPUT);
  pinMode(INB1,OUTPUT);
  pinMode(INB2,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
/////////////////////////////////////////////////////////
//  Calibrate_Line(30);
  while(true){
    if(buttonValues[0]==1){
      break;
    }
    else{
      ReadSensors();
    }
  }
  treashold = calibrateSensors();
  delay(500);
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,HIGH);
  analogWrite(ENA,35);
  analogWrite(ENB,35);
  delay(450);
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  servo.write(90);
}

void loop() {  
  ReadSensors();
  pid.Compute();
  digitizeSensors(treashold);
  RP = calculateLine();
  speedA = speed-Output;
  speedB = speed+Output;
  Serial.print(speedA);
  Serial.print("  ");
  Serial.print(speedB);
  Serial.print("  ");
  Serial.print(RP);
  Serial.print("  ");
  Serial.println(Output);
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB1,HIGH);
  digitalWrite(INB2,LOW);
  analogWrite(ENA,speedA);
  analogWrite(ENB,speedB);

}
