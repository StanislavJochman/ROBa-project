/*
Attiny84 8mhz only
*/
#define __AVR_ATtiny841__

#include <Arduino.h>

#if defined(__AVR_ATtiny841__)
#define F_CPU 8000000                          // clock speed: 16MHz (external crystal) - modify as needed
#include "WireS.h"                              // I2C library for ATtiny841 (and other modern ATtinys)
#else
#define F_CPU 8000000                          // clock speed: 20MHz (external crystal) - modify as needed
#include "TinyWireS.h"                          // I2C library for ATtiny84A (and other older ATtinys)
#endif       


//0x11 or 0x12
uint8_t address = 0x12;
#define S1 A7
#define S2 A5
#define S3 A3 
#define S4 A2
#define S5 A1
#define S6 A0
#define button1 1
#define button2 2
#define interrupt 0

int s1;
int s2;
int s3;
int s4;
int s5;
int s6;
uint8_t b1;
uint8_t b2;

void setup(){
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(interrupt,OUTPUT);
  TinyWireS.begin(address);
  TinyWireS.onRequest(requestEvent);
}
void loop()
  {
    b1 = digitalRead(button1);
    b2 = digitalRead(button2);
    s1 = analogRead(S1);
    s2 = analogRead(S2);
    s3 = analogRead(S3);
    s4 = analogRead(S4);
    s5 = analogRead(S5);
    s6 = analogRead(S6);
  }
void requestEvent()
{
  TinyWireS.write(b1);
  TinyWireS.write(b2);
  TinyWireS.write(s1);
  TinyWireS.write((s1 >> 8));
  TinyWireS.write(s2);
  TinyWireS.write((s2 >> 8));
  TinyWireS.write(s3);
  TinyWireS.write((s3 >> 8));
  TinyWireS.write(s4);
  TinyWireS.write((s4 >> 8));
  TinyWireS.write(s5);
  TinyWireS.write((s5 >> 8));
  TinyWireS.write(s6);
  TinyWireS.write((s6 >> 8));
  
}
