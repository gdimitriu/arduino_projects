#include <Wire.h> //I2C Arduino Library
#include <LiquidCrystal_I2C.h>
#include <HMC5983.h>

#define addr 0x1E //I2C Address for The HMC5883
//LiquidCrystal_I2C  lcd (0x3f, 20,4);
LiquidCrystal_I2C  lcd (0x27, 16,2);
HMC5983 compass;
boolean compass_rdy = false;

void readCompass_ISR() {
  compass_rdy = true;
}

void setup(){
  Wire.begin();
  lcd.begin();               // start the library
  lcd.backlight();
  lcd.setCursor(0,0);
  while (!compass.begin(NULL, 0)) {
    lcd.print("HMC5983 Problem");
    delay(500);
    lcd.setCursor(0,0);
  }
  compass.setMeasurementMode(HMC5983_CONTINOUS);
  lcd.clear();
  
}
void loop()
{
//  if (compass_rdy) {
//    compass_rdy = false;
    double heading = compass.read();
    //lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Heading: ");
    lcd.print(heading);//-6.06666 to real nord
    delay(25);
//  }
}
