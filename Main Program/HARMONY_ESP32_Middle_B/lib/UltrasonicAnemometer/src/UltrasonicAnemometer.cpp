#include "UltrasonicAnemometer.h"

const byte anemometerCommand[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};

UltrasonicAnemometer::UltrasonicAnemometer(int roPin, int diPin, int dePin, int rePin)
    : roPin(roPin), diPin(diPin), dePin(dePin), rePin(rePin),
      ultrasonicAnemometer(roPin, diPin, false), windSpeedMs(NAN), windDirection(-1), directionOffset(0) {}

void UltrasonicAnemometer::begin()
{
  ultrasonicAnemometer.begin(4800);
  pinMode(rePin, OUTPUT);
  pinMode(dePin, OUTPUT);
}

bool UltrasonicAnemometer::readData()
{
  synchronize();
  transmitRequest();
  if (receiveResponse())
  {
    parseData();
    return true; // Data received and parsed successfully
  }
  else
  {
    windSpeedMs = NAN;
    windDirection = NAN;
    return false; // Sensor timeout or incomplete frame
  }
}

float UltrasonicAnemometer::getWindSpeed_ms() const
{
  return windSpeedMs;
}

float UltrasonicAnemometer::getWindSpeed_kph() const
{
  return (!isnan(windSpeedMs)) ? windSpeedMs * 3.6 : NAN;
}

int UltrasonicAnemometer::getWind_Direction() const
{
  if (!isnan(windSpeedMs) && windSpeedMs == 0.0f)
  {
    return 0; // Set wind direction to 0 if wind speed is 0
  }
  else if (!isnan(windDirection))
  {
    int adjustedDirection = windDirection + directionOffset;
    if (adjustedDirection >= 360)
    {
      adjustedDirection -= 360;
    }
    else if (adjustedDirection < 0)
    {
      adjustedDirection += 360;
    }
    return adjustedDirection;
  }
  return NAN;
}

void UltrasonicAnemometer::setDirectionOffset(int offset)
{
  directionOffset = offset;
}

void UltrasonicAnemometer::synchronize()
{
  while (ultrasonicAnemometer.available())
  {
    ultrasonicAnemometer.read();
  }
}

void UltrasonicAnemometer::transmitRequest()
{
  digitalWrite(dePin, HIGH);
  digitalWrite(rePin, HIGH);
  delay(10);

  ultrasonicAnemometer.write(anemometerCommand, sizeof(anemometerCommand));

  digitalWrite(dePin, LOW);
  digitalWrite(rePin, LOW);
}

bool UltrasonicAnemometer::receiveResponse()
{
  unsigned long startTime = millis();
  while (millis() - startTime < 1000)
  {
    if (ultrasonicAnemometer.available() >= 9)
    {
      return true;
    }
  }
  return false;
}

void UltrasonicAnemometer::parseData()
{
  byte index = 0;
  while (ultrasonicAnemometer.available() && index < 9)
  {
    values[index] = ultrasonicAnemometer.read();
    index++;
  }

  parseWindSpeed();
  parseWindDirection();
}

void UltrasonicAnemometer::parseWindSpeed()
{
  int windSpeedInt = int(values[3] << 8 | values[4]);
  windSpeedMs = windSpeedInt / 100.0;
}

void UltrasonicAnemometer::parseWindDirection()
{
  windDirection = int(values[5] << 8 | values[6]);
}
