#include <SPI.h>

const int slaveSelectPin = 10; // Chip Select-Pin des Slave-Arduino
const int potPin = A0;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  //SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0)); // Setze Taktgeschwindigkeit auf 1 MHz //Macht nur alles kaputt

  pinMode(slaveSelectPin, INPUT);
  pinMode(12,OUTPUT); //SET MISO to output necessary
  //digitalWrite(slaveSelectPin, HIGH); // Setzen Sie den Chip Select-Pin zu High, um die Kommunikation zu beginnen
  
  pinMode(potPin, INPUT); // Potentiometer-Pin als Eingang konfigurieren
  //analogReadResolution(8);
  Serial.println("Initialized, ready to receive:");
}

void loop() {

  int sensorWert = analogRead(potPin); // Wert vom Potentiometer lesen
  float spannung = sensorWert * (3.3 / 1023.0); // Spannung aus dem Messwert berechnen
  float setspeed = sensorWert * 0.5702;  //Geschwindigkeit aus Sensorwert berechnen zum übergeben
  uint16_t transf_speed = setspeed;
  
  Serial.print("Potiwert: ");
  Serial.print(sensorWert);
  Serial.print(" | Voltage: ");
  Serial.print(spannung, 2); // Spannung mit 2 Dezimalstellen ausgeben
  Serial.print(" | Geschwindigkeit: ");
  Serial.print(setspeed, 2); // Spannung mit 2 Dezimalstellen ausgeben
  Serial.print(" | Uebertragen: ");
  Serial.println(transf_speed); // Spannung mit 2 Dezimalstellen ausgeben
  
  

  if (digitalRead(slaveSelectPin) == HIGH) {
    Serial.println("I'm here ...");
    delay(1000);
  }

  if (digitalRead(slaveSelectPin) == LOW) {
    uint16_t receivedVal16 = SPI.transfer16(transf_speed); // Empfangen Sie den Wert vom Master
    Serial.println("Receiving Stuff ...");
    Serial.println(receivedVal16);

    //SPI.transfer(receivedValue); // Senden Sie den Wert zurück an den Master
  }

}
