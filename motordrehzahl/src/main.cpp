#include <Arduino.h>

#define ENGINEPIN PB14      



void setup(){
   Serial.begin(9600);
   pinMode(5, OUTPUT);
}


void loop(){

  int calcd_speed = 100;
  analogWrite(ENGINEPIN, calcd_speed);


  float desiredVoltage = 1.5;
  
  // Berechne den 12-Bit DAC-Wert für die gewünschte Spannung
  uint16_t dacValue = (uint16_t)((desiredVoltage / 3.3) * 4095);
  
  // Sende den Wert an den DAC
  analogWrite(5, dacValue);
  //digitalWrite(5, HIGH);
  
  // Ausgabe zur Überprüfung
  Serial.print("Setting voltage to: ");
  Serial.print(desiredVoltage);
  Serial.print("V (DAC value: ");
  Serial.print(dacValue);
  Serial.println(")");
  
  delay(1000); // Warte 1 Sekunde, bevor die Spannung erneut gesetzt wird
}
