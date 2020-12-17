/*
 * analogic components calibrations/reading.
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
#define DIGITAL_PIN 7
#define ANALOGIC_PIN A0
/*
 * Hall sensor:
 * the window face -> pins 1,2,3 from left to right
 * vcc to first pin
 * gnd to second pin
 * for analogic output pin (3) direct to A0
 * for digital resitor 10k between output (3) and vcc and to 7
 * 
 * PhotoRezistor: 
 * VCC to photresistor first pin
 * photoresistor second pin to A0
 * photoresistor second pin to rezistor 10k first pin
 * resistor second pin to GND
 *
 *Photorezistor and photodiode are almost the same
 * PhotoTransistor:
 * longer pin to vcc
 * shorter pin to first pin 470k/10k rezistor and to A0
 * second pin of rezistor to gnd
 * PhotoDiode:
 * shorter pin to vcc
 * longer pin to first pin 2k rezistor and to A0
 * second pin of rezistor to gnd
 * 
 * Termistor 10k:
 * first pin of termistor to vcc
 * second pin of temistor to first pin of rezistor (10k) and to A0
 * second pin of rezistor to gnd
 */
bool isValidInput;
char inData[20]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character

bool analogicOrDigital = false; //true if is digital false for analogic
void setup() {
  Serial.begin(9600);
  pinMode(ANALOGIC_PIN, INPUT);
  pinMode(DIGITAL_PIN, INPUT_PULLUP);
}


void loop()
{
  Serial.println( "-----------------------------------------------------" );
  Serial.println( "Reading of analogic sensors");
  Serial.println( "-----------------------------------------------------" );
  Serial.println( "MENU:" );
  Serial.println( "d# digital read" );
  Serial.println( "a# analogic read");
  Serial.println( "-----------------------------" );
   do {
    for (index = 0; index < 20; index++)
    {
       inData[index] = '\0';
    }
    inChar = '0';
    index = 0;
    while(inChar != '#') {
      while( !Serial.available() ) {
        if (analogicOrDigital) {
           int value = digitalRead(DIGITAL_PIN);
           Serial.println(value);
           delay(100);
        } else {
            int value = analogRead(ANALOGIC_PIN);
            Serial.println(value);
            delay(100);
        }
      }
      while(Serial.available() > 0) // Don't read unless
                                                 // there you know there is data
      {
          if(index < 19) // One less than the size of the array
          {
              inChar = Serial.read(); // Read a character
              inData[index] = inChar; // Store it
              index++; // Increment where to write next
              inData[index] = '\0'; // Null terminate the string
          }
      }
    }
    if (index > 0) {
      inData[index-1] = '\0';
    }
    if (strcmp(inData,"d") == 0) {
      analogicOrDigital = true;
      isValidInput = true;
    } else if (strcmp(inData, "a") == 0) {
      analogicOrDigital = false;
      isValidInput = true;
    } else {
      isValidInput = false;
    }
  } while( isValidInput == true );
}
