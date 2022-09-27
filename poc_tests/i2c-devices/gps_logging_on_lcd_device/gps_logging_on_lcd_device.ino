/*
 * GPS logging on I2C LCD .
 * Copyright 2018 Gabriel Dimitriu

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
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>

long latitude = 0;
long longitude = 0;
unsigned long fix_age = 0;

LiquidCrystal_I2C lcd (0x27, 16,2);
TinyGPS gps;
SoftwareSerial mySerial(3, 2);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
}

void loop() {
 
  while (mySerial.available())
  {
    int c = mySerial.read();                   // Read the GPS data
    if (gps.encode(c))                        // Check the GPS data
    {
     // process new gps info here
    }
    
  }
  gps.get_position(&latitude, &longitude, &fix_age);
  Serial.print(latitude);Serial.print(":"); Serial.println(longitude);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(latitude);
  lcd.setCursor(0,1);
  lcd.print(longitude);
  lcd.setCursor(0,2);
  lcd.print(fix_age);
  delay(1000);
}
