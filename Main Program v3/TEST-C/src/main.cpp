#include <Arduino.h>

// Receiver and Sender ESP-C
#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

uint8_t ESP_D_broadcastAddress[] = {0x24, 0xdc, 0xc3, 0x43, 0xe0, 0x30}; // MAC Address of ESP-D
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

  String time;
  String date;
  int hour;
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
  int hour;
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

    time = data.time;
    date = data.date;
    hour = data.hour;

    return *this;
  }

} SensorsData1;
SensorsData1 sensorsData1;

esp_now_peer_info_t peerInfo_ESP_D;

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

#include <PZEM004Tv30.h>
#define healthPZEM_RX 16
#define healthPZEM_TX 17
PZEM004Tv30 healthPZEM(Serial1, healthPZEM_RX, healthPZEM_TX);
#define daycarePZEM_RX 32
#define daycarePZEM_TX 33
PZEM004Tv30 daycarePZEM(Serial2, daycarePZEM_RX, daycarePZEM_TX);

const int LED_PIN = LED_BUILTIN;
bool dataReceived = false;
ulong previousMillis = 0, previousMillis1 = 0, prevMillis = 0;

void blinkLED(int);

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&sensorsData, incomingData, sizeof(sensorsData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.printf("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%s,%s,%d\n",
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
                sensorsData.time,
                sensorsData.date,
                sensorsData.hour);
  sensorsData1 = sensorsData;
  dataReceived = true;
}


void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);

  // int32_t channel = getWiFiChannel(WIFI_SSID);
  // esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);


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

  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
  float healthVoltage = healthPZEM.voltage();
  float healthCurrent = healthPZEM.current();
  float healthPower = healthPZEM.power();
  float healthEnergy = healthPZEM.energy();
  float healthPowerFactor = healthPZEM.pf();
  float daycareVoltage = daycarePZEM.voltage();
  float daycareCurrent = daycarePZEM.current();
  float daycarePower = daycarePZEM.power();
  float daycareEnergy = daycarePZEM.energy();
  float daycarePowerFactor = daycarePZEM.pf();

  sensorsData1.healthVoltage = healthVoltage;
  sensorsData1.healthCurrent = healthCurrent;
  sensorsData1.healthPower = healthPower;
  sensorsData1.heatlhEnergy = healthEnergy;
  sensorsData1.healthPowerFactor = healthPowerFactor;
  sensorsData1.daycareVoltage = daycareVoltage;
  sensorsData1.daycareCurrent = daycareCurrent;
  sensorsData1.daycarePower = daycarePower;
  sensorsData1.daycareEnergy = daycareEnergy;
  sensorsData1.daycarePowerFactor = daycarePowerFactor;

  if (dataReceived && (millis() - prevMillis >= 100))
  {
    blinkLED(25);
    dataReceived = false;
  }

  if (millis() - previousMillis >= 100)
  {
    previousMillis = millis();
    // Send data to ESP-D
    esp_err_t result = esp_now_send(ESP_D_broadcastAddress, (uint8_t *)&sensorsData1, sizeof(sensorsData1));
    if (result == ESP_OK)
    {
      Serial.println("Sent to ESP-D successfully");
    }
  }
}

void blinkLED(int interval)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(interval);
  digitalWrite(LED_BUILTIN, LOW);
}