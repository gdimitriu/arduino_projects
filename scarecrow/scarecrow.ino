#include <avr/sleep.h>

#define DEBUG 1
#define SENSOR_PIN 2
#define SERVO_PIN 3
void wakeUp() {
#ifdef DEBUG
  Serial.println("wakeup");
#endif  
  sleep_disable();
//  detachInterrupt(0);
}

void going_to_Sleep()
{
#ifdef DEBUG
  Serial.println("going to sleep");
#endif
  sleep_enable();
  attachInterrupt(0, wakeUp, HIGH);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  sleep_cpu();
  analogWrite(SERVO_PIN,255);
  delay(5*1000); //5s
  analogWrite(SERVO_PIN,0);
  delay(30*1000); //30s
}

void setup() {
#ifdef DEBUG
    Serial.begin(9600);
    Serial.println("starting");
#endif
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  going_to_Sleep();
}
