/*
  Get the soil Humidity.
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
#define SOIL_SENSOR_PIN A0
void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
}
int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 1023, 465, 0, 100);
  return percentValue;
}

void loop() {
  float sensorReading = 0;
  for(int i = 0; i< 100; i++)
  {
    sensorReading +=analogRead(SOIL_SENSOR_PIN);
    delay(1);
  }
  sensorReading = sensorReading/100.00;
  Serial.print(sensorReading);
  Serial.print(":%:");
  Serial.println(convertToPercent(sensorReading));
  delay(1000);
}
