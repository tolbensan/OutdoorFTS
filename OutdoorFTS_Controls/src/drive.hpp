#pragma once
#include <Arduino.h>

#define SPEEDFAKTOR 8.03696   //linearer Umrechnungsfaktor zur Bestimmung des einzustellenden 12Bit-Wert an DAC
#define INITIAL 993.72727     //0,8 Volt Schwelle, ab der erst ein Wert beim Motor ankommt. Eigentlich 992,... aber um rundungsfehler auf 4095 auszugleichen um eins höher gesetzt.
#define ENGINEPIN PB14
#define BRAKEPIN PB5

void driveSetup();
void drive(double transfd_speed);
void emergency_brake();
void brake();
void steer();



void driveSetup()
{
  pinMode(ENGINEPIN, OUTPUT);
  pinMode(BRAKEPIN, OUTPUT);
  analogWriteResolution(12);
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
}


void emergency_brake()
{
    Serial.println("This is emergency brake ...");
    //Untersuchen ob es verschiedene Möglichkeiten gibt zu bremsen und ob diese den Throttle überschreibt
    digitalWrite(BRAKEPIN, HIGH);
    //create connection between brake signals
    //std::cout << "Emergency! I'm brakin." << std::endl;     //printf("Emergency! I'm brakin.");
}


void brake()
{

    Serial.println("This is brake function ...");
    /*Untersuchen ob es verschiedene Möglichkeiten gibt zu bremsen und ob diese den Throttle überschreibt*/
    digitalWrite(BRAKEPIN, HIGH);
    //create connection between brake signals
    //std::cout << "This is brake_func" << std::endl;         //("This is brake_func");
}  
