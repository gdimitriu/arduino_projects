#include <Wire.h> //I2C Arduino Library
#include <LiquidCrystal_I2C.h>
#include <HMC5983.h>

#define addr 0x1E //I2C Address for The HMC5883
LiquidCrystal_I2C  lcd (0x3f, 20,4);
HMC5983 compass;

void setup(){
  Wire.begin();
  compass.begin(NULL, true);
  lcd.begin();               // start the library
  lcd.backlight();
  lcd.setCursor(0,0);
}
void loop()
{
  double heading = compass.read();
  lcd.setCursor(0,1);
  lcd.print("Heading: ");
  lcd.print(heading);
  delay(100);
}
