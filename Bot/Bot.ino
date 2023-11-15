#include <Wire.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include "define_nano.h"
#include <PID_v1.h>
#include <Servo.h>
/////////////////////////////////////////////////////////
double RP, Output;
double Setpoint = 0;
// P 50 I 0 D 20
double Kp=80, Ki=0, Kd=10;
PID pid(&RP, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

/////////////////////////////////////////////////////////
Servo servo;
/////////////////////////////////////////////////////////
int speed = 127;//127
/////////////////////////////////////////////////////////

int sensorValues[] = {0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t buttonValues[] = {0,0,0,0};


int state = 1;
int white_value = 0;
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
/*  ReadLine();
  //Sensors 1-3
  if(sensorLine[0]==0){
    RP = -3;
  }
  else if(sensorLine[1]==0){
    RP = -2;
  }
  else if(sensorLine[2]==0){
    RP = -1;
  }
  //Sensors 4-6
  else if(sensorLine[5]==1){
    RP = 3;
  }
  else if(sensorLine[4]==1){
    RP = 2;
  }
  else if(sensorLine[3]==1){
    RP = 1;
  }
  else{
    RP = 0;
  }
  
  //Debug("Normal");
  pid.Compute();
  speedA = speed-Output;
  speedB = speed+Output;
  if(RP == 0){
    speedA = speed;
    speedB = speed;  
  }
  
  //Debug("PID");
  //A
  digitalWrite(INA1,HIGH);
  digitalWrite(INA2,LOW);
  analogWrite(ENA,speedA);
  //B
  digitalWrite(INB1,HIGH);
  digitalWrite(INB2,LOW);
  analogWrite(ENB,speedB);
  */
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,HIGH);
  analogWrite(ENA,255);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,HIGH);
  analogWrite(ENB,255);
  delay(1000);
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,HIGH);
  analogWrite(ENA,255);
  digitalWrite(INB1,HIGH);
  digitalWrite(INB2,LOW);
  analogWrite(ENB,255);
  delay(500);
  ReadSensors();
  for(int x=0;x<12;x++){
  Serial.print(sensorValues[x]);
  Serial.print(" ");}
  Serial.println("");
  //servo.write(0);
  delay(30);
}
