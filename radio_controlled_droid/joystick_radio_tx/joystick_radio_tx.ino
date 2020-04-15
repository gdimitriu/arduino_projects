/*
Radio Controlled Droid.
Copyright 2020 Gabriel Dimitriu

This is part of Radio Controlled Droid.
Joystick Command emiter.

Radio Controlled Droid is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
Radio Controlled Droid is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with Radio Controlled Droid; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
*/
#include <VirtualWire.h> //include library
#include <EnableInterrupt.h>
#define JOYSTICK_X_PIN A3
#define JOYSTICK_Y_PIN A4
#define JOYSTICK_SW_PIN 4
#define PIN_TX 8
long joystick_x;
long joystick_y;
int joystick_sw;
uint8_t sendData[20];
#define NR_READS 50
#define DEBUG_MODE true
volatile boolean fullStopFlag = false;
void setup() {
#ifdef DEBUG_MODE  
  Serial.begin(9600);
#endif
  pinMode(JOYSTICK_SW_PIN, INPUT_PULLUP);
  pinMode(JOYSTICK_X_PIN, INPUT);
  pinMode(JOYSTICK_Y_PIN, INPUT);
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(PIN_TX); //Set transmitter pin
  vw_setup(400); //Set transmission speed, slower means greater range
  enableInterrupt(JOYSTICK_SW_PIN,fullStop,FALLING);
}

void fullStop() {
  fullStopFlag = true;
}

void clearBuffer() {
  for(int i = 0; i < 20; i++) {
   sendData[i]='\0';
  }
}
void loop() {
  long readValue = 0;
  int i;
  for (i = 0; i< NR_READS; i++)
    readValue += analogRead(JOYSTICK_X_PIN);
  readValue = readValue/NR_READS;
  if (labs(readValue - joystick_x) > 2) {
    joystick_x = readValue;
#ifdef DEBUG_MODE    
    Serial.print("x="); Serial.println(joystick_x);
#endif
    clearBuffer();
    sprintf(sendData,"x%d",joystick_x);
    vw_send((uint8_t *)sendData,strlen(sendData));
    vw_wait_tx();
  }
  readValue = 0;
  for (i = 0; i< NR_READS; i++)
    readValue += analogRead(JOYSTICK_Y_PIN);
  readValue = readValue/NR_READS;
  if (labs(readValue - joystick_y) > 2) {
    joystick_y = readValue;
#ifdef DEBUG_MODE
    Serial.print("y="); Serial.println(joystick_y);
#endif
    clearBuffer();
    sprintf(sendData,"y%d",joystick_y);
    vw_send((uint8_t *)sendData,strlen(sendData));
    vw_wait_tx();
  }
  if (fullStopFlag) {
     fullStopFlag=false;
#ifdef DEBUG_MODE    
    Serial.println("Pushed");
#endif
    clearBuffer();
    sprintf(sendData, "s");
    vw_send((uint8_t *)sendData,strlen(sendData));
    vw_wait_tx();
  }
//  delay(20);
}
