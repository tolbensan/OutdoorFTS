#include <SPI.h>
#include "communicate.hpp"
#include "drive.hpp"
#include "steer.hpp"

void setup() {
  driveSetup();
  steerSetup();
  commSetup();
  
  Serial.println("Initialized, ready to go:");
}

void loop() {
  int speedData;
  int steerData;
  int CompleteValue = 0b1100100101110000; //1100100101110000


  digitalWrite(chipSelectPin, LOW); // Wählen Sie den Slave aus
  Serial.println("Sending Stuff ...");
  uint16_t receivedVal16 = SPI.transfer16(uint16_t(25)); // Empfangen Sie den Wert vom Slave
  digitalWrite(chipSelectPin, HIGH); // Wählen Sie den Slave ab

  Serial.println(receivedVal16);
  
  speedData = (receivedVal16 >> 9) & 0x7F;
  steerData = receivedVal16 & 0x01FF;

  Serial.println(speedData);
  Serial.println(steerData);

  drive(speedData);
  steer(steerData);
  
  uint16_t dataToSend = receivedVal16; // Dein Wert, den du senden möchtest
  uint16_t reversedData = (dataToSend << 8) | (dataToSend >> 8); // Umkehrung der Byte-Reihenfolge

  //drive(reversedData);
  
  delay(1000);
}

