#include <Arduino.h>
#include <ui/ui.h>

#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

#define DEBUG 0

#if DEBUG == 1
#define debug(x) Serial.print(x);
#define debugln(x) Serial.println(x);
#define debugf(x, y) Serial.printf(x, y);
#else
#define debug(x)
#define debugln(x)
#define debugf(x)
#endif

static const char *ssid = "hehez";
static const char *password = "qwertyuiop";

// Structure to keep data (maximum 250 bytes only)
struct struct_message
{
    // for solar
    double solarVoltage;
    double solarCurrent;
    // for wind
    double windVoltage;
    double windCurrent;
    int windDegrees;
    double windSpeed;
    // for battery
    int batteryPercentage;
    // for brgy hall (PZEM A)
    double brgyHallPower;
    double brgyHallFreq;
    double brgyHallFactor;
    // for health center (PZEM B)
    double healthPower;
    double healthFreq;
    double healthFactor;
    // for daycare center (PZEM C)
    double daycarePower;
    double daycareFreq;
    double daycareFactor;
};

double solarVoltage;
double solarCurrent;
double windVoltage;
double windCurrent;
double windSpeed;
int windDegrees;
int battPercent;
double brgyHall[3] = {};
double healthCenter[3] = {};
double daycare[3] = {};

// Create a struct_message
struct_message myStruct;

// callback function executed when data is received
void OnRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&myStruct, incomingData, sizeof(myStruct));
    debug("Bytes received: ");
    debug(len);

    solarVoltage = myStruct.solarVoltage;
    solarCurrent = myStruct.solarCurrent;
    windVoltage = myStruct.windVoltage;
    windCurrent = myStruct.windCurrent;
    windSpeed = myStruct.windSpeed;
    windDegrees = myStruct.windDegrees;
    battPercent = myStruct.batteryPercentage;
    brgyHall[0] = myStruct.brgyHallPower;
    brgyHall[1] = myStruct.brgyHallFreq;
    brgyHall[2] = myStruct.brgyHallFactor;
    healthCenter[0] = myStruct.healthPower;
    healthCenter[1] = myStruct.healthFreq;
    healthCenter[2] = myStruct.healthFactor;
    daycare[0] = myStruct.daycarePower;
    daycare[1] = myStruct.daycareFreq;
    daycare[2] = myStruct.daycareFactor;
}

void wifiNowSetup()
{
    // Set device as a Wi-Fi AP Station
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, password);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        debugln("There was an error initializing ESP-NOW");
        return;
    }

    // Once the ESP-Now protocol is initialized, we will register the callback function
    // to be able to react when a package arrives in near to real time
    esp_now_register_recv_cb(OnRecv);
}

int blinkState = 0; // 0: red, 1: blue
void checkWiFiConnection()
{
    static uint32_t prev_millis = 0;
    

    if (WiFi.status() != WL_CONNECTED)
    {   
        sensorStatus(ui_statusWifi, SENSOR_NOT_CONNECTED);
        uint32_t current_millis = millis();
        // Check for 1 second interval for blinking and dot printing (combined condition)
        if (current_millis - prev_millis >= 50)
        {
            prev_millis = current_millis;

            // Toggle blink state
            blinkState = !blinkState;

            debug(".");

            // Set LED color based on blinkState
            if (blinkState == 0)
            {
                smartdisplay_led_set_rgb(1, 0, 0);
            }
            else
            {
                smartdisplay_led_set_rgb(0, 0, 1);
            }
        }
    }
    else
    {
        sensorStatus(ui_statusWifi, SENSOR_CONNECTED);
    }
}