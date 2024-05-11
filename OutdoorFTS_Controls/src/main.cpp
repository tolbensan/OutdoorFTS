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
  pinMode(slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH); // Setzen Sie den Chip Select-Pin zu High, um die Kommunikation zu beginnen
  Serial.println("Initialized, ready to go:");
}

void loop() {
  digitalWrite(slaveSelectPin, LOW); // Wählen Sie den Slave aus

  Serial.println("Sending Stuff ...");
  //SPI.transfer(42); // Senden Sie einen Wert an den Slave
  
  int receivedValue = SPI.transfer(45); // Empfangen Sie den Wert vom Slave
  Serial.println(receivedValue);

  digitalWrite(slaveSelectPin, HIGH); // Wählen Sie den Slave ab

  drive();
  
  delay(1000);
}

