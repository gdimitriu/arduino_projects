#include <SerialFlash.h>
#include <SPI.h>
#define CSPIPIN 10
SerialFlashFile file;
void setup() {
  Serial.begin(9600);
  if (!SerialFlash.begin(CSPIPIN)) {
    while(1) {
      Serial.println("Unable to access SPI Flash chip");
      delay(1000);
    }
  }
  if (SerialFlash.exists("test.bin")) {
    file = SerialFlash.open("test.bin");
    file.erase();
    Serial.print("Size of file=");Serial.println(file.size());
  } else {
    Serial.println("Create file");
    SerialFlash.createErasable("test.bin",256);
    file = SerialFlash.open("test.bin");
  }
  int nr;
  nr = 6;
  file.write(&nr,1);
  nr = file.write("test a",nr);
  uint16_t distance=1657;
  file.write(&distance,2); 
  file.flush();
  Serial.print("Written=");Serial.println(nr);

  Serial.println("Writed to file");
  Serial.println("Read from file");
  char buffer[256];
  Serial.print("position=");Serial.println(file.position());
  file.seek(0);
  int val;
  file.read(&val,1);
  Serial.println(val);
  nr = file.read(buffer,val);
  Serial.println(nr);
  
  Serial.println(buffer);
  distance = 0;
  file.read(&distance,2);
  Serial.println(distance);
  file.close();
}

void loop() {

}
