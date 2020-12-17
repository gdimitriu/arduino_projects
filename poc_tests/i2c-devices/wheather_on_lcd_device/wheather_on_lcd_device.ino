/*
 * Wheather on LCD on I2C triggerred by IR remote controll.
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
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>
#include "IRremote.h"

#define DHT11SENSOR DHT11
#define pinDH11 6
#define IR_PIN 11

uint32_t delayMS;

/*-----( Declare objects )-----*/
//create instance of weather sensor
DHT_Unified dht11(pinDH11, DHT11SENSOR);
//create instance of LCD
LiquidCrystal lcd(12,10,5,4,3,2);
// create instance of 'irrecv'
IRrecv irrecv(IR_PIN);

// give a string  based on IR code received
String translateIR(decode_results *results) 
{
  switch(results->value)
  {
  case 0xFFA25D:  
    return String("CH-"); 
  case 0xFF629D:  
    return String("CH");
  case 0xFFE21D:  
    return String("CH+");
  case 0xFF22DD:  
    return String("PREV");
  case 0xFF02FD:  
    return String("NEXT");
  case 0xFFC23D:  
    return String("PLAY/PAUSE");
  case 0xFFE01F:  
    return String("VOL-");
  case 0xFFA857:  
    return String("VOL+"); 
  case 0xFF906F:  
    return String("EQ");
  case 0xFF6897:  
    return String("0");
  case 0xFF9867:  
    return String("100+");
  case 0xFFB04F:  
    return String("200+");
  case 0xFF30CF:  
    return String("1");
  case 0xFF18E7:  
    return String("2");
  case 0xFF7A85:  
    return String("3");
  case 0xFF10EF:  
    return String("4");
  case 0xFF38C7:  
    return String("5");
  case 0xFF5AA5:  
    return String("6");
  case 0xFF42BD:  
    return String("7");
  case 0xFF4AB5:  
    return String("8");
  case 0xFF52AD:  
    return String("9");
  default: 
    return String("other");
  }
} //END translateIR

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
  // Initialize device.
  dht11.begin();  
  sensor_t sensor;
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  // Start the IR receiver
  irrecv.enableIRIn(); 
}

void loop() {
  decode_results results;
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    Serial.print(translateIR(&results)); 
    irrecv.resume(); // receive the next value
  }
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
