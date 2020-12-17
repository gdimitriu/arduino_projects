/*
 * GPS logging on I2C LCD version 2.
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
#include <TinyGPS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

TinyGPS gps;
LiquidCrystal_I2C  lcd (0x27, 16,2);              //LCD driver pins
int led = 13;

SoftwareSerial mySerial(3, 2);

long lat, lon;
unsigned long fix_age, time, date, speed, course;
unsigned long chars;
unsigned short sentences, failed_checksum;
//int year;
//byte month, day, hour, minute, second, hundredths;

int DEG;
int MIN1;
int MIN2;
 
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



void setup()
{
  Serial.begin(115200);
  mySerial.begin(9600);            //Set the GPS baud rate.
  pinMode(led, OUTPUT);  
  Serial.println("Adafruit GPS library basic test!");
  lcd.begin();               // start the library
  lcd.backlight();
  lcd.setCursor(0,0);             // set the LCD cursor   position 
  lcd.print("GPS test");          // print a simple message on the LCD 
  delay(2000);
}

void loop()
{
  while (mySerial.available())
  {
    digitalWrite(led, HIGH);
    int c = mySerial.read();                   // Read the GPS data
    if (gps.encode(c))                        // Check the GPS data
    {
      // process new gps info here
    }
    Serial.print(c);
  }
  Serial.println("done");
  digitalWrite(led, LOW);
  gps.get_position(&lat, &lon, &fix_age);     // retrieves +/- lat/long in 100000ths of a degree
  Serial.print(lat); Serial.print(":"); Serial.println(lon);
  gps.get_datetime(&date, &time, &fix_age);   // time in hhmmsscc, date in ddmmyy
  Serial.print(date); Serial.print(":time:"); Serial.println(time);
  //gps.crack_datetime(&year, &month, &day,    //Date/time cracking
  //&hour, &minute, &second, &hundredths, &fix_age);  

LAT();
LON();

}
