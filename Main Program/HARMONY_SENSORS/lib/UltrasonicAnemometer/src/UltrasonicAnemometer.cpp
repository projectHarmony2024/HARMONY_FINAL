#include "UltrasonicAnemometer.h"

const byte anemometerCommand[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};

UltrasonicAnemometer::UltrasonicAnemometer(int roPin, int diPin, int dePin, int rePin, int max485VCC_Pin) : roPin(roPin), diPin(diPin), dePin(dePin), rePin(rePin), max485VCC_Pin(max485VCC_Pin),
                                                                                                            ultrasonicAnemometer(roPin, diPin, false), windSpeedMs(-1), windDirection(-1), directionOffset(0) {}

void UltrasonicAnemometer::begin()
{
  ultrasonicAnemometer.begin(4800);
  pinMode(max485VCC_Pin, OUTPUT);
  pinMode(rePin, OUTPUT);
  pinMode(dePin, OUTPUT);
  digitalWrite(max485VCC_Pin, HIGH);
}

int UltrasonicAnemometer::readData()
{
  synchronize();
  transmitRequest();
  if (receiveResponse())
  {
    parseData();
    return 1; // Data received and parsed successfully
  }
  else
  {
    windSpeedMs = 0;
    windDirection = 0;
    return sqrt(-1); // Sensor timeout or incomplete frame
  }
}

float UltrasonicAnemometer::getWindSpeed_ms() const
{
  return windSpeedMs;
}

float UltrasonicAnemometer::getWindSpeed_kph() const
{
  return (windSpeedMs != -1) ? windSpeedMs * 3.6 : -1;
}

int UltrasonicAnemometer::getWind_Direction() const
{
  if (windSpeedMs != -1 && windSpeedMs == 0.0f)
  {
    // Set wind direction to 0 if wind speed is 0
    return 0;
  }
  else if (windDirection != -1)
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
  return -1;
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
