#include <SoftwareSerial.h>

#define DI 13
#define DE 12
#define RE 14
#define RO 27
#define MAX485 26

const byte anemometer[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B };
byte values[9];

SoftwareSerial ultrasonicAnemometer(RO, DI, false);

float TotalWindSpeed_ms = 0;
float avg_direction_degrees = 0;

int wind_directions[5];

int counter = 0;


void setupUltrasonicAnemometer() {
  ultrasonicAnemometer.begin(4800);

  pinMode(MAX485, OUTPUT);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  digitalWrite(MAX485, HIGH);
  memset(wind_directions, 0, sizeof(wind_directions));
}

void syncAnemometerBytes() {
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

void readAndTransmitUltrasonicAnemometer() {
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);

  ultrasonicAnemometer.write(anemometer, sizeof(anemometer));

  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(10);
}

void checkUltrasonicAnemometerNumBytes() {
  unsigned long startTime = millis();
  while (ultrasonicAnemometer.available() < 9 && millis() - startTime < 1000) {
    delay(1);
  }
}

void windDirectionUnitVectorAlgo() {
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
  avg_direction_degrees = avg_direction_radians * 180.0 / PI;

  // Ensure result is in the range 0-359
  if (avg_direction_degrees < 0) {
    avg_direction_degrees += 360;
  }

  // Print the result
  Serial.print("Average wind direction: ");
  Serial.println(avg_direction_degrees);

  memset(wind_directions, 0, sizeof(wind_directions));
}

void readDataUltrasonicAnemometer() {
  if (ultrasonicAnemometer.available() >= 9) {

    // Read the response
    byte index = 0;
    while (ultrasonicAnemometer.available() && index < 9) {
      values[index] = ultrasonicAnemometer.read();
      index++;
    }

    // Parse the Wind Speed value
    int Wind_Speed_Int = int(values[3] << 8 | values[4]);
    float Wind_Speed_m_s = Wind_Speed_Int / 100.0;

    Serial.print("Wind Speed: ");
    Serial.print(Wind_Speed_m_s);
    Serial.print(" m/s    |     ");

    // Parse the Wind Direction value
    int Wind_Direction = int(values[5] << 8 | values[6]);
    Serial.print("Wind Direction: ");
    Serial.println(Wind_Direction);

    TotalWindSpeed_ms = TotalWindSpeed_ms + Wind_Speed_m_s;
    wind_directions[counter] = Wind_Direction;

    counter++;

    if ((Firebase.ready() && counter >= 5) || counter >= 5) {
      for(int i = 0; i < counter; i++){
        Serial.println(wind_directions[i]);
      }

      windDirectionUnitVectorAlgo();
      float AveWindSpeed_ms = TotalWindSpeed_ms / 5;
      float AveWindSpeed_kph = AveWindSpeed_ms * 3.6;

      Serial.println("--------------------------------------");
      sendToDbFloat("anemometer/AveWindDirection", avg_direction_degrees);
      sendToDbFloat("anemometer/AveWindSpeed_ms", AveWindSpeed_ms);
      sendToDbFloat("anemometer/AveWindSpeed_kph", AveWindSpeed_kph);
      Serial.println("--------------------------------------");

      TotalWindSpeed_ms = 0;
      avg_direction_degrees = 0;
      counter = 0;
    }
    

  } else {
    Serial.println("Sensor timeout or incomplete frame");
  }
}