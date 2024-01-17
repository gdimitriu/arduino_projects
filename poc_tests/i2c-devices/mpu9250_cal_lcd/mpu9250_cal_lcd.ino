#include "MPU9250.h"
#include <LiquidCrystal_I2C.h>

MPU9250 mpu;
LiquidCrystal_I2C  lcd (0x3f, 20,4);

void setup() {
    Wire.begin();
    delay(2000);
    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0,0);
    
    if (!mpu.setup(0x68)) {  // change to your own address
        while (1) {
            lcd.print("MPU9250 Problem");
            delay(5000);
            lcd.setCursor(0,0);
        }
    }

    // calibrate anytime you want to
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Accel Gyro calib");
    lcd.setCursor(0,1);
    lcd.print("in 5sec.");
    lcd.setCursor(0,2);
    lcd.print("Leave device still");
    lcd.setCursor(0,3);
    lcd.print("on the flat plane.");
    mpu.verbose(true);
    delay(5000);
    mpu.calibrateAccelGyro();

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Mag calib in 5sec.");
    lcd.setCursor(0,2);
    lcd.print("Move in figure eight");
    lcd.setCursor(0,3);
    lcd.print("until done.");
    delay(5000);
    mpu.calibrateMag();

    print_calibration();
    mpu.verbose(false);
}

void loop() {
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 100) {
            print_roll_pitch_yaw();
            prev_ms = millis();
        }
    }
}

void print_roll_pitch_yaw() {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Yaw, Pitch, Roll: ");
    lcd.setCursor(0,1);
    lcd.print(mpu.getYaw(), 2);
    lcd.print(", ");
    lcd.print(mpu.getPitch(), 2);
    lcd.print(", ");
    lcd.print(mpu.getRoll(), 2);
    lcd.setCursor(0,2);
    lcd.print(mpu.getGyroX(),2);
    lcd.print(",");
    lcd.print(mpu.getGyroY(),2);
    lcd.print(",");
    lcd.print(mpu.getGyroZ(),2);
}

void print_calibration() {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("accel bias [g]:");
    lcd.setCursor(0,1);
    lcd.print(mpu.getAccBiasX() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    lcd.setCursor(0,2);
    lcd.print(mpu.getAccBiasY() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    lcd.setCursor(0,3);
    lcd.print(mpu.getAccBiasZ() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("gyro bias [deg/s]:");
    lcd.setCursor(0,1);
    lcd.print(mpu.getGyroBiasX() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    lcd.setCursor(0,2);
    lcd.print(mpu.getGyroBiasY() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    lcd.setCursor(0,3);
    lcd.print(mpu.getGyroBiasZ() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("mag bias [mG]:");
    lcd.setCursor(0,1);
    lcd.print(mpu.getMagBiasX());
    lcd.setCursor(0,2);
    lcd.print(mpu.getMagBiasY());
    lcd.setCursor(0,3);
    lcd.print(mpu.getMagBiasZ());
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("mag scale []:");
    lcd.setCursor(0,1);
    lcd.print(mpu.getMagScaleX());
    lcd.setCursor(0,2);
    lcd.print(mpu.getMagScaleY());
    lcd.setCursor(0,3);
    lcd.print(mpu.getMagScaleZ());
    delay(2000);
}
