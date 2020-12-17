/*
 * SX1509 with four leds using analog write (PWM).
 * Copyright 2019 Gabriel Dimitriu

 * This file is part of Arduino Projects

 * Arduino Projects is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * Arduino Projects is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with Arduino Projects; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
*/
#include<Wire.h>
#include <SparkFunSX1509.h>

#define FIRST_LED_PIN 0
#define SECOND_LED_PIN 2
#define THIRD_LED_PIN 5
#define FOURTH_LED_PIN 7
SX1509 extender;

void setup() {
  extender.begin(0x3E);
  extender.clock(INTERNAL_CLOCK_2MHZ,7);
  extender.pinMode(FIRST_LED_PIN, ANALOG_OUTPUT);
  extender.pinMode(SECOND_LED_PIN, ANALOG_OUTPUT);
  extender.pinMode(THIRD_LED_PIN, ANALOG_OUTPUT);
  extender.pinMode(FOURTH_LED_PIN, ANALOG_OUTPUT);
}

void loop() {
  extender.analogWrite(FIRST_LED_PIN, 255);
  extender.analogWrite(SECOND_LED_PIN, 0);
  extender.analogWrite(THIRD_LED_PIN, 255);
  extender.analogWrite(FOURTH_LED_PIN, 0);
  delay(60*10*1000);
  extender.analogWrite(FIRST_LED_PIN, 0);
  extender.analogWrite(SECOND_LED_PIN, 255);
  extender.analogWrite(THIRD_LED_PIN, 0);
  extender.analogWrite(FOURTH_LED_PIN, 255);
  delay(60*10*1000);
  extender.analogWrite(FIRST_LED_PIN, 0);
  extender.analogWrite(SECOND_LED_PIN, 0);
  extender.analogWrite(THIRD_LED_PIN, 0);
  extender.analogWrite(FOURTH_LED_PIN, 0);
  delay(60*10*1000);
  extender.analogWrite(FIRST_LED_PIN, 255);
  extender.analogWrite(SECOND_LED_PIN, 255);
  extender.analogWrite(THIRD_LED_PIN, 255);
  extender.analogWrite(FOURTH_LED_PIN, 255);
  delay(60*10*1000);
}
