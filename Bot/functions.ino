#include "define.h"

bool ButtonState(){
  bool value = digitalRead(button);
  return !value;
}
void ReadSensors(){
  Wire.requestFrom(0x11, 14);
  buttonValues[2] = !Wire.read();
  buttonValues[3] = !Wire.read();
  
  sensorValues[0] = (Wire.read() | Wire.read() << 8);
  sensorValues[1] = (Wire.read() | Wire.read() << 8);
  sensorValues[2] = (Wire.read() | Wire.read() << 8);
  sensorValues[3] = (Wire.read() | Wire.read() << 8);
  sensorValues[4] = (Wire.read() | Wire.read() << 8);
  sensorValues[5] = (Wire.read() | Wire.read() << 8);
  Wire.requestFrom(0x12, 14);
  buttonValues[0] = !Wire.read();
  buttonValues[1] = !Wire.read();
  
  sensorValues[6] = (Wire.read() | Wire.read() << 8);
  sensorValues[7] = (Wire.read() | Wire.read() << 8);
  sensorValues[8] = (Wire.read() | Wire.read() << 8);
  sensorValues[9] = (Wire.read() | Wire.read() << 8);
  sensorValues[10] = (Wire.read() | Wire.read() << 8);
  sensorValues[11] = (Wire.read() | Wire.read() << 8);
}
int sumWindow(int index,int size=3){
  int result = 0;
  for (int i=index;i<index+size;i++){
    result += sensorValues[i];
  }
  return result;
}
int calculateLine(){
  if(sumWindow(0,12) == 0){
    return 0;
  }
  int range = 12-sensor_window_size;
  int max = 0;
  int max_index = -1;
  for (int i=0;i<range;i++){
    int value = sumWindow(i,sensor_window_size);
    if (value >= max){
      max = value;
      max_index = i;
    }
  }
  return int(map(max_index,0,range,0,range));
}

void digitizeSensors(int treashold){
  for (int i=0;i<12;i++){
    if (sensorValues[i] < treashold){
      sensorValues[i] = 0;
    }
    else{
      sensorValues[i] = 1;
    }
  }
}
int calibrateSensors(){
  ReadSensors();
  int treashold = 0;
  for (int i=0;i<6;i++){
    if(sensorValues[i] > sensorValues[11-i]){
        treashold += sensorValues[i] - sensorValues[11-i];
    }
    else{
        treashold += sensorValues[11-i] - sensorValues[i];
    }
  }
  return 1023-treashold/6;
}
void RunMotor(String motor,int speed){
  if (motor == "A"){
      if(speed > 0){
        digitalWrite(INA1,LOW);
        digitalWrite(INA2,HIGH);
      }
      else{
        digitalWrite(INA1,HIGH);
        digitalWrite(INA2,LOW);
      }
      analogWrite(ENA,abs(speed));
    }
    else if(motor == "B"){
      if(speed > 0){
        digitalWrite(INB1,LOW);
        digitalWrite(INB2,HIGH);
      }
      else{
        digitalWrite(INB1,HIGH);
        digitalWrite(INB2,LOW);
      }
      analogWrite(ENB,abs(speed));
    }
    else if(motor == "AB"){
      if(speed > 0){
        digitalWrite(INA1,LOW);
        digitalWrite(INA2,HIGH);
        digitalWrite(INB1,LOW);
        digitalWrite(INB2,HIGH);
      }
      else{
        digitalWrite(INA1,HIGH);
        digitalWrite(INA2,LOW);
        digitalWrite(INB1,HIGH);
        digitalWrite(INB2,LOW);
        
      }
      analogWrite(ENA,abs(speed));
      analogWrite(ENB,abs(speed));
    }
}