//   PZEM004T PINOUT
//    VCC   =   5V
//    GND   =   GND
//    TX    =   PIN 16
//    RX    =   PIN 17

#include <PZEM004Tv30.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>

#define RX1 2
#define TX1 3
#define RX2 16
#define TX2 17
#define RX3 0
#define TX3 4

SoftwareSerial PZEMSerial3(RX3, TX3);

PZEM004Tv30 PZEM1(&Serial1, TX1, RX1); // HardwareSerial pointer, TX pin, RX pin
PZEM004Tv30 PZEM2(&Serial2, RX2, TX2); // HardwareSerial pointer, TX pin, RX pin
PZEM004Tv30 PZEM3(PZEMSerial3);

void PZEM004T_init()
{
    Serial2.begin(9600, SERIAL_8N1, 16, 17); // Initialize Serial2 with baud rate and pins
}

float PZEM004T_Voltage(int facility)
{
    float voltage;
    switch (facility)
    {
    case 1:
        voltage = PZEM1.voltage();
        break;
    case 2:
        voltage = PZEM2.voltage();
        break;
    case 3:
        voltage = PZEM3.voltage();
        break;
    }
    return voltage;
}

void loop()
{
    float voltage = PZEM2.voltage();
    float current = PZEM2.current();
    float power = PZEM2.power();
    float energy = PZEM2.energy();
    float frequency = PZEM2.frequency();
    float pf = PZEM2.pf();

    if (!isnan(voltage) || !isnan(current) || !isnan(power) || !isnan(energy) || !isnan(frequency) || !isnan(pf))
    {
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
    }
    else
    {
        Serial.println("Error reading PZEM");
    }

    Serial.println();
    delay(2000);
}
