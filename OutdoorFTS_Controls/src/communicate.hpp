// Don't know if usage of defines nessecary
#define MOSI_PIN D11
#define MISO_PIN D12
#define SCLK_PIN D13
#define CS_PIN D10

const int chipSelectPin = 10; // Chip Select-Pin des Slave-Arduino

void commSetup(){
    Serial.begin(9600);
    SPI.begin();
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0)); // Setze Taktgeschwindigkeit auf 1 MHz 
  
    pinMode(chipSelectPin, OUTPUT);
    digitalWrite(chipSelectPin, HIGH); // Setzen Sie den Chip Select-Pin zu High, um die Kommunikation zu beginnen
}

