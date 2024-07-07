#include <SPI.h>
#include "communicate.hpp"
#include "drive.hpp"
#include "steer.hpp"

void setup() {
  driveSetup();
  steerSetup();
  commSetup();
  
  Serial.println("Initialized, ready to go:");  //debug
}

void loop() {
  int speedData;
  int steerData;

  digitalWrite(chipSelectPin, LOW);         // select a chip
  Serial.println("Receiving Stuff ...");        //debug
  uint16_t receivedVal = SPI.transfer16(0); // receive val from chip
  digitalWrite(chipSelectPin, HIGH);        // deselect the chip 

  Serial.println(receivedVal);                  //debug
  
  //split received data into speed and steer data
  steerData = (receivedVal >> 9) & 0x7F; 
  speedData = receivedVal & 0x01FF;  

  Serial.println(speedData);                    //debug
  Serial.println(steerData);                    //debug

  drive(speedData);
  steer(steerData);
  
  delay(1000);
}

