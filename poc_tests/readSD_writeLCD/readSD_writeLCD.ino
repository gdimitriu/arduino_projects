
#include <SPI.h>
#include <Ucglib.h>
#include <SD.h>

/*
  Hardware SPI Pins:
    Arduino Uno    sclk=13, data=11
    Arduino Due   sclk=76, data=75
    Arduino Mega  sclk=52, data=51
*/
#define chipSelect_SD 25
#define cardDetect_SD 24
#define DC_LCD 23
#define RST_LCD 22
//unused choose something that is not used
#define CS_LCD 10

Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ DC_LCD , /*cs=*/ CS_LCD, /*reset=*/ RST_LCD);

char fileName[] = "testLCD.txt"; // SD library only supports up to 8.3 names
File fd;
bool alreadyBegan = false;  // SD.begin() misbehaves if not first call
char fileBuffer[256];

////////////////////////////////////////////////////////////////////////////////
// Do everything from detecting card through opening the demo file
////////////////////////////////////////////////////////////////////////////////
void initializeCard(void)
{
  Serial.print("Initializing SD card...");
  
  // Is there even a card?
  if (!digitalRead(cardDetect_SD))
  {
    Serial.println("No card detected. Waiting for card.");
    while (!digitalRead(cardDetect_SD));
    delay(250); // 'Debounce insertion'
  }
  
  // Card seems to exist.  begin() returns failure
  // even if it worked if it's not the first call.
  if (!SD.begin(chipSelect_SD) && !alreadyBegan)  // begin uses half-speed...
  {
    Serial.println("Initialization failed!");
    initializeCard(); // Possible infinite retry loop is as valid as anything
  }
  else
  {
    alreadyBegan = true;
  }
  Serial.println("Initialization done.");

  Serial.print(fileName);
  if (SD.exists(fileName))
  {
    Serial.println(" exists.");
  }
  else
  {
    Serial.println(" doesn't exist. Creating.");
  }
  
  Serial.print("Opening file: ");
  Serial.println(fileName);
}

void text(char *buffer, ucg_int_t pos) {
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(2,pos);
  ucg.setPrintDir(0);
  ucg.print(buffer);
}

void readCardAndPrintText() {
  fd = SD.open(fileName);
  if (fd) {
    Serial.println("");
    Serial.print(fileName);
    Serial.println(":");
    //ucg.setFont(ucg_font_helvB08_hr);
    ucg.setFont(ucg_font_helvB24_hr);
    ucg_int_t pos = 28;//18;
    int index = 0;
    int lineNr = 1;
    while (fd.available())
    {
      char ch = fd.read();
      
      if (ch == '\n') {
        ucg_int_t currentPos = lineNr *pos + (lineNr - 1) * 5;
        text(fileBuffer, currentPos);
        index = 0;
        lineNr++;
        Serial.print(currentPos);Serial.print(" === ");
        Serial.println(fileBuffer);
        memset(fileBuffer,0,sizeof(char)*256);
      } else {
        fileBuffer[index++] = ch;
        fileBuffer[index] = '\0';
      }
    }
  }
  else
  {
    Serial.print("Error opening ");
    Serial.println(fileName);
  }
  fd.close();
}
void setup() {
  Serial.begin(9600);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_ncenR14_hr);
  ucg.clearScreen();
  pinMode(cardDetect_SD, INPUT);

  initializeCard();
  //clear screen
  ucg.clearScreen();
  ucg.setColor(0, 80, 40, 0);
  ucg.setColor(1, 60, 0, 40);
  ucg.setColor(2, 20, 0, 20);
  ucg.setColor(3, 60, 0, 0);
  ucg.setRotate90();
  ucg.drawGradientBox(0, 0, ucg.getWidth(), ucg.getHeight());
  //print data
  readCardAndPrintText();
}

void loop() {
  // put your main code here, to run repeatedly:

}
