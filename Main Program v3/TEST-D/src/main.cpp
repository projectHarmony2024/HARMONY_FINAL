#include <Arduino.h>

// Receiver and Sender ESP-D
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

uint8_t LVGL_broadcastAddress[] = {0x30, 0xc9, 0x22, 0x32, 0xb6, 0x14}; // MAC Address of LVGL
// constexpr char WIFI_SSID[] = "realme 3 Pro";

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
  int hour;
  // Add more fields if needed
} SensorsData;
SensorsData sensorsData;

void blinkLED(int);
ulong previousMillis = 0, previousMillis1 = 0, prevMillis = 0;
const int LED_PIN = LED_BUILTIN;
bool dataReceived = false;

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&sensorsData, incomingData, sizeof(sensorsData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.printf("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%s,%s,%d\n",
                sensorsData.SolarVoltage,
                sensorsData.SolarCurrent,
                sensorsData.WindVoltage,
                sensorsData.WindCurrent,
                sensorsData.WindSpeed_MS,
                sensorsData.WindDirection,
                sensorsData.BatteryVoltage,
                sensorsData.BatteryPercentage,
                sensorsData.brgyVoltage,
                sensorsData.brgyCurrent,
                sensorsData.brgyPower,
                sensorsData.brgyEnergy,
                sensorsData.brgyPowerFactor,
                sensorsData.healthVoltage,
                sensorsData.healthCurrent,
                sensorsData.healthPower,
                sensorsData.heatlhEnergy,
                sensorsData.healthPowerFactor,
                sensorsData.daycareVoltage,
                sensorsData.daycareCurrent,
                sensorsData.daycarePower,
                sensorsData.daycareEnergy,
                sensorsData.daycarePowerFactor,
                sensorsData.time,
                sensorsData.date,
                sensorsData.hour);
  dataReceived = true;
}

// int32_t getWiFiChannel(const char *ssid)
// {
//   if (int32_t n = WiFi.scanNetworks())
//   {
//     for (uint8_t i = 0; i < n; i++)
//     {
//       if (!strcmp(ssid, WiFi.SSID(i).c_str()))
//       {
//         return WiFi.channel(i);
//       }
//     }
//   }
//   return 0;
// }

esp_now_peer_info_t peerInfo_LVGL;
void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.mode(WIFI_STA);

  // int32_t channel = getWiFiChannel(WIFI_SSID);
  // esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
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
  if (dataReceived && (millis() - prevMillis >= 100))
  {
    blinkLED(25);
    dataReceived = false;
  }

  if (millis() - previousMillis >= 1000)
  {
    previousMillis = millis();

    // Send data to LVGL
    esp_err_t result = esp_now_send(LVGL_broadcastAddress, (uint8_t *)&sensorsData, sizeof(sensorsData));
    if (result == ESP_OK)
    {
      Serial.println("Sent to LVGL successfully");
    }
  }
}

void blinkLED(int interval)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(interval);
  digitalWrite(LED_BUILTIN, LOW);
}
