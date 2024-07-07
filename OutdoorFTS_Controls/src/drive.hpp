#pragma once
#include <Arduino.h>

#define SPEEDFAKTOR 8.03696   //linearer Umrechnungsfaktor zur Bestimmung des einzustellenden 12Bit-Wert an DAC
#define INITIAL 993.72727     //0,8 Volt Schwelle, ab der erst ein Wert beim Motor ankommt. Eigentlich 992,... aber um rundungsfehler auf 4095 auszugleichen um eins höher gesetzt.
#define ENGINEPIN PB14
#define BRAKEPIN PB5
#define EMCYBRAKEPIN PB3

void driveSetup();
int drive(double transfd_speed);
void brake(int calcd_speed);
void emergency_brake(int calcd_speed);

void driveSetup()
{
  pinMode(ENGINEPIN, OUTPUT);
  pinMode(BRAKEPIN, OUTPUT);
  pinMode(EMCYBRAKEPIN, OUTPUT);
  analogWriteResolution(12);
}

int drive(double transfd_speed)
{
    double speed;
    int calcd_speed;
    // Just debugging stuff ...
    Serial.print("This is drive function ...");

    // Calculate engine speed out of received speed data
    speed = transfd_speed * SPEEDFAKTOR + INITIAL;
    calcd_speed = static_cast<int>(speed);
    Serial.print("received speed: ");
    Serial.print(transfd_speed);
    Serial.print(" | calculated speed: ");
    Serial.print(speed);
    Serial.print(" | set speed: ");
    Serial.println(calcd_speed);
    // set engine to calculated speed
    analogWrite(ENGINEPIN, calcd_speed);

    return calcd_speed;
}

void brake(int calcd_speed)  
{
    Serial.println("This is brake function ...");
    digitalWrite(BRAKEPIN, HIGH);
    if (calcd_speed <= 100) {
        digitalWrite(BRAKEPIN, LOW);
    }
}

void emergency_brake(int calcd_speed) // for redundancy
{
    Serial.println("This is emergency brake ...");
    digitalWrite(EMCYBRAKEPIN, HIGH);
    if (calcd_speed == 0) {
        digitalWrite(BRAKEPIN, LOW);
    }
}