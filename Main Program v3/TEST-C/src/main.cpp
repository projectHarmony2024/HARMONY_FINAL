#include <Arduino.h>

// Receiver and Sender ESP-C
#include <esp_now.h>
#include <WiFi.h>

uint8_t ESP_D_broadcastAddress[] = {0x24, 0xdc, 0xc3, 0x43, 0xe0, 0x30}; // MAC Address of ESP-D
uint8_t LVGL_broadcastAddress[] = {0x30, 0xc9, 0x22, 0x32, 0xb6, 0x14};  // MAC Address of LVGL
typedef struct SensorsData
{
  float SolarVoltage;
  float SolarCurrent;

  float WindVoltage;
  float WindCurrent;
  float WindSpeed_MS;
  int WindDirection;

  float BatteryVoltage;
  float BatteryPercentage;

  float brgyVoltage;
  float brgyCurrent;
  float brgyPower;
  float brgyEnergy;
  float brgyPowerFactor;

  float healthVoltage;
  float healthCurrent;
  float healthPower;
  float heatlhEnergy;
  float healthPowerFactor;

  float daycareVoltage;
  float daycareCurrent;
  float daycarePower;
  float daycareEnergy;
  float daycarePowerFactor;

  String time;
  String date;
  // Add more fields if needed
} SensorsData;
SensorsData sensorsData;

typedef struct SensorsData1
{
  float SolarVoltage;
  float SolarCurrent;

  float WindVoltage;
  float WindCurrent;
  float WindSpeed_MS;
  int WindDirection;

  float BatteryVoltage;
  float BatteryPercentage;

  float brgyVoltage;
  float brgyCurrent;
  float brgyPower;
  float brgyEnergy;
  float brgyPowerFactor;

  float healthVoltage;
  float healthCurrent;
  float healthPower;
  float heatlhEnergy;
  float healthPowerFactor;

  float daycareVoltage;
  float daycareCurrent;
  float daycarePower;
  float daycareEnergy;
  float daycarePowerFactor;

  String time;
  String date;
  // Add more fields if needed

  // Assignment operator to assign SensorsData to SensorsData1
  SensorsData1 &operator=(const SensorsData &data)
  {
    SolarVoltage = data.SolarVoltage;
    SolarCurrent = data.SolarCurrent;

    WindVoltage = data.WindVoltage;
    WindCurrent = data.WindCurrent;
    WindSpeed_MS = data.WindSpeed_MS;
    WindDirection = data.WindDirection;

    BatteryVoltage = data.BatteryVoltage;
    BatteryPercentage = data.BatteryPercentage;

    brgyVoltage = data.brgyVoltage;
    brgyCurrent = data.brgyCurrent;
    brgyPower = data.brgyPower;
    brgyEnergy = data.brgyEnergy;
    brgyPowerFactor = data.brgyPowerFactor;

    healthVoltage = data.healthVoltage;
    healthCurrent = data.healthCurrent;
    healthPower = data.healthPower;
    heatlhEnergy = data.heatlhEnergy;
    healthPowerFactor = healthPowerFactor;

    daycareVoltage = data.daycareVoltage;
    daycareCurrent = data.daycareCurrent;
    daycarePower = data.daycarePower;
    daycareEnergy = data.daycareEnergy;
    daycarePowerFactor = data.daycarePowerFactor;

    time = data.time;
    date = data.date;

    return *this;
  }

} SensorsData1;
SensorsData1 sensorsData1;

esp_now_peer_info_t peerInfo_ESP_D;
esp_now_peer_info_t peerInfo_LVGL;

const int LED_PIN = LED_BUILTIN;
bool blinking = false;
int blinkCount = 0;
int blinkTimes = 0;
unsigned long blinkInterval = 0;
unsigned long lastBlinkTime = 0;
bool dataReceived = false;
ulong previousMillis = 0;

void blinkLED(int, int);
void handleBlinking();

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&sensorsData, incomingData, sizeof(sensorsData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.printf("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d,%0.2f,%0.2f\n",
                sensorsData.SolarVoltage,
                sensorsData.SolarCurrent,
                sensorsData.WindVoltage,
                sensorsData.WindCurrent,
                sensorsData.WindSpeed_MS,
                sensorsData.WindDirection,
                sensorsData.BatteryVoltage,
                sensorsData.BatteryPercentage);
  sensorsData1 = sensorsData;

  blinkLED(1, 25);

  // Set dataReceived flag and record the current time
  dataReceived = true;
  previousMillis = millis();
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Add peer: ESP-D
  memcpy(peerInfo_ESP_D.peer_addr, ESP_D_broadcastAddress, 6);
  peerInfo_ESP_D.channel = 0;
  peerInfo_ESP_D.encrypt = false;
  if (esp_now_add_peer(&peerInfo_ESP_D) != ESP_OK)
  {
    Serial.println("Failed to add ESP-D");
    return;
  }

  // Add peer: LVGL
  memcpy(peerInfo_LVGL.peer_addr, LVGL_broadcastAddress, 6);
  peerInfo_LVGL.channel = 0;
  peerInfo_LVGL.encrypt = false;
  if (esp_now_add_peer(&peerInfo_LVGL) != ESP_OK)
  {
    Serial.println("Failed to add LVGL");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
  handleBlinking();

  if (dataReceived && (millis() - previousMillis >= 100))
  {
    // Send data to ESP-D
    esp_err_t result = esp_now_send(ESP_D_broadcastAddress, (uint8_t *)&sensorsData1, sizeof(sensorsData1));
    if (result == ESP_OK)
    {
      Serial.println("Sent to ESP-D successfully");
    }

    // Send data to LVGL
    esp_err_t result1 = esp_now_send(LVGL_broadcastAddress, (uint8_t *)&sensorsData1, sizeof(sensorsData1));
    if (result1 == ESP_OK)
    {
      Serial.println("Sent to LVGL successfully");
    }

    // Reset the flag
    dataReceived = false;
  }
}

void blinkLED(int count, int interval)
{
  blinking = true;
  blinkCount = 0;
  blinkTimes = count * 2;
  blinkInterval = interval;
  lastBlinkTime = millis();
}

void handleBlinking()
{
  if (blinking && (millis() - lastBlinkTime >= blinkInterval))
  {
    lastBlinkTime = millis();
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    blinkCount++;

    if (blinkCount >= blinkTimes)
    {
      blinking = false;
      digitalWrite(LED_PIN, LOW);
    }
  }
}
