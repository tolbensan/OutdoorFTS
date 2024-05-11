#pragma once
#include <Arduino.h>
//#include <stdio.h>
//#include <iostream>

//int transfd_speed = 0;

void test();
void drive(double transfd_speed);
void emergency_brake();
void brake();
void steer();



void test()
{
    Serial.println("Test passed");
}

void drive(double transfd_speed)
{
    double speed;

    //debug indicator on serial monitor
    Serial.println("This is drive function ...");

    //calculate enginespeed out of received speeddata
    Serial.println(transfd_speed);
    Serial.println(speed);

    //acceleration for engine on gpio pins
    // Setze den OutputPin auf 0,7 V
    analogWrite(PB14, (0.7 / 3.3) * 4095); // Berechne Wert für 0,7 V
    delay(1000); // 1 Sekunde warten

    // Setze den OutputPin auf 1,7 V
    analogWrite(PB14, (1.7 / 3.3) * 4095); // Berechne Wert für 1,7 V
    delay(1000); // 1 Sekunde warten

    // Setze den OutputPin auf 3,3 V
    analogWrite(PB14, 4095); // Maximaler Wert für 3,3 V
    delay(1000); // 1 Sekunde warten
    //std::cout << "I'm drivin" << std::endl;    //printf("I'm drivin");

}


void emergency_brake()
{
    Serial.println("This is emergency brake ...");
    //Untersuchen ob es verschiedene Möglichkeiten gibt zu bremsen und ob diese den Throttle überschreibt
    digitalWrite(PB5, HIGH);
    //create connection between brake signals
    //std::cout << "Emergency! I'm brakin." << std::endl;     //printf("Emergency! I'm brakin.");
}


void brake()
{

    Serial.println("This is brake function ...");
    /*Untersuchen ob es verschiedene Möglichkeiten gibt zu bremsen und ob diese den Throttle überschreibt*/
    digitalWrite(PB5, HIGH);
    //create connection between brake signals
    //std::cout << "This is brake_func" << std::endl;         //("This is brake_func");
}

void steer()
{
    Serial.println("This is steer function ...");
    //std::string direction = "straight";     //Default value
    //calculate steering angle
    //set steering angle to step engine
    //std::cout << "Driving " << direction << std::endl;
}



    
  
  // put your setup code here, to run once:
  //int result = myFunction(2, 3);
  //pinMode(ledPin, OUTPUT); // LED-Pin als Output konfigurieren
  // OutputPin als Analog-Output konfigurieren
  //analogWriteResolution(12); // 12 Bit Auflösung für Analogausgabe
  //pinMode(PB14, OUTPUT);
  //test();

 

  
  

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