#include <AccelStepper.h>
#include <EEPROM.h>

#define STEP_PIN 5 // Anschluss des Schrittsignals
#define DIR_PIN 2  // Anschluss des Richtungssignals

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN); // Erstelle einen Schrittmotorobjekt
const int EEPROM_ADDRESS = 0; // Adresse im EEPROM, um die Position zu speichern
long currentPosition = 0; // Verfolge die aktuelle Position des Motors

// Definiere die virtuellen Anschläge
const int MIN_POSITION = -200;
const int MAX_POSITION = 200;

//200Steps = 1 Umdrehung = 360°

void motorLinksDrehen(int schritte);
void motorRechtsDrehen(int schritte);


void steer(int transfd_steerangle){
  if (transfd_steerangle < 64){
    motorLinksDrehen(transfd_steerangle);
  }
  if (transfd_steerangle > 64){
    motorRechtsDrehen(transfd_steerangle - 64);
  }
  if (transfd_steerangle == 64){
    if (currentPosition != 0) {
    stepper.moveTo(-currentPosition);
    stepper.runToPosition();
    currentPosition = 0;
    EEPROM.put(EEPROM_ADDRESS, currentPosition); // Setze die gespeicherte Position auf 0
    Serial.println("Schrittmotor auf Position 0 zurückgefahren und Position auf 0 gesetzt.");
  } else {
    Serial.println("Schrittmotor befindet sich bereits auf Position 0.");
  }
  }
}

void steerSetup() {
  // Setze Step- und Direction-Pins auf Ausgang
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  // Setze die Step- und Direction-Pins auf einen definierten Anfangszustand
  digitalWrite(STEP_PIN, LOW);
  digitalWrite(DIR_PIN, LOW);

  stepper.setMaxSpeed(5000); // Setze die maximale Geschwindigkeit (angepasst an deine Anforderungen)
  stepper.setAcceleration(1500); // Setze die maximale Beschleunigung auf 1500

  // Lese die gespeicherte Position aus dem EEPROM
  EEPROM.get(EEPROM_ADDRESS, currentPosition);
  Serial.print("Gespeicherte Position: ");
  Serial.println(currentPosition);

  // Fahre den Motor zur Position 0, wenn er sich nicht bereits auf Position 0 befindet
  if (currentPosition != 0) {
    stepper.moveTo(-currentPosition);
    stepper.runToPosition();
    currentPosition = 0;
    EEPROM.put(EEPROM_ADDRESS, currentPosition); // Setze die gespeicherte Position auf 0
    Serial.println("Schrittmotor auf Position 0 zurückgefahren und Position auf 0 gesetzt.");
  } else {
    Serial.println("Schrittmotor befindet sich bereits auf Position 0.");
  }

  Serial.println("Geben Sie 'L <Schritte>' für Linksdrehung oder 'R <Schritte>' für Rechtsdrehung ein.");
}


void motorLinksDrehen(int schritte) {
  long newPosition = currentPosition - schritte;
  if (newPosition < MIN_POSITION) {
    newPosition = MIN_POSITION;
  }
  stepper.moveTo(newPosition); // Bewegung ausführen
  stepper.runToPosition(); // Warte, bis die Bewegung abgeschlossen ist
  currentPosition = newPosition; // Aktualisiere die aktuelle Position
  EEPROM.put(EEPROM_ADDRESS, currentPosition); // Speichere die aktuelle Position im EEPROM
  Serial.print("Position nach links drehen gespeichert: ");
  Serial.println(currentPosition);
}

void motorRechtsDrehen(int schritte) {
  long newPosition = currentPosition + schritte;
  if (newPosition > MAX_POSITION) {
    newPosition = MAX_POSITION;
  }
  stepper.moveTo(newPosition); // Bewegung ausführen
  stepper.runToPosition(); // Warte, bis die Bewegung abgeschlossen ist
  currentPosition = newPosition; // Aktualisiere die aktuelle Position
  EEPROM.put(EEPROM_ADDRESS, currentPosition); // Speichere die aktuelle Position im EEPROM
  Serial.print("Position nach rechts drehen gespeichert: ");
  Serial.println(currentPosition);
}
