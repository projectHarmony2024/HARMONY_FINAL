#include <SoftwareSerial.h>

#define baudRate 9600
#define DI 8
#define DE 9
#define RE 10
#define RO 11

const byte anemometer[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B };
byte values[9];
SoftwareSerial ultrasonicAnemometer(RO, DI, false);

void setup() {
  Serial.begin(baudRate);
  ultrasonicAnemometer.begin(4800);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  Serial.print("Initializing Ultrasonic Anemometer");
  for (int i=0; i<10; i++) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  
}

void loop() {
  // Synchronization loop: Wait until the start of a new data frame is detected
  Serial.println("---");
  Serial.println(ultrasonicAnemometer.peek());
  while (true) {
    // Check for the start of frame marker
    if (ultrasonicAnemometer.peek() == -1) {
      // Start of frame detected, exit the synchronization loop
      break;
    }
    // Discard any bytes until the start of frame is found
    ultrasonicAnemometer.read();
  }

  // Now that synchronization is achieved, proceed to read the rest of the data frame
  // Transmit the request to the sensor
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);

  ultrasonicAnemometer.write(anemometer, sizeof(anemometer));

  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(10);

  // Wait until we have the expected number of bytes or timeout
  unsigned long startTime = millis();
  while (ultrasonicAnemometer.available() < 9 && millis() - startTime < 1000) {
    delay(1);
  }

  if (ultrasonicAnemometer.available() >= 9) {
    // Read the response
    byte index = 0;
    while (ultrasonicAnemometer.available() && index < 9) {
      values[index] = ultrasonicAnemometer.read();
      Serial.print(values[index], HEX);
      Serial.print(" ");
      index++;
    }
    Serial.println();

    // Parse the Wind Speed value
    int Wind_Speed_Int = int(values[3] << 8 | values[4]);
    float Wind_Speed_m_s = Wind_Speed_Int / 100.0;
    float Wind_Speed_kph = Wind_Speed_m_s * 3.6;  // Conversion to km/h

    Serial.print("Wind Speed: ");
    Serial.print(Wind_Speed_m_s);
    Serial.println(" m/s");

    // Parse the Wind Direction value
    int Wind_Direction = int(values[5] << 8 | values[6]);
    Serial.print("Wind Direction: ");
    Serial.print(Wind_Direction);
    Serial.println(" degrees");
  } else {
    Serial.println("Sensor timeout or incomplete frame");
  }

  delay(1000);
}