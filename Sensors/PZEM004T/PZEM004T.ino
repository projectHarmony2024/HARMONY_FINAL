//   PZEM004T PINOUT
//    VCC   =   5V
//    GND   =   GND
//    TX    =   PIN 16 (black)
//    RX    =   PIN 17 (white)

#include <PZEM004Tv30.h>
#include <HardwareSerial.h>  // Include the ESP32 Hardware Serial library

#define TX_PIN 16
#define RX_PIN 17

PZEM004Tv30 pzem(&Serial2, TX_PIN, RX_PIN);  //HardwareSerial pointer, TX pin, RX pin


void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, TX_PIN, RX_PIN);  // Initialize Serial2 with baud rate and pins
}

void loop() {
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();

  if (!isnan(voltage) || !isnan(current) || !isnan(power) || !isnan(energy) || !isnan(frequency) || !isnan(pf)) {
    Serial.print("V: ");
    Serial.print(voltage);
    Serial.print("  I: ");
    Serial.print(current);
    Serial.print("  P: ");
    Serial.print(power, 3);
    Serial.print("  E: ");
    Serial.print(energy, 1);
    Serial.print("  f: ");
    Serial.print(frequency);
    Serial.print("  pf: ");
    Serial.print(pf);
  } else {
    Serial.println("Error reading PZEM");
  }

  Serial.println();
  delay(2000);
}
