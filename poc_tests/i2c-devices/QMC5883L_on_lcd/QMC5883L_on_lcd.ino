/*
  QMC5883L compass azimuth on IC2 LCD
  Copyright 2024 Gabriel Dimitriu

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
#include <QMC5883LCompass.h>

//LiquidCrystal_I2C  lcd (0x3f, 20,4);
LiquidCrystal_I2C  lcd (0x27, 16,2);
QMC5883LCompass compass;
void setup(){
  Wire.begin();
  lcd.begin();               // start the library
  lcd.backlight();
  lcd.setCursor(0,0);
  compass.init();
  lcd.print("Calibration");
  lcd.setCursor(0,0);
  lcd.clear();
  compass.setCalibrationOffsets(compass.getCalibrationOffset(0), compass.getCalibrationOffset(1), compass.getCalibrationOffset(2));
  compass.setCalibrationScales(compass.getCalibrationScale(0), compass.getCalibrationScale(1), compass.getCalibrationScale(2));
  lcd.setCursor(0,1);
  lcd.print("Azimuth: ");
}
void loop()
{
    compass.read();
    int azimuth = compass.getAzimuth();
    //lcd.clear();
//    lcd.setCursor(9,1);
//    lcd.print("       ");
//    delay(25);
    lcd.setCursor(9,1);
    lcd.print(azimuth);
    delay(25);
}
