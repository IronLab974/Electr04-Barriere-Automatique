#include <Servo.h>

// Déclaration du servo
Servo barriereServo;

// Définition des pins
const int trigPin = 4;      // Pin Trigger du HC-SR04
const int echoPin = 3;     // Pin Echo du HC-SR04
const int ledRouge = 11;     // LED rouge
const int ledVerte = 10;     // LED verte
const int servoPin = 9;     // Servo moteur MG996R

// Distance minimale pour détecter un obstacle (ici 5 cm)
const int distanceSeuil = 5;

void setup() {
  Serial.begin(9600);             // Initialisation de la communication série
  pinMode(trigPin, OUTPUT);       // Trigger en sortie
  pinMode(echoPin, INPUT);        // Echo en entrée
  pinMode(ledRouge, OUTPUT);      // LED rouge en sortie
  pinMode(ledVerte, OUTPUT);      // LED verte en sortie

  barriereServo.attach(servoPin); // Attacher le servo au pin défini
  barriereServo.write(90);        // Barrière initialement fermée (position 90°)
}

void loop() {
  // Envoi de l'impulsion sur le trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lecture de la durée de l'impulsion Echo
  long duree = pulseIn(echoPin, HIGH);

  // Conversion du temps en distance (cm)
  int distance = duree * 0.034 / 2;

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= distanceSeuil) {
    // Objet détecté à proximité
    digitalWrite(ledRouge, LOW);     // Éteindre la LED rouge
    digitalWrite(ledVerte, HIGH);    // Allumer la LED verte
    barriereServo.write(90);          // Ouvrir la barrière (0°)
    delay(2000);                     // On attend 2 secondes
  } else {
    // Pas d'objet détecté
    digitalWrite(ledRouge, HIGH);    // Allumer la LED rouge
    digitalWrite(ledVerte, LOW);     // Éteindre la LED verte
    barriereServo.write(0);         // Fermer la barrière (90°)
  }

  delay(200); // Délai pour éviter les déclenchements trop fréquents
}