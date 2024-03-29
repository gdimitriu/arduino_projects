/*
  HMC5983 compass heading on IC2 LCD
  Copyright 2023 Gabriel Dimitriu

  This file is part of Arduino Projects

  Arduino Projects is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  Arduino Projects is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with Arduino Projects; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
*/
#include <Wire.h> //I2C Arduino Library
#include <LiquidCrystal_I2C.h>
#include <HMC5983.h>

//LiquidCrystal_I2C  lcd (0x3f, 20,4);
LiquidCrystal_I2C  lcd (0x27, 16,2);
HMC5983 compass;
boolean compass_rdy = false;

void readCompass_ISR() {
  compass_rdy = true;
}

void setup(){
  Wire.begin();
  lcd.begin();               // start the library
  lcd.backlight();
  lcd.setCursor(0,0);
  while (!compass.begin(NULL, 0)) {
    lcd.print("HMC5983 Problem");
    delay(500);
    lcd.setCursor(0,0);
  }
  compass.setMeasurementMode(HMC5983_CONTINOUS);
  lcd.clear();
  
}
void loop()
{
//  if (compass_rdy) {
//    compass_rdy = false;
    double heading = compass.read();
    //lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Heading: ");
    lcd.print(heading);//-6.06666 to real nord
    delay(25);
//  }
}
