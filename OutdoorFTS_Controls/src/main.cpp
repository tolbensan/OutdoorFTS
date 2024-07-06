#include <SPI.h>
#include "communicate.hpp"
#include "drive.hpp"
#include "steer.hpp"



/*void loop() {
  int speedData;
  int steerData;
  int CompleteValue = 0b1100100101110000; //1100100101110000


  digitalWrite(chipSelectPin, LOW); // Wählen Sie den Slave aus
  Serial.println("Sending Stuff ...");
  uint16_t receivedVal16 = SPI.transfer16(uint16_t(25)); // Empfangen Sie den Wert vom Slave
  digitalWrite(chipSelectPin, HIGH); // Wählen Sie den Slave ab

  Serial.println(receivedVal16);
  
  speedData = (receivedVal16 >> 9) & 0x7F;
  steerData = receivedVal16 & 0x01FF;

  Serial.println(speedData);
  Serial.println(steerData);

  drive(speedData);
  steer(steerData);
  
  uint16_t dataToSend = receivedVal16; // Dein Wert, den du senden möchtest
  uint16_t reversedData = (dataToSend << 8) | (dataToSend >> 8); // Umkehrung der Byte-Reihenfolge

  //drive(reversedData);
  
  delay(1000);
}
*/


#include <Arduino.h>

volatile int i = 0;
byte myArray[2];
int x;

void setup()
{
  driveSetup();
  steerSetup();
  //commSetup(); //not working at all
  
  Serial.println("Initialized, ready to go:");
  //Serial.begin(9600);

  // Pinmodes setzen
  pinMode(PB12, INPUT_PULLUP);  // SS (Slave Select)
  pinMode(PB15, OUTPUT);  // MOSI
  pinMode(PB13, INPUT);   // SCK

  // SPI Initialisierung auf Registerebene
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;  // SPI1 Clock einschalten

  // SPI Konfiguration
  SPI1->CR1 = SPI_CR1_SPE       // SPI aktivieren
            | SPI_CR1_BR_1      // Baudrate
            | SPI_CR1_CPOL      // Clock Polarity
            | SPI_CR1_CPHA      // Clock Phase
            | SPI_CR1_MSTR      // Master mode
            | SPI_CR1_SSI       // Internal slave select
            | SPI_CR1_SSM;      // Software slave management

  // SPI Interrupt aktivieren
  SPI1->CR2 |= SPI_CR2_RXNEIE;  // RX buffer not empty interrupt enable

  // NVIC für SPI1 konfigurieren
  NVIC_EnableIRQ(SPI1_IRQn);
}

void loop(void)
{
  int speedData;
  int steerData;
  //Serial.println("I'm here");
  if (i == 2)
  {
    x = (int)myArray[0] << 8 | (int)myArray[1];
    Serial.print("Received 16-bit data item from Master: ");
    Serial.println(x, HEX);
    i = 0;
    Serial.println("=============================================");
  }

  speedData = (x >> 9) & 0x7F;
  steerData = x & 0x01FF;

  Serial.println(speedData);
  Serial.println(steerData);  
  drive(speedData);
  steer(steerData-64);  //set steerData to 0 if wanted to drive straight because of implementation of steer function
}

// SPI1 Interrupt Service Routine
extern "C" void SPI1_IRQHandler(void)
{
  Serial.println("I'm interrupting ... ");
  if (SPI1->SR & SPI_SR_RXNE)  // Prüfen, ob Daten im Empfangsregister sind
  {
    myArray[i] = SPI1->DR;  // Daten vom SPI Data Register lesen
    i++;
  }
}

/*
#include <SPI.h>

volatile int i = 0;
byte myArray[2];

void SPI_ISR();

void setup()
{
  Serial.begin(9600);
  pinMode(SS, INPUT_PULLUP);
  pinMode(MOSI, OUTPUT);
  pinMode(SCK, INPUT);
  SPI.begin(); // Initialisiere das SPI
  attachInterrupt(digitalPinToInterrupt(SS), SPI_ISR, FALLING);  // Interrupt am SS-Pin anhängen
}

void loop(void)
{
  if (i == 2)
  {
    int x = (int)myArray[0] << 8 | (int)myArray[1];
    Serial.print("16-Bit-Daten vom Master empfangen: ");
    Serial.println(x, HEX);
    i = 0;
    Serial.println("=============================================");
  }
}

void SPI_ISR()  // Interrupt Service Routine für SPI
{
  myArray[i] = SPI.transfer(0x00);  // Dummy-Byte senden, um Daten zu lesen
  i++;
}
*/