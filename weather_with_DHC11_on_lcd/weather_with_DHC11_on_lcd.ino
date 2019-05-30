/*
  Wheather (Humidity and temperature using DHT11) and print the LCD without I2C.
  Copyright 2018 Gabriel Dimitriu

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
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

#define DHT11SENSOR DHT11
#define pinDH11 6

uint32_t delayMS;

/*-----( Declare objects )-----*/
//create instance of weather sensor
DHT_Unified dht11(pinDH11, DHT11SENSOR);
//create instance of LCD
LiquidCrystal lcd(12,10,5,4,3,2);
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
  // Initialize device.
  dht11.begin();  
  sensor_t sensor;
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
 // Get temperature event and print its value.
  sensors_event_t event;  
  dht11.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    String temp= "Temp : " + String(event.temperature) + " *C";
    Serial.println(temp);
    lcd.setCursor(0,0);
    lcd.print(temp);
  }
  // Get humidity event and print its value.
  dht11.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    String humid = "Humid: " + String(event.relative_humidity) + " %";
    Serial.println(humid);
    lcd.setCursor(0,1);
    lcd.print(humid);
  }
  delay(10000);
}
