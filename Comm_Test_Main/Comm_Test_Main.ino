#include <SPI.h>

const int slaveSelectPin = 10; // Chip Select-Pin des Slave-Arduino

void setup() {
  Serial.begin(9600);
  SPI.begin();
  pinMode(slaveSelectPin, INPUT);
  pinMode(12,OUTPUT); //SET MISO to output necessary
  //digitalWrite(slaveSelectPin, HIGH); // Setzen Sie den Chip Select-Pin zu High, um die Kommunikation zu beginnen
  Serial.println("Initialized, ready to receive:");
}

void loop() {
  if (digitalRead(slaveSelectPin) == HIGH) {
    Serial.println("I'm here ...");
    delay(1000);
  }

  if (digitalRead(slaveSelectPin) == LOW) {
    int receivedValue = SPI.transfer(69); // Empfangen Sie den Wert vom Master
    Serial.println("Receiving Stuff ...");
    Serial.println(receivedValue);

    //SPI.transfer(receivedValue); // Senden Sie den Wert zurück an den Master
  }

}