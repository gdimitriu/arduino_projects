/*
 * GPS logging on I2C LCD version 3.
 * Copyright 2018 Gabriel Dimitriu
 * This is inspired from:
 * https://www.instructables.com/GPS-Speedometer/
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
#include <TinyGPS++.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NeoSWSerial.h>
#include <EnableInterrupt.h>
#define RxD 2
#define TxD 3

TinyGPSPlus gps;
LiquidCrystal_I2C  lcd (0x3f, 20,4);
//Program variables
double Lat;
double Long;

int num_sat, gps_speed;
String heading;


NeoSWSerial mySerial(RxD, TxD);
 void neoSSerial1ISR() {
    NeoSWSerial::rxISR(*portInputRegister(digitalPinToPort(RxD)));
}

void setup() {
  mySerial.begin(9600);  
  enableInterrupt(RxD, neoSSerial1ISR, CHANGE);
  Wire.begin();
  lcd.begin();               // start the library
  lcd.backlight();
  lcd.setCursor(0,0);             // set the LCD cursor   position 
  lcd.print("GPS test");          // print a simple message on the LCD 
  delay(2000);
  lcd.clear();
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (mySerial.available())
      gps.encode(mySerial.read());
  } while (millis() - start < ms);
}


void Get_GPS() {

  num_sat = gps.satellites.value();

  if (gps.location.isValid() == 1) {

    Lat = gps.location.lat();
    Long = gps.location.lng();


    gps_speed = gps.speed.kmph();

    heading = gps.cardinal(gps.course.value());
  }

  smartDelay(1000);
}

void Display() {
  lcd.setCursor(0,0);
  lcd.print("LAT:");
  lcd.print(Lat,5);
  lcd.setCursor(0,1);
  lcd.print("LON:");
  lcd.print(Long,5);
  lcd.setCursor(0,2);
  lcd.print("SPEED:");
  lcd.print(gps_speed);
  lcd.print(" Km/h");
  lcd.setCursor(0,3);
  lcd.print("Heading:");
  lcd.print(heading);
}

void loop() {
  Get_GPS();
  Display();
}
