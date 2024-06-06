#include <Arduino.h>

#if DEBUG == 1
#define debug_init(baudrate) Serial.begin(baudrate)
#define debug(...) Serial.print(__VA_ARGS__)
#define debugln(...) Serial.println(__VA_ARGS__)
#define debugf(...) Serial.printf(__VA_ARGS__)
#else
#define debug_init(baudrate)
#define debug(...)
#define debugln(...)
#define debugf(...)
#endif