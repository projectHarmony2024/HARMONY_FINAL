#include <Arduino.h>

 /*
Watch video instruction for this code on YouTube https://youtu.be/znBiVlgV9JI
Resource page for this lesson and code:
http://robojax.com/course3
Tutoril by https://youTube.com/@robojax

/*
Arduino code for ESP32 to measure any DC voltage
written by Ahmad Shamshiri
www.robojax.com
Feb 19, 2024
*/
bool debug = true;
const int R1 = 7500;//we read the voltage acrosst this resistor ()
const int R2 = 29655;

const int VinPin = 26; // Potentiometer connected to GPIO14


// PWM settings
const int freq = 5000; // PWM frequency
const int resolution = 12; // PWM resolution (bits)
const int channel = 0; // PWM channel

float VB1;
int mV;

void readVoltage();
void maxVoltage();
void calculateResistor(int r1, float voltage);

void setup() {
  Serial.begin(115200);
  // Configure PWM
  ledcSetup(channel, freq, resolution);
  //calculatResistor(R1, 24);//10000 ohm and 35.0V

}



void loop() {
  readVoltage();

  Serial.print("VB1 Voltage: ");
  Serial.print(VB1); // Convert millivolts to volts
  Serial.println("V ");


  delay(500);
}

void readVoltage()
{
  uint32_t voltage_mV = analogReadMilliVolts(VinPin); // Read the voltage in millivolts
  if(debug)
  {
    maxVoltage();
    Serial.print("PinVoltage: ");
    Serial.print(voltage_mV);
    Serial.println("mV");
    Serial.println();//this adds a new line
  }
  mV = voltage_mV;
  VB1 = (((float) voltage_mV) / 1000.0)  * (1 + (float)R2/(float)R1);
}

/*
prints maximum volage
*/
void maxVoltage()
{
  float maxVoltage = ( 3.1)  * (1 + (float)R2/(float)R1);
    Serial.print("****Maximum Voltage: ");
    Serial.print(maxVoltage);
    Serial.println("V");

}//maxVoltage() end

void calculatResistor(int r1, float voltage)
{
    Serial.print("Calculating R2 when R1 is :");
    Serial.print(r1);
    Serial.print(" Ohms and Maximum Input Voltage is ");  
    Serial.print(voltage);  
    Serial.println("V");  
    Serial.print("***** R2 Should Be ");  
    float r2 = (voltage - 3.1)/ (3.1/ (float)r1);
    Serial.print(r2 / 1000.0);  
    Serial.println(" kilo Ohms");  
    while(1);
}