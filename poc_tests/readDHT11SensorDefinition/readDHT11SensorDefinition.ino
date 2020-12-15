/*
  Read DHT11 sensor definition.
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
#include <Adafruit_Sensor.h>
#include <DHT_U.h>

#define DHT11SENSOR DHT11
#define pinDH11 6

const String  TEMPERATURE = "Temperature";
const String  HUMIDITY = "Humidity";

uint32_t delayMS;


/*-----( Declare objects )-----*/
DHT_Unified dht11(pinDH11, DHT11SENSOR);

void setup() {
  Serial.begin(9600);
  // Initialize device.
  dht11.begin();
  Serial.println("DHTxx Unified Sensor informations:");
  // Print temperature sensor details.
  sensor_t sensor;
  dht11.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println(TEMPERATURE);
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht11.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println(HUMIDITY);
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
}
void loop() {
 //nothing to do

}
