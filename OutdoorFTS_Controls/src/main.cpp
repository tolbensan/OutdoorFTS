#include <SPI.h>
#include "communicate.hpp"
#include "drive.hpp"
#include "steer.hpp"

#define MOSI_PIN D11
#define MISO_PIN D12
#define SCLK_PIN D13
#define CS_PIN D10

const int slaveSelectPin = 10; // Chip Select-Pin des Slave-Arduino

void setup() {
  Serial.begin(9600);
  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0)); // Setze Taktgeschwindigkeit auf 1 MHz //Macht nur alles kaputt
  
  pinMode(slaveSelectPin, OUTPUT);
  pinMode(ENGINEPIN, OUTPUT);
  analogWriteResolution(12);
  digitalWrite(slaveSelectPin, HIGH); // Setzen Sie den Chip Select-Pin zu High, um die Kommunikation zu beginnen
  Serial.println("Initialized, ready to go:");
}

void loop() {
  digitalWrite(slaveSelectPin, LOW); // Wählen Sie den Slave aus

  Serial.println("Sending Stuff ...");
  //SPI.transfer(42); // Senden Sie einen Wert an den Slave
  
  uint16_t receivedVal16 = SPI.transfer16(uint16_t(25)); // Empfangen Sie den Wert vom Slave
  //delay(100);
  //uint16_t receivedVal1 = SPI.transfer(130); // Empfangen Sie den Wert vom Slave

  Serial.println(receivedVal16);
  //Serial.println(receivedVal1);

  digitalWrite(slaveSelectPin, HIGH); // Wählen Sie den Slave ab

  drive(receivedVal16);


  
  uint16_t dataToSend = receivedVal16; // Dein Wert, den du senden möchtest
  uint16_t reversedData = (dataToSend << 8) | (dataToSend >> 8); // Umkehrung der Byte-Reihenfolge

  drive(reversedData);
  
  delay(1000);
}

