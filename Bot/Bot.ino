#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Wire.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include "define_nano.h"
#include <PID_v1.h>

#include <ros.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/String.h>
/////////////////////////////////////////////////////////

int speed = 120;//127
/////////////////////////////////////////////////////////

int sensorValues[] = {0,0,0,0,0,0,0,0,0,0,0,0};
int buttonValues[] = {0,0,0,0};

int state = 1;
int treashold = 0;
int value = 0;
int speedA;
int speedB;
/////////////////////////////////////////////////////////

int RP = 0;
int Output = 0;

ros::NodeHandle  nh;

std_msgs::UInt8 int_msg;
ros::Publisher chatter("chatter", &int_msg);


void motor_cb(const std_msgs::UInt8& cmd_msg){
  Output = cmd_msg.data-120;
}

ros::Subscriber<std_msgs::UInt8> sub("writer", motor_cb);

/////////////////////////////////////////////////////////
void setup() {
  Wire.begin();
  /////////////////////////////////////////////////////////
  /*while(true){
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
  analogWrite(ENB,0);*/
  treashold = 995;
////////////////////////////////////////////////////////
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
  pinMode(button,INPUT_PULLUP);
  pinMode(INA1,OUTPUT);
  pinMode(INA2,OUTPUT);
  pinMode(INB1,OUTPUT);
  pinMode(INB2,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}

void loop() {  
  ReadSensors();
  digitizeSensors(treashold);
  RP = calculateLine();
  speedA = speed+Output;
  speedB = speed-Output;

  digitalWrite(INA1,LOW);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB1,HIGH);
  digitalWrite(INB2,LOW);
  analogWrite(ENA,speedA);
  analogWrite(ENB,speedB);
  int_msg.data = RP;
  chatter.publish( &int_msg );

  nh.spinOnce();
  delay(1);

}
