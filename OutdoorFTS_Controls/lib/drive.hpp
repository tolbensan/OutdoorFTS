#pragma once

#include <stdio.h>
#include <iostream>

void test()
{
    std::cout << "Test bestanden!" << std::endl;    //printf("Test bestanden!");
}

void drive()
{
    double speed;
    //calculate enginespeed out of received speeddata
    //acceleration for engine on gpio pins
    std::cout << "I'm drivin" << std::endl;    //printf("I'm drivin");

}

void emergency_brake()
{
    /*Untersuchen ob es verschiedene Möglichkeiten gibt zu bremsen und ob diese den Throttle überschreibt*/
    
    //create connection between brake signals
    std::cout << "Emergency! I'm brakin." << std::endl;     //printf("Emergency! I'm brakin.");
}

void brake()
{
    /*Untersuchen ob es verschiedene Möglichkeiten gibt zu bremsen und ob diese den Throttle überschreibt*/
    
    //create connection between brake signals
    std::cout << "This is brake_func" << std::endl;         //("This is brake_func");
}

void steer()
{
    std::string direction = "straight";     //Default value
    //calculate steering angle
    //set steering angle to step engine
    std::cout << "Driving " << direction << std::endl;
}



    
  
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  //pinMode(ledPin, OUTPUT); // LED-Pin als Output konfigurieren
  // OutputPin als Analog-Output konfigurieren
  //analogWriteResolution(12); // 12 Bit Auflösung für Analogausgabe
  //pinMode(PB14, OUTPUT);
  //test();

 
void sett() {
  
  // Setze den OutputPin auf 0,7 V
  analogWrite(PB14, (0.7 / 3.3) * 4095); // Berechne Wert für 0,7 V
  delay(1000); // 1 Sekunde warten

  // Setze den OutputPin auf 1,7 V
  analogWrite(PB14, (1.7 / 3.3) * 4095); // Berechne Wert für 1,7 V
  delay(1000); // 1 Sekunde warten

  // Setze den OutputPin auf 3,3 V
  analogWrite(PB14, 4095); // Maximaler Wert für 3,3 V
  delay(1000); // 1 Sekunde warten
}

/*
void sendData(String data) {
  // Aktiviere den ESP32 Chip Select
  digitalWrite(STM32_CHIP_SELECT_PIN, LOW);

  // Sende die Daten an den ESP32
  for (int i = 0; i < data.length(); i++) {
    SPI.transfer(data[i]);
  }

  // Deaktiviere den ESP32 Chip Select
  digitalWrite(STM32_CHIP_SELECT_PIN, HIGH);
}

String receiveData() {
  String response = "";

  // Aktiviere den ESP32 Chip Select
  digitalWrite(STM32_CHIP_SELECT_PIN, LOW);

  // Empfange Daten vom ESP32
  while (SPI.available()) {
    response += (char)SPI.transfer(0);
  }

  // Deaktiviere den ESP32 Chip Select
  digitalWrite(STM32_CHIP_SELECT_PIN, HIGH);

  return response;
}
*/