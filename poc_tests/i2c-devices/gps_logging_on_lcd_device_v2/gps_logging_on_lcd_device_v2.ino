/*
 * GPS logging on I2C LCD version 2.
 * Copyright 2018 Gabriel Dimitriu
 * This is inspired from:
 * https://create.arduino.cc/projecthub/ruchir1674/how-to-interface-gps-module-neo-6m-with-arduino-8f90ad
 * https://wiki.dfrobot.com/GPS_Module_With_Enclosure__SKU_TEL0094_
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
#include <TinyGPS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NeoSWSerial.h>
#include <EnableInterrupt.h>
#define RxD 2
#define TxD 3

TinyGPS gps;
LiquidCrystal_I2C  lcd (0x3f, 20,4);
//LiquidCrystal_I2C  lcd (0x27, 16,2);
long lat, lon;
float flat, flon;
unsigned long fix_age, time, date, speed, course;

int DEG;
int MIN1;
int MIN2;

NeoSWSerial mySerial(RxD, TxD);
 void neoSSerial1ISR() {
    NeoSWSerial::rxISR(*portInputRegister(digitalPinToPort(RxD)));
}

void LAT(){                       //Latitude state
  DEG=lat/1000000;
  MIN1=(lat/10000)%100;
  MIN2=lat%10000;

  lcd.setCursor(0,0);             // set the LCD cursor   position 
  lcd.print("LAT:");              
  lcd.print(DEG);
  lcd.write(0xDF);
  lcd.print(MIN1);
  lcd.print(".");
  lcd.print(MIN2);
  lcd.print("'   ");
}
void LON(){                        //Longitude state
  DEG=lon/1000000;
  MIN1=(lon/10000)%100;
  MIN2=lon%10000;

  lcd.setCursor(0,1);              // set the LCD cursor   position 
  lcd.print("LON:");              
  lcd.print(DEG);
  lcd.write(0xDF);
  lcd.print(MIN1);
  lcd.print(".");
  lcd.print(MIN2);
  lcd.print("'   ");
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

void loop() {
  while (mySerial.available())
  {
    if (gps.encode(mySerial.read()))                        // Check the GPS data
    {
      gps.get_position(&lat, &lon, &fix_age);     // retrieves +/- lat/long in 100000ths of a degree
      gps.f_get_position(&flat, &flon);
      lcd.clear();
      LAT();
      lcd.setCursor(0,2);
      lcd.print("Lat: ");
      lcd.print(flat);
      LON();
      lcd.setCursor(0,3);
      lcd.print("Long:");
      lcd.print(flon);
      gps.get_datetime(&date, &time, &fix_age);   // time in hhmmsscc, date in ddmmyy
    }
  }  
//  delay(1000);
}
