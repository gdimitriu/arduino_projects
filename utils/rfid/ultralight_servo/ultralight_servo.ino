/* mifare ultralight example (25-02-2018)
 *
 *   RFID-RC522 (SPI connexion)
 *   
 *   CARD RC522      Arduino (UNO)
 *     SS   -----------  10 (Configurable, see SS_PIN constant)
 *     SCK  -----------  13
 *     MOSI -----------  11
 *     MISO -----------  12
 *     IRQ  ----------- 
 *     GND  -----------  GND
 *     RST  -----------  9 (onfigurable, see RST_PIN constant)
 *     3.3V ----------- 3.3V
 *     
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>


#define SS_PIN          10
#define RST_PIN         MFRC522::UNUSED_PIN
#define SERVO_PIN 7

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
MFRC522::StatusCode status; //variable to get card status

byte buffer[18];  //data transfer buffer (16+2 bytes data+CRC)
byte size = sizeof(buffer);
Servo rfidServo;

uint8_t pageAddr = 0x06;  //In this example we will write/read 16 bytes (page 6,7,8 and 9).
                            //Ultraligth mem = 16 pages. 4 bytes per page. 
                            //Pages 0 to 4 are for special functions.           
//for communication
char inDataBT[20]; // Allocate some space for the string
char inDataSerial[20]; // Allocate some space for the string
char inCharSerial; // Where to store the character read
byte indexSerial = 0; // Index into array; where to store the character
boolean cleanupSerial;

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card 
  Serial.println("Starting!");
  if (!mfrc522.PCD_PerformSelfTest())
    Serial.println("Self test failed");
  mfrc522.PCD_Init(); // Init MFRC522 card 
  rfidServo.attach(SERVO_PIN);
  Serial.println("Started!");
}

void cleanup(bool isBT) {
   for (indexSerial = 0; indexSerial < 20; indexSerial++) {
      inDataSerial[indexSerial] = '\0';
   }
   inCharSerial = '0';
   indexSerial = 0;
   cleanupSerial = false;
}

boolean isValidNumber(char *data, int size) {
  if (size == 0 ) return false;
   boolean isNum=false;
   if(!(data[0] == '+' || data[0] == '-' || isDigit(data[0]))) return false;

   for(byte i=1;i<size;i++) {
       if(!(isDigit(data[i]) || data[i] == '.')) return false;
   }
   return true;
}

bool makeMove(char *inData,int index, bool isBT) {
  if (inData[0] == 's') {
     //remove s from command
     for (int i = 0 ; i < strlen(inData); i++) {
        inData[i]=inData[i+1];
     }
     if (!isValidNumber(inData, index - 2)) {
        cleanup(isBT);
        return false;
     }
     int target = atoi(inData);
     if (target < 0 || target > 180) {
        Serial.print("Value out of range");
        cleanup(isBT);
        return false;
     }
     Serial.print("move servo ");
     Serial.print(target);
     Serial.println(" degree");
     rfidServo.write(target);
     cleanup(isBT);
     return true;
  }
  cleanup(isBT);
  return false;
}

void readSerialCommand() {
  
   while(Serial.available() > 0) // Don't read unless
                                                 // there you know there is data
   {
      if(indexSerial < 19) // One less than the size of the array
      {
         inCharSerial = Serial.read(); // Read a character
         if (inCharSerial == '\r' || inCharSerial == '\n' || inCharSerial == '\0' || inCharSerial < 35 || inCharSerial > 122) {
            continue;
         }
         //commands start with a letter capital or small
         if (indexSerial == 0 && !((inCharSerial > 64 && inCharSerial < 91) || (inCharSerial > 96 && inCharSerial < 123))) {
            continue;
         }
         inDataSerial[indexSerial++] = inCharSerial; // Store it
         inDataSerial[indexSerial] = '\0'; // Null terminate the string
      } else {
        cleanup(false);
      }
   }
   if (indexSerial == 0) {
    return;
   }
   if (inDataSerial[indexSerial-1] == '#') {
      if (indexSerial > 0) {
         inDataSerial[indexSerial-1] = '\0';
      }
      makeMove(inDataSerial,indexSerial, false);
   }
}

void readRFID() {
    // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;

  // Read data ***************************************************
  Serial.println(F("Reading data ... "));
  //data in 4 block is readed at once.
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(pageAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Read() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  Serial.print(F("Readed data: "));
  //Dump a byte array to Serial
  for (byte i = 0; i < 16; i++) {
    Serial.write(buffer[i]);
  }
  Serial.println();

  mfrc522.PICC_HaltA();
}

void loop() {
  while( !Serial.available()) {
    readRFID();
  }
  readSerialCommand();
}
