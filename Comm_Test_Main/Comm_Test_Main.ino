#include <SPI.h>

const int slaveSelectPin = 10; // Chip Select-Pin des Slave-Arduino
const int potPin = A0;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  pinMode(slaveSelectPin, INPUT);
  pinMode(12,OUTPUT); //SET MISO to output necessary
  //digitalWrite(slaveSelectPin, HIGH); // Setzen Sie den Chip Select-Pin zu High, um die Kommunikation zu beginnen
  
  pinMode(potPin, INPUT); // Potentiometer-Pin als Eingang konfigurieren
  
  Serial.println("Initialized, ready to receive:");
}

void loop() {

  int sensorWert = analogRead(potPin); // Wert vom Potentiometer lesen
  float spannung = sensorWert * (3.3 / 255.0); // Spannung aus dem Messwert berechnen
  
  Serial.print("Potentiometerwert: ");
  Serial.print(sensorWert);
  Serial.print(" | Spannung: ");
  Serial.println(spannung, 2); // Spannung mit 2 Dezimalstellen ausgeben
  
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
