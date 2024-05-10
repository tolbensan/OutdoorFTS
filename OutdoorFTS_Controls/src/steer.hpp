#include <AccelStepper.h>

#define STEP_PIN 5 // Anschluss des Schrittsignals
#define DIR_PIN 2  // Anschluss des Richtungssignals

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN); // Erstelle einen Schrittmotorobjekt
int currentPosition = 0; // Verfolge die aktuelle Position des Motors

//200Steps = 1 Umdrehung = 360°
//


void setupp() {
  stepper.setMaxSpeed(5000); // Setze die maximale Geschwindigkeit (angepasst an deine Anforderungen)
  stepper.setAcceleration(2000); // Setze die Beschleunigung (angepasst an deine Anforderungen)
}

void motorLinksDrehen(int schritte) {
  stepper.moveTo(currentPosition-schritte); // Negative Schritte für Drehung nach links
  stepper.runToPosition(); // Bewegung ausführen
  currentPosition -= schritte; // Aktualisiere die aktuelle Position
}

// Funktion zum Drehen des Motors nach rechts um die angegebene Anzahl von Schritten
void motorRechtsDrehen(int schritte) {
  stepper.moveTo(currentPosition + schritte); // Positive Schritte für Drehung nach rechts
  stepper.runToPosition(); // Bewegung ausführen
    currentPosition += schritte; // Aktualisiere die aktuelle Position

}

void loopp() {
  // Beispiel: Drehung um 200 Schritte nach rechts
  motorRechtsDrehen(200);
  delay(1000); // Wartezeit für Stabilität
  motorLinksDrehen(100);
  delay(1000);
}