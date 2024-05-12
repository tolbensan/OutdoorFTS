#pragma once
#include <Arduino.h>
//#include <stdio.h>
//#include <iostream>

//int transfd_speed = 0;

#define SPEEDFAKTOR 8.03696   //linearer Umrechnungsfaktor zur Bestimmung des einzustellenden 12Bit-Wert an DAC
#define INITIAL 993.72727     //0,8 Volt Schwelle, ab der erst ein Wert beim Motor ankommt. Eigentlich 992,... aber um rundungsfehler auf 4095 auszugleichen um eins höher gesetzt.
#define ENGINEPIN PB14

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
    int calcd_speed;

    //debug indicator on serial monitor
    Serial.print("This is drive function ...");

    //calculate enginespeed out of received speeddata
    speed = transfd_speed * SPEEDFAKTOR + INITIAL;
    calcd_speed = speed;
    Serial.print("received speed: ");
    Serial.print(transfd_speed);
    Serial.print(" | calculated speed: ");
    Serial.print(speed);
    Serial.print(" | set speed: ");
    Serial.println(calcd_speed);

    analogWrite(ENGINEPIN, calcd_speed);


    //acceleration for engine on gpio pins
    /*
    for (int brightness = 0; brightness <= 4095; brightness += 10) {
      analogWrite(ENGINEPIN, brightness); // Helligkeit setzen
      Serial.println(brightness);
      delay(50); // Kurze Pause für den Übergang
    }
    */
/*
analogWrite(motorPin, 0);
  delay(1000); // 1 Sekunde warten

  // Beschleunige den Motor in Stufen
  for (int i = 0; i <= 4095; i++) {
    analogWrite(motorPin, i); // Spannung von 0 V bis 3,3 V
    delay(10); // 10 ms warten
  }

  // Halte die maximale Spannung (3,3 V) für 1 Sekunde
  analogWrite(motorPin, 4095);
  delay(1000);

  // Bremse den Motor in Stufen ab
  for (int i = 4095; i >= 0; i--) {
    analogWrite(motorPin, i); // Spannung von 3,3 V bis 0 V
    delay(10); // 10 ms warten
  }
  */
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
  //pinMode(ledPin, OUTPUT); // ledPin als Output konfigurieren
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