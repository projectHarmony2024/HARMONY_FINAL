#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

/* --------- DEBUGGING MODES --------- */

#ifndef DEBUG

// Completely disable debug functionality when DEBUG is not defined
void debug_Init(int baudrate) {}  // Empty function to avoid potential linker errors
#define debugf(...)  // Do nothing (empty macro)

#else  // DEBUG is defined

// Function-like macro with variadic arguments for debugf
#define debugf(...)  \
  if (Serial) {      \
    Serial.print(__VA_ARGS__);  \
  }

// Separate initialization for debug (optional)
void debug_Init(int baudrate) {
  if (Serial) {
    Serial.begin(baudrate);
  }
}

#endif // DEBUG

#endif // DEBUG_H
