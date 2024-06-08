#include <Arduino.h>

#define ledPin 33

void analogBlink() {
    for (int i = 0; i < 255; i++)
    {
        /* code */
        analogWrite(ledPin, i);
        delay(5);
    }
}