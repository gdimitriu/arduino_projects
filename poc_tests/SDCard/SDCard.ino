/*
 * First read from SD card
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
#include <SD.h> 
 
File myFile; 

void setup() { 
	Serial.begin(9600); 
//	pinMode(10, OUTPUT); 
 
	if (!SD.begin(53)) { 
		Serial.println("SD Card initialization failed :("); 
	} 
	else{ 
		Serial.println("SD Card initialization done :)"); 
		myFile = SD.open("/first.txt");
    if (myFile) { 
     //Used to separate code 
     Serial.println("===:The File Contains The following text:===");  
      while (myFile.available()) { // Checking if the SD card has the file 
        Serial.write(myFile.read()); // Reading file and printing on serial  
      } 
      myFile.close(); //closing the file 
     } else { 
      Serial.println("error opening test.txt"); //If fine not available 
    } 
	}
} 
 
void loop() {
 
} 
