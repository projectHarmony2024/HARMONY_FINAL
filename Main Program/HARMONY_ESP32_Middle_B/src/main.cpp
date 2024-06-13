/*======================================================================================================================
▐▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▌
▐                                                                                                                     ▌
▐ ███████╗███████╗██████╗ ██████╗ ██████╗               ██████╗        ███╗   ███╗██╗██████╗ ██████╗ ██╗     ███████╗ ▌
▐ ██╔════╝██╔════╝██╔══██╗╚════██╗╚════██╗              ██╔══██╗██╗    ████╗ ████║██║██╔══██╗██╔══██╗██║     ██╔════╝ ▌
▐ █████╗  ███████╗██████╔╝ █████╔╝ █████╔╝    █████╗    ██████╔╝╚═╝    ██╔████╔██║██║██║  ██║██║  ██║██║     █████╗   ▌
▐ ██╔══╝  ╚════██║██╔═══╝  ╚═══██╗██╔═══╝     ╚════╝    ██╔══██╗██╗    ██║╚██╔╝██║██║██║  ██║██║  ██║██║     ██╔══╝   ▌
▐ ███████╗███████║██║     ██████╔╝███████╗              ██████╔╝╚═╝    ██║ ╚═╝ ██║██║██████╔╝██████╔╝███████╗███████╗ ▌
▐ ╚══════╝╚══════╝╚═╝     ╚═════╝ ╚══════╝              ╚═════╝        ╚═╝     ╚═╝╚═╝╚═════╝ ╚═════╝ ╚══════╝╚══════╝ ▌
▐                                                                                                                     ▌
▐▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▌
=======================================================================================================================*/

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

/* ========== CONFIGURATION ========== */
// ESP-NOW Broadcast Address. Replace with LVGL LCD MAC Address
uint8_t broadcastAddress[] = {0x30, 0xC9, 0x22, 0x32, 0xB6, 0x14};

// // ULTRASONIC ANEMOMETER
// #include <UltrasonicAnemometer.h>
// #define DI 25
// #define DE 26
// #define RE 27
// #define RO 14
// #define MAX485_Vcc 33
// UltrasonicAnemometer Anemometer(RO, DI, DE, RE);

// PZEM-C
// #include <PZEM004Tv30.h>
// #define PZEM_C_RX_PIN 23
// #define PZEM_C_TX_PIN 19
// PZEM004Tv30 PZEM3(Serial1, PZEM_C_RX_PIN, PZEM_C_TX_PIN);

// MOVING AVERAGE FILTER
#include <MovingAverageFilter.h>
enum SensorChannel
{
    WIND_SPEED_MS,
    WIND_SPEED_KPH,
    WIND_DIRECTION,
    PZEM_C_VOLTAGE,
    PZEM_C_CURRENT,
    PZEM_C_POWER,
    PZEM_C_ENERGY,
    PZEM_C_FREQUENCY,
    PZEM_C_POWERFACTOR,
    NUM_OF_CHANNELS
};
#define WINDOW_SIZE 15
MovingAverageFilter Filter(WINDOW_SIZE, NUM_OF_CHANNELS);

// SENSORS DATA FROM ESP32-A
struct SmoothedSensorReadings
{
    float Solar_Voltage;
    float Solar_Current;
    float Wind_Voltage;
    float Wind_Current;
    float Battery_Voltage;
    int Battery_Percentage;
    float PZEM_A_Voltage;
    float PZEM_A_Current;
    float PZEM_A_Power;
    float PZEM_A_Energy;
    float PZEM_A_Frequency;
    float PZEM_A_PowerFactor;
    float PZEM_B_Voltage;
    float PZEM_B_Current;
    float PZEM_B_Power;
    float PZEM_B_Energy;
    float PZEM_B_Frequency;
    float PZEM_B_PowerFactor;
    String RTC_Date;
    String RTC_Time;
    String RTC_Timestamp;
    int RTC_TimeInt;
};
SmoothedSensorReadings SensorData;

// SENSORS DATA TO SEND TO LVGL LCD
struct SmoothedSensorReadingsLCD
{
    float Solar_Voltage;
    float Solar_Current;
    float Wind_Voltage;
    float Wind_Current;
    float WindSpeed_ms;
    float WindSpeed_kph;
    int Wind_Direction;
    float Battery_Voltage;
    int Battery_Percentage;
    float PZEM_A_Voltage;
    float PZEM_A_Current;
    float PZEM_A_Power;
    float PZEM_A_Energy;
    float PZEM_A_Frequency;
    float PZEM_A_PowerFactor;
    float PZEM_B_Voltage;
    float PZEM_B_Current;
    float PZEM_B_Power;
    float PZEM_B_Energy;
    float PZEM_B_Frequency;
    float PZEM_B_PowerFactor;
    float PZEM_C_Voltage;
    float PZEM_C_Current;
    float PZEM_C_Power;
    float PZEM_C_Energy;
    float PZEM_C_Frequency;
    float PZEM_C_PowerFactor;
    String RTC_Date;
    String RTC_Time;
    String RTC_Timestamp;
    int RTC_TimeInt;
};
SmoothedSensorReadingsLCD SensorDataLCD;

