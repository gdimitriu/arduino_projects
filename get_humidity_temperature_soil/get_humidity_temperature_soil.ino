/*
  Get the soil Humidity and temperature using DHT11 on surface and deep sensor and print on LCD with I2C.
  Copyright 2019 Gabriel Dimitriu

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
/*
 * HUMIDITY
 * https://github.com/adafruit/Adafruit_Sensor
 * https://github.com/winlinvip/SimpleDHT
 * https://github.com/adafruit/DHT-sensor-library
 * https://learn.adafruit.com/dht/downloads
 * https://create.arduino.cc/projecthub/electropeak/complete-guide-to-use-soil-moisture-sensor-w-examples-756b1f
 * https://www.instructables.com/id/Arduino-Soil-Moisture-Sensor/
 * https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-soil-moisture-sensor-ce769b
 * https://learn.sparkfun.com/tutorials/soil-moisture-sensor-hookup-guide/all
 * http://www.electronics-lab.com/project/using-soil-moisture-sensor-arduino/
 * https://maker.pro/arduino/projects/arduino-soil-moisture-sensor
 * 
 * interrupts and keypad
 * http://gammon.com.au/interrupts
 * http://playground.arduino.cc//Main/PinChangeIntExample
 * https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * https://forum.arduino.cc/index.php?topic=268805.0
 * https://playground.arduino.cc/Main/KeypadTutorial
 */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>
#include <avr/sleep.h>

//#define DEBUG 1
#define pinDH11 3
#define pinButton 2
#define pinDeepSensor A0
#define DHT11SENSOR DHT11

//liquid crystal LCD 1602 on i2c
LiquidCrystal_I2C lcd(0x27, 16, 2);
//create instance of weather sensor
DHT_Unified dht11(pinDH11, DHT11SENSOR);

uint32_t delayMS;

void wakeUp() {
  Serial.println("wake up");
  sleep_disable();
  //detachInterrupt(0);
}

int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 1023, 465, 0, 100);
  return percentValue;
}

void going_to_Sleep()
{
#ifdef DEBUG
  Serial.println("going to sleep");
#endif
  sleep_enable();
  attachInterrupt(0, wakeUp, HIGH);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  sleep_cpu();
  lcd.backlight();
  digitalWrite(LED_BUILTIN, HIGH);
  sensors_event_t event;  
  dht11.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
#ifdef DEBUG
    Serial.println("Error reading temperature!");
#endif
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eroare de citire");
    lcd.setCursor(0,1);
    lcd.print("Sensor temp");
    delay(5000);
  }
  else {
    String temp= "Temp : " + String(event.temperature) + " *C";
#ifdef DEBUG
    Serial.println(temp);
#endif
    lcd.setCursor(0,0);
    lcd.print(temp);
  }
  // Get humidity event and print its value.
  dht11.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
#ifdef DEBUG
    Serial.println("Error reading humidity!");
#endif
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Eroare de citire");
    lcd.setCursor(0,1);
    lcd.print("Sensor umid");
    delay(5000);

  }
  else {
    String humid = "Humid: " + String(event.relative_humidity) + " %";
#ifdef DEBUG
    Serial.println(humid);
#endif
    lcd.setCursor(0,1);
    lcd.print(humid);
  }
  delay(5000);
  float sensorReading = 0;
  for(int i = 0; i< 100; i++)
  {
    sensorReading +=analogRead(pinDeepSensor);
    delay(1);
  }
  sensorReading = sensorReading/100.00;
#ifdef DEBUG
  Serial.println(sensorReading);
#endif
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(sensorReading);
  lcd.setCursor(0,1);
  lcd.print(convertToPercent(sensorReading));
  delay(5000);
  sensorReading = 0;
  for(int i = 0; i< 100; i++)
  {
    sensorReading +=analogRead(pinDeepSensor);
    delay(1);
  }
  sensorReading = sensorReading/100.00;
#ifdef DEBUG
  Serial.println(sensorReading);
#endif
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(sensorReading);
  lcd.setCursor(0,1);
  lcd.print(convertToPercent(sensorReading));
  delay(5000);
  lcd.noBacklight();
  lcd.clear();
}

void setup() {
#ifdef DEBUG
    Serial.begin(9600);
    Serial.println("starting");
#endif
  lcd.begin();
  lcd.noBacklight();
  lcd.setCursor(0,0);
  dht11.begin();  
  sensor_t sensor;
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  going_to_Sleep();
}
