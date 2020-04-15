/*
Radio Controlled Droid.
Copyright 2020 Gabriel Dimitriu

This file is part of Radio Controlled Droid.
This is the receiver part for droid using two sets of propellers and MOS-FET 
transistors.

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
#include <VirtualWire.h>
#define LEFT_MOTOR_PIN 9
#define RIGHT_MOTOR_PIN 10
#define PIN_RX 8
long joystick_x;
long joystick_y;
int joystick_sw;
char inData[20];

#define DEBUG_MODE true
void setup() {
#ifdef DEBUG_MODE
  Serial.begin(9600);
  Serial.println("starting");
#endif
  vw_set_ptt_inverted(true);
  vw_set_rx_pin(PIN_RX); //Set transmitter pin
  vw_setup(400); //Set transmission speed, slower means greater range
  pinMode(LEFT_MOTOR_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN, OUTPUT);
  digitalWrite(LEFT_MOTOR_PIN,LOW);
  digitalWrite(RIGHT_MOTOR_PIN,LOW);
  vw_rx_start();
}


void loop() {
  uint8_t bufLen = 20;
  int power;
  for(int i =0; i< 20; i++) {
    inData[i]='\0';
  }
  if(!vw_get_message(inData,&bufLen)) {
    return;
  }
#ifdef DEBUG_MODE
  Serial.println(inData);
#endif
  if (strcmp(inData,"s") == 0) {
#ifdef DEBUG_MODE
    Serial.println("All on zero");
#endif
    digitalWrite(LEFT_MOTOR_PIN,LOW);
    digitalWrite(RIGHT_MOTOR_PIN,LOW);
  } else if (strlen(inData) > 1) {
    if (inData[0] == 'x') {
      for (unsigned int i = 0 ; i < strlen(inData); i++) {
        inData[i]=inData[i+1];
      }
      power = atoi(inData) - 510;
      power = power/2;
      if (power > 255) {
          power = 255;
      } else if (power < -255) {
          power = -255;
      }
#ifdef DEBUG_MODE
  Serial.print("Left:"); Serial.print(power); Serial.print(" Right:"); Serial.println(power);
#endif
      analogWrite(LEFT_MOTOR_PIN, power);
      analogWrite(RIGHT_MOTOR_PIN, power);
    } else if (inData[0] == 'y') {
      for (unsigned int i = 0 ; i < strlen(inData); i++) {
        inData[i]=inData[i+1];
      }
      power = atoi(inData) - 538;
      power = power/2;
      if (power > 255) {
          power = 255;
      } else if (power < -255) {
          power = -255;
      }
      if (power > 0) { //right
         analogWrite(LEFT_MOTOR_PIN, power);
         digitalWrite(RIGHT_MOTOR_PIN,LOW);
#ifdef DEBUG_MODE
  Serial.print("Left:"); Serial.print(power); Serial.print(" Right:"); Serial.println(0);
#endif
      } else {
        analogWrite(RIGHT_MOTOR_PIN, power);
        digitalWrite(LEFT_MOTOR_PIN,LOW);
#ifdef DEBUG_MODE
  Serial.print("Left:"); Serial.print(0); Serial.print(" Right:"); Serial.println(power);
#endif        
      }
    }
  }
}