esp_now_peer_info_t peerInfo;

// FUNCTIONS
void SensorReadings();
void DisplayResult();
/* ========== END OF CONFIGURATION ========== */

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&SensorData, incomingData, sizeof(SensorData));
    Serial.println();
    Serial.print("Bytes received: ");
    Serial.println(len);
    DisplayResult();
}

void setup()
{
    Serial.begin(115200);

    // Anemometer.begin();
    // Anemometer.setDirectionOffset(195);

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb(OnDataRecv);

    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
}

ulong previousMillis = 0;

void loop()
{
    // Read PZEM_C
    SensorReadings();

    ulong currentMillis = millis();

    if ((currentMillis - previousMillis >= 1000))
    {
        previousMillis = currentMillis;

        SensorDataLCD.Solar_Voltage = SensorData.Solar_Voltage;
        SensorDataLCD.Solar_Current = SensorData.Solar_Current;
        SensorDataLCD.Wind_Voltage = SensorData.Wind_Voltage;
        SensorDataLCD.Wind_Current = SensorData.Wind_Current;
        SensorDataLCD.WindSpeed_ms;
        SensorDataLCD.WindSpeed_kph;
        SensorDataLCD.Wind_Direction;
        SensorDataLCD.Battery_Voltage = SensorData.Battery_Voltage;
        SensorDataLCD.Battery_Percentage = SensorData.Battery_Percentage;
        SensorDataLCD.PZEM_A_Voltage = SensorData.PZEM_A_Voltage;
        SensorDataLCD.PZEM_A_Current = SensorData.PZEM_A_Current;
        SensorDataLCD.PZEM_A_Power = SensorData.PZEM_A_Power;
        SensorDataLCD.PZEM_A_Energy = SensorData.PZEM_A_Energy;
        SensorDataLCD.PZEM_A_Frequency = SensorData.PZEM_A_Frequency;
        SensorDataLCD.PZEM_A_PowerFactor = SensorData.PZEM_A_PowerFactor;
        SensorDataLCD.PZEM_B_Voltage = SensorData.PZEM_B_Voltage;
        SensorDataLCD.PZEM_B_Current = SensorData.PZEM_B_Current;
        SensorDataLCD.PZEM_B_Power = SensorData.PZEM_B_Power;
        SensorDataLCD.PZEM_B_Energy = SensorData.PZEM_B_Power;
        SensorDataLCD.PZEM_B_Frequency = SensorData.PZEM_B_Frequency;
        SensorDataLCD.PZEM_B_PowerFactor = SensorData.PZEM_B_PowerFactor;
        SensorDataLCD.PZEM_C_Voltage;
        SensorDataLCD.PZEM_C_Current;
        SensorDataLCD.PZEM_C_Power;
        SensorDataLCD.PZEM_C_Energy;
        SensorDataLCD.PZEM_C_Frequency;
        SensorDataLCD.PZEM_C_PowerFactor;
        SensorDataLCD.RTC_Date = SensorData.RTC_Date;
        SensorDataLCD.RTC_Time = SensorData.RTC_Time;
        SensorDataLCD.RTC_Timestamp = SensorData.RTC_Timestamp;
        SensorDataLCD.RTC_TimeInt = SensorData.RTC_TimeInt;

        Serial.printf("PZEM-C: %0.2f , %0.2f , %0.2f , %0.2f , %0.2f , %0.2f \n", SensorDataLCD.PZEM_C_Voltage, SensorDataLCD.PZEM_C_Current, SensorDataLCD.PZEM_C_Power, SensorDataLCD.PZEM_C_Energy, SensorDataLCD.PZEM_C_Frequency, SensorDataLCD.PZEM_C_PowerFactor);
        Serial.printf("Wind Speed: %0.2f  Wind Direction: %d\n", SensorDataLCD.WindSpeed_kph, SensorDataLCD.Wind_Direction);

        // Send message via ESP-NOW
        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&SensorDataLCD, sizeof(SensorDataLCD));
    }
}

float randomFloat(float minVal, float maxVal) {
  return minVal + (float)random() / ((float)RAND_MAX / (maxVal - minVal));
}

