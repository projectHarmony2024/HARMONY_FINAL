#include <Arduino.h>

int ledPin = 33;

void setupLED() {
    pinMode(ledPin, OUTPUT);
}

void blinkLED() {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
}