#define DI 13
#define DE 12
#define RE 14
#define RO 27
#define MAX485 26

float TotalWindSpeed_ms = 0;
float TotalWindSpeed_kph = 0;
float TotalWindDirection = 0;

int counter = 0;

const byte anemometer[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B };
byte values[9];

SoftwareSerial ultrasonicAnemometer(RO, DI, false);

void ultrasonicAnemometer_bytesync() {
  while (true) {
    // Check for the start of frame marker
    if (ultrasonicAnemometer.peek() == -1) {
      // Start of frame detected, exit the synchronization loop
      break;
    }
    // Discard any bytes until the start of frame is found
    ultrasonicAnemometer.read();
  }
}

void ultrasonicAnemometerWrite() {
  ultrasonicAnemometer.write(anemometer, sizeof(anemometer));
}

void checkUltrasonicAnemometerBytes() {
  unsigned long startTime = millis();
  while (ultrasonicAnemometer.available() < 9 && millis() - startTime < 1000) {
    delay(1);
  }
}

void readUltrasonicAnemometer() {
  if (ultrasonicAnemometer.available() >= 9) {
    // Parse the Wind Speed and direction value
    int Wind_Speed_Int = int(values[3] << 8 | values[4]);
    float Wind_Speed_m_s = Wind_Speed_Int / 100.0;
    float Wind_Speed_kph = Wind_Speed_m_s * 3.6;  // Conversion to km/h
    float Wind_Direction = int(values[5] << 8 | values[6]);


    if (counter > 4) {
      TotalWindSpeed_ms = 0;
      TotalWindSpeed_kph = 0;
      TotalWindDirection = 0;
    }

    counter++;

    TotalWindSpeed_ms = TotalWindSpeed_ms + Wind_Speed_m_s;
    TotalWindSpeed_kph = TotalWindSpeed_kph + Wind_Speed_kph;
    TotalWindDirection = TotalWindDirection + Wind_Direction;

    Serial.print(Wind_Speed_m_s);
    Serial.print(" m/s    |    ");
    Serial.print(Wind_Direction);
    Serial.println(" degrees");

    

  } else {
    Serial.println("Sensor timeout or incomplete frame");
  }
}
