#include <Arduino.h>

#include <HardwareSerial.h>
#define RX_pin 16
#define TX_pin 17
HardwareSerial ESP32_A(1); // UART1 (Serial1) channel

#include <esp_now.h>
#include <WiFi.h>
uint8_t ESP_C_broadcastAddress[] = {0xfc, 0xb4, 0x67, 0xf1, 0xbf, 0x6c}; // MAC Address of ESP-C
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
  // Add more fields if needed
} SensorsData;
SensorsData sensorsData;

esp_now_peer_info_t peerInfo_ESP_C;

#include <PZEM004Tv30.h>
#define brgyPZEM_RX 32
#define brgyPZEM_TX 33
PZEM004Tv30 brgyPZEM(Serial2, brgyPZEM_RX, brgyPZEM_TX); // UART2 (Serial2) channel

void blinkLED(int);

void setup()
{
  Serial.begin(115200);
  ESP32_A.begin(115200, SERIAL_8N1, TX_pin, RX_pin);
  pinMode(LED_BUILTIN, OUTPUT); // Recieved Indicator

  /* Initialize ESP-NOW */
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  memcpy(peerInfo_ESP_C.peer_addr, ESP_C_broadcastAddress, 6);
  peerInfo_ESP_C.channel = 0;
  peerInfo_ESP_C.encrypt = false;
  if (esp_now_add_peer(&peerInfo_ESP_C) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
}

ulong previousMillis = 0;

void loop()
{
  float brgyVoltage = brgyPZEM.voltage();
  float brgyCurrent = brgyPZEM.current();
  float brgyPower = brgyPZEM.power();
  float brgyEnergy = brgyPZEM.energy();

  if (ESP32_A.available())
  {
    String message = ESP32_A.readStringUntil('\n');
    Serial.println(message);

    int startIdx = 0;
    int endIdx = message.indexOf(',');
    sensorsData.SolarVoltage = message.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = message.indexOf(',', startIdx);
    sensorsData.SolarCurrent = message.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = message.indexOf(',', startIdx);
    sensorsData.WindVoltage = message.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = message.indexOf(',', startIdx);
    sensorsData.WindCurrent = message.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = message.indexOf(',', startIdx);
    sensorsData.WindSpeed_MS = message.substring(startIdx, endIdx).toFloat();

    startIdx = endIdx + 1;
    endIdx = message.indexOf(',', startIdx);
    sensorsData.WindDirection = message.substring(startIdx, endIdx).toInt();

    startIdx = endIdx + 1;
    endIdx = message.indexOf(',', startIdx);
    sensorsData.BatteryVoltage = message.substring(startIdx, endIdx).toFloat();

    blinkLED(25);
  }

  if ((millis() - previousMillis >= 100))
  {
    previousMillis = millis();
    Serial.printf("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d,%0.2f,%0.2f\n",
                  sensorsData.SolarVoltage,
                  sensorsData.SolarCurrent,
                  sensorsData.WindVoltage,
                  sensorsData.WindCurrent,
                  sensorsData.WindSpeed_MS,
                  sensorsData.WindDirection,
                  sensorsData.BatteryVoltage,
                  sensorsData.BatteryPercentage);
    esp_err_t result = esp_now_send(ESP_C_broadcastAddress, (uint8_t *)&sensorsData, sizeof(sensorsData));
    Serial.println("Sent to ESP-C Successfully!");
  }
}

void blinkLED(int interval)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(interval);
  digitalWrite(LED_BUILTIN, LOW);
}
