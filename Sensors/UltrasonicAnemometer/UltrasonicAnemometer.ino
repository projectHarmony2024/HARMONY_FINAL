//  ULTRASONIC ANEMOMETER PINOUT
//      VCC   =   10-30V
//      GND   =   GND
//      DI    =   PIN 13
//      DE    =   PIN 12
//      RE    =   PIN 14
//      RO    =   PIN 27
//    MAX485  =   pin 26 (MAX485 VCC)

#include <SoftwareSerial.h>

#define baudRate 115200
#define DI 13
#define DE 12
#define RE 14
#define RO 27
#define MAX485 26

const byte anemometer[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B };
byte values[9];

SoftwareSerial ultrasonicAnemometer(RO, DI, false);

float TotalWindSpeed_ms = 0;
float TotalWindSpeed_kph = 0;
float TotalWindDirection = 0;
int wind_directions[5];
int counter = 0;

void setup() {
  Serial.begin(baudRate);
  ultrasonicAnemometer.begin(4800);
  pinMode(MAX485, OUTPUT);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  Serial.print("Initializing Ultrasonic Anemometer");
  for (int i = 0; i < 10; i++) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  digitalWrite(MAX485, HIGH);
}

void loop() {
  // Synchronization loop: Wait until the start of a new data frame is detected
  Serial.println("---");
  // Serial.println(ultrasonicAnemometer.peek());

  while (true) {
    // Check for the start of frame marker
    if (ultrasonicAnemometer.peek() == -1) {
      // Start of frame detected, exit the synchronization loop
      break;
    }
    // Discard any bytes until the start of frame is found
    ultrasonicAnemometer.read();

    memset(wind_directions, 0, sizeof(wind_directions));
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
      // Serial.print(values[index], HEX);
      // Serial.print(" ");
      index++;
    }
    // Serial.println();



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

    wind_directions[counter] = Wind_Direction;
    counter++;

    if (counter >= 5) {
      float u_sum = 0;
      float v_sum = 0;

      for (int i = 0; i < counter; i++) {
        // Convert wind direction to radians
        float radians = wind_directions[i] * PI / 180.0;

        // Calculate u and v components
        float u = sin(radians);
        float v = cos(radians);

        // Accumulate u and v
        u_sum += u;
        v_sum += v;
      }

      // Compute average wind direction in radians
      float avg_direction_radians = atan2(u_sum, v_sum);

      // Convert back to degrees
      float avg_direction_degrees = avg_direction_radians * 180.0 / PI;

      // Ensure result is in the range 0-359
      if (avg_direction_degrees < 0) {
        avg_direction_degrees += 360;
      }

      // Print the result
      Serial.print("Average wind direction: ");
      Serial.println(avg_direction_degrees);

      counter = 0;
      memset(wind_directions, 0, sizeof(wind_directions));
    }

  } else {
    Serial.println("Sensor timeout or incomplete frame");
    TotalWindSpeed_ms = 0;
  }
}