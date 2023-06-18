const int speakerPin = 4;
const int enablePin = 5;
const int rx = 2;
const int tx = 3;
#define baud = 115200;

#include <QMC5883LCompass.h>
#include <SoftwareSerial.h>
#include <avr/wdt.h>
SoftwareSerial Serie (rx, tx);

QMC5883LCompass compass;

void setup() {
  Serie.begin(115200);
  Serial.begin(9600);
  compass.init();
  compass.setCalibration(-1216, 923, -740, 1420, -1515, 0);

  
}

void loop() {
  int a;
  
  // Read compass values
  compass.read();

  // Return Azimuth reading
  a = compass.getAzimuth();
  
  Serial.print("/");Serial.print(a);Serial.println(":");
  Serie.print("/");Serie.print(a);Serie.print(":");

  delay(10);
}
