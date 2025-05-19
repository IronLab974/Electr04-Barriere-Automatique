#include <Servo.h>

Servo myServo;  // Création de l'objet servo

const int potPin = 0;    // Broche du potentiomètre
int potValue = 0;         // Valeur analogique lue
int angle = 0;            // Position convertie

void setup() {
  myServo.attach(9);      // Branchement du servo sur la broche D9
}

void loop() {
  potValue = analogRead(potPin);            // Lecture de la valeur du potentiomètre
  angle = map(potValue, 0, 1023, 0, 180);   // Conversion en angle pour le servo
  myServo.write(angle);                     // Déplacement du servo à l'angle donné
  delay(15);                                // Pause pour laisser le temps au servo de bouger
}