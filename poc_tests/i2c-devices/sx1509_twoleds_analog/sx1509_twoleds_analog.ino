/*
 * SX1509 with two leds using analog write (PWM).
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
#define SECOND_LED_PIN 1
SX1509 extender;

void setup() {
  extender.begin(0x3E);
  extender.clock(INTERNAL_CLOCK_2MHZ,7);
  extender.pinMode(FIRST_LED_PIN, ANALOG_OUTPUT);
  extender.pinMode(SECOND_LED_PIN, ANALOG_OUTPUT);
}

void loop() {
  for(int i = 0; i < 256; i++)
  {
    extender.analogWrite(FIRST_LED_PIN, i);
    extender.analogWrite(SECOND_LED_PIN,255-i);
    delay(20);
  }
  delay(500);
  for (int i = 255; i >= 0; i--)
  {
    extender.analogWrite(FIRST_LED_PIN, i);
    extender.analogWrite(SECOND_LED_PIN,255-i);
    delay(20);
  }
  delay(500);
}
