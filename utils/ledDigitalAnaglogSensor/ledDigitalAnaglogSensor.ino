/*
  Led on/off and read Analogic and Digital sensor.
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
 * PhotoDiode works:
 * shorter pin to gnd
 * longer pin to first pin 2k rezistor and to A0
 * second pin of rezistor to vcc
 * 
 * Termistor 10k:
 * first pin of termistor to vcc
 * second pin of temistor to first pin of rezistor (10k) and to A0
 * second pin of rezistor to gnd
 */
#include <EnableInterrupt.h>

#define LED_PIN 8
#define ANALOGIC_PIN A0
#define DIGITAL_PIN 9

char inData[20]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character
bool isValidInput;

boolean isValidNumber(char *data, int size)
{
  if (size == 0 ) return false;
   boolean isNum=false;
   if(!(data[0] == '+' || data[0] == '-' || isDigit(data[0]))) return false;

   for(byte i=1;i<size;i++)
   {
       if(!(isDigit(data[i]) || data[i] == '.')) return false;
   }
   return true;
}

void isrReceive() {
  Serial.println("ISR Triggered");
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ANALOGIC_PIN, INPUT);
  pinMode(DIGITAL_PIN, INPUT_PULLUP);
  isValidInput = false;
  digitalWrite(LED_PIN, LOW);
}


void loop() {
 Serial.println( "--------------------------------------------------" );
  Serial.println( "Led and digital and analogic sensors");
  Serial.println( "--------------------------------------------------" );
  Serial.println( "MENU:" );
  Serial.println( "o# turn on");
  Serial.println( "f# turn off");
  Serial.println( "d# read digital data");
  Serial.println( "axxx# read xxx time analogic sensor with an average of 100 reads and delay of 1000");
  Serial.println( "i# disable isr");
  Serial.println( "Ix# enable isr 0=RISING, 1=FALLING");
  Serial.println( "-----------------------------" );
  do {
    for (index = 0; index < 20; index++)
    {
       inData[index] = '\0';
    }
    inChar = '0';
    index = 0;
    while(inChar != '#') {
      while( !Serial.available() )
        ; // LOOP...
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
    if (strlen(inData) == 1) {
      if (inData[0] == 'o') {
        Serial.println("Turn on device");
        digitalWrite(LED_PIN, HIGH);
        isValidInput = true;
      } else if (inData[0] == 'f') {
        Serial.println("Turn off device");
        digitalWrite(LED_PIN, LOW);
        isValidInput = true;
      } else if (inData[0] == 'd') {
        Serial.print("Read digital sensor = ");
        Serial.println(digitalRead(DIGITAL_PIN));
        isValidInput = true;
      } else if (inData[0] == 'i') {
        Serial.print("Disable ISR");
        disableInterrupt(DIGITAL_PIN);
        isValidInput = true;
      } else {
          isValidInput = false;
      }
    } else if (strlen(inData) > 1) {
      if (inData[0] == 'a') {
        //remove f from command
        for (int i = 0 ; i < strlen(inData); i++) {
          inData[i]=inData[i+1];
        }
        if (!isValidNumber(inData, index - 2)) {
          isValidInput = false;
          break;
        }
        long value = 0;
        for (int j = 0; j < atoi(inData); j++ ) {
          value = 0;
          for (int i = 0; i < 100; i++) {
            value += analogRead(ANALOGIC_PIN);
          }
          value = value/100;
          Serial.print("Read analogic sensor with average = ");Serial.println(value);
          delay(1000);
        }
        isValidInput = true;
      } else if (inData[0] == 'I') {
        //remove f from command
        for (int i = 0 ; i < strlen(inData); i++) {
          inData[i]=inData[i+1];
        }
        if (!isValidNumber(inData, index - 2)) {
          isValidInput = false;
          break;
        }
        int type = atoi(inData);
        switch(type) {
          case 0:
            enableInterrupt(DIGITAL_PIN, isrReceive, RISING);
            break;
          case 1:
            enableInterrupt(DIGITAL_PIN, isrReceive, FALLING);
            break;
        }
          isValidInput = true;
        } else {
          isValidInput = false;
        }
    } else {
      isValidInput = false;
    }
  } while( isValidInput == true );
}
