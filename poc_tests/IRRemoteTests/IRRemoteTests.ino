/*
 * IR Remote test
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
#include <IRremote.h>

#define IR_PIN 0
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
// create instance of 'irrecv'
IRrecv irrecv(IR_PIN);
// create instance of 'decode_results'
decode_results results;

void setup() {
  // Start the IR receiver
  irrecv.enableIRIn(); 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    Serial.println(results.value);
    irrecv.resume(); // receive the next value
  }
  delay(10);
}