/* ========== SENSOR READINGS ========== */
void SensorReadings()
{
    // RAW READINGS
#define SAMPLEDATA 0
#if SAMPLEDATA == 1
    static float pzem_voltage = PZEM3.voltage();
    static float pzem_current = PZEM3.current();
    static float pzem_power = PZEM3.power();
    static float pzem_energy = PZEM3.energy();
    static float pzem_frequency = PZEM3.frequency();
    static float pzem_pf = PZEM3.pf();

    // ADD RAW READINGS TO MOVING AVERAGE FILTER
    Filter.addReading(pzem_voltage, PZEM_C_VOLTAGE);
    Filter.addReading(pzem_current, PZEM_C_CURRENT);
    Filter.addReading(pzem_power, PZEM_C_POWER);
    Filter.addReading(pzem_energy, PZEM_C_ENERGY);
    Filter.addReading(pzem_frequency, PZEM_C_ENERGY);
    Filter.addReading(pzem_pf, PZEM_C_POWERFACTOR);

    // GET SMOOTHED READINGS AND UPDATE STRUCT DATA
    SensorData.PZEM_C_Voltage = Filter.getAverage(PZEM_C_VOLTAGE);
    SensorData.PZEM_C_Current = Filter.getAverage(PZEM_C_CURRENT);
    SensorData.PZEM_C_Power = Filter.getAverage(PZEM_C_POWER);
    SensorData.PZEM_C_Energy = Filter.getAverage(PZEM_C_ENERGY);
    SensorData.PZEM_C_Frequency = Filter.getAverage(PZEM_C_FREQUENCY);
    SensorData.PZEM_C_PowerFactor = Filter.getAverage(PZEM_C_POWERFACTOR);
#else
    // SensorDataLCD.WindSpeed_ms = Anemometer.getWindSpeed_ms();
    // SensorDataLCD.WindSpeed_kph = Anemometer.getWindSpeed_kph();
    // SensorDataLCD.Wind_Direction = Anemometer.getWind_Direction();
    // float WindSpeed_ms;
    // float WindSpeed_kph;
    // int Wind_Direction;

    // if (!isnan(Anemometer.readData()))
    // {
    //     // Anemometer Data successfully read
    //     WindSpeed_ms = Anemometer.getWindSpeed_ms();
    //     WindSpeed_kph = Anemometer.getWindSpeed_kph();
    //     Wind_Direction = Anemometer.getWind_Direction();
    // }
    // else
    // {
    //     // Handle error: No anemometer data received
    //     // windSpeed_ms and wind_Direction will be nan
    //     Serial.printf("Anemometer Error: No data received\n");
    // }

    // Filter.addReading(WindSpeed_ms, WIND_SPEED_MS);
    // Filter.addReading(WindSpeed_kph, WIND_SPEED_KPH);
    // Filter.addReading(Wind_Direction, WIND_DIRECTION);

    // SensorDataLCD.WindSpeed_ms = Filter.getAverage(WIND_SPEED_MS);
    // SensorDataLCD.WindSpeed_kph = Filter.getAverage(WIND_SPEED_KPH);
    // SensorDataLCD.Wind_Direction = Filter.getAverage(WIND_DIRECTION);

    SensorDataLCD.WindSpeed_ms = randomFloat(0.0, 10.0);
    SensorDataLCD.WindSpeed_kph = randomFloat(0.0, 2.0);
    SensorDataLCD.Wind_Direction = random(0, 10);
    SensorDataLCD.PZEM_C_Voltage = 0;
    SensorDataLCD.PZEM_C_Current = 0;
    SensorDataLCD.PZEM_C_Power = 0;
    SensorDataLCD.PZEM_C_Energy = 0;
    SensorDataLCD.PZEM_C_Frequency = 0;
    SensorDataLCD.PZEM_C_PowerFactor = 0;

#endif
}
/* ========== END OF SENSOR READINGS ========== */

// For Debugging Only
void DisplayResult()
{
    Serial.println("\n=== TIME ===");
    Serial.printf("Date: %s  Time: %s\n", SensorData.RTC_Date.c_str(), SensorData.RTC_Time.c_str());
    Serial.println("=== SOLAR ===");
    Serial.printf("Voltage: %0.2f  Current: %0.2f\n", SensorData.Solar_Voltage, SensorData.Solar_Current);
    Serial.println("=== WIND ===");
    // Serial.printf("Voltage: %0.2f  Current: %0.2f  Wind Speed: %0.2fkph  Wind Direction: %d\n", SensorData.Wind_Voltage, SensorData.Wind_Current, SensorData.WindSpeed_kph, SensorData.Wind_Direction);
    Serial.printf("Voltage: %0.2f  Current: %0.2f\n", SensorData.Wind_Voltage, SensorData.Wind_Current);
    Serial.println("=== BATTERY ===");
    Serial.printf("Voltage: %0.2f  Percentage: %d%\n", SensorData.Battery_Voltage, SensorData.Battery_Percentage);
    Serial.println("=== ENERGY CONSUMPTION ===");
    Serial.printf("PZEM-A: %0.2f , %0.2f , %0.2f , %0.2f , %0.2f , %0.2f \n", SensorData.PZEM_A_Voltage, SensorData.PZEM_A_Current, SensorData.PZEM_A_Power, SensorData.PZEM_A_Energy, SensorData.PZEM_A_Frequency, SensorData.PZEM_A_PowerFactor);
    Serial.printf("PZEM-B: %0.2f , %0.2f , %0.2f , %0.2f , %0.2f , %0.2f \n", SensorData.PZEM_B_Voltage, SensorData.PZEM_B_Current, SensorData.PZEM_B_Power, SensorData.PZEM_B_Energy, SensorData.PZEM_B_Frequency, SensorData.PZEM_B_PowerFactor);
    Serial.println(SensorData.RTC_TimeInt);
}