/*
PINNEN

HC-SR04  ->  Level converter 

Vcc          HV
Trig         HV2
Echo         HV1
GND          GND

Power Supply 5V -> Level converter
+                  HV
-                  GND

Level converter  ->  ESP32
LV                   3V3
LV2                  D4
LV1                  D2
GND                  GND
*/

#include "Arduino.h"
#define triggerPin 4      // pin voor de trigger
#define echoPin 2         // pin voor de echo
#define soundSpeed 343.0  // snelheid van het geluid (m/s)

// init variables
long echoTime = 0;
float distance = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wacht op seriele monitor
  }
  Serial.println("--- Seriele monitor gestart ---");
  pinMode(triggerPin, OUTPUT);  // zet trigger pin als uitgang
  pinMode(echoPin, INPUT);      // zet echo pin als ingang
}

void loop() {
  // zend startpuls (trigger)
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // meet lengte van de echo puls
  echoTime = pulseInLong(echoPin, HIGH);
  // en bereken hiermee de afstand (in cm)
  distance = float(echoTime) / 2 * (soundSpeed / 10000.0);
  // en geef weer op de seriele monitor
  Serial.print("Afstand = ");
  Serial.print((String)distance);
  Serial.println(" cm");

  // wacht 500ms
  delay(500);
}