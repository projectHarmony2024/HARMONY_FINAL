//   SD CARD PINOUT
//  VCC   =   5V
//  GND   =   GND
//  CS    =   PIN 5
//  MOSI  =   PIN 23
//  CLK   =   PIN 18
//  MISO  =   PIN 19


#include <SD.h>
#include <SPI.h>

/* DEBUGGING */
#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#define debugf(x, y) Serial.printf(x, y);
#else
#define debug(x)
#define debugln(x)
#define debugf(x)
#endif

// Define the chip select pin for the SD card module
#define SD_CS_PIN 5

File dataFile;

void setup() {
  Serial.begin(115200);
  
  // Initialize SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed.");
    return;
  }
  Serial.println("SD card initialized successfully.");
  
  // Open a file for writing
  dataFile = SD.open("/test.txt", FILE_WRITE);
}

void loop() {
  // Check if the file opened successfully
  
  if (!dataFile) {
    Serial.println("Error opening file.");
  } else {
    Serial.println("File opened successfully.");
    // Write some data to the file
    dataFile.println("Hello, SD card!");
    dataFile.println("This is a test file.");
    dataFile.close(); // Close the file
    Serial.println("Data written to file.");
  }
  delay(5000);
}
