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
// #define DI 32
// #define DE 33
// #define RE 25
// #define RO 26
// // #define MAX485_Vcc 33
// // UltrasonicAnemometer Anemometer(RO, DI, DE, RE, MAX485_Vcc);
// UltrasonicAnemometer Anemometer(RO, DI, DE, RE);

// PZEM-C
#include <PZEM004Tv30.h>
#define PZEM_C_RX_PIN 23
#define PZEM_C_TX_PIN 19
PZEM004Tv30 PZEM3(Serial1, PZEM_C_RX_PIN, PZEM_C_TX_PIN);

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
    // float WindSpeed_ms;
    // float WindSpeed_kph;
    // int Wind_Direction;
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
    // float PZEM_C_Voltage;
    // float PZEM_C_Current;
    // float PZEM_C_Power;
    // float PZEM_C_Energy;
    // float PZEM_C_Frequency;
    // float PZEM_C_PowerFactor;
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

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    // Serial.print("\r\nLast Packet Send Status:\t");
    // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// FUNCTIONS
void SensorReadings();
void DisplayResult();
/* ========== END OF CONFIGURATION ========== */

// callback function that will be executed when data is received
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

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info
    esp_now_register_recv_cb(OnDataRecv);

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    esp_now_register_send_cb(OnDataSent);

    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peer
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

        // if (result == ESP_OK)
        // {
        //     Serial.println("Sent with success");
        // }
        // else
        // {
        //     Serial.println("Error sending the data");
        // }
    }
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
    SensorDataLCD.WindSpeed_ms = random(0,60);
    SensorDataLCD.WindSpeed_kph = random(0,60);
    SensorDataLCD.Wind_Direction = random(0,60);
    SensorDataLCD.PZEM_C_Voltage = random(0, 60);
    SensorDataLCD.PZEM_C_Current = random(0, 60);
    SensorDataLCD.PZEM_C_Power = random(0, 60);
    SensorDataLCD.PZEM_C_Energy = random(0, 60);
    SensorDataLCD.PZEM_C_Frequency = random(0, 60);
    SensorDataLCD.PZEM_C_PowerFactor = random(0, 60);

#endif
}
/* ========== END OF SENSOR READINGS ========== */

// void Read_ESP_A()
// {
//     if (Serial2.available())
//     {
//         String receivedData = Serial2.readStringUntil('\n');

//         int startIdx = 0;
//         int endIdx = receivedData.indexOf(',');
//         SensorData.Solar_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.Solar_Current = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.Wind_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.Wind_Current = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.WindSpeed_ms = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.WindSpeed_kph = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.Wind_Direction = receivedData.substring(startIdx, endIdx).toInt();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.Battery_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.Battery_Percentage = receivedData.substring(startIdx, endIdx).toInt();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_A_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_A_Current = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_A_Power = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_A_Energy = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_A_Frequency = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_A_PowerFactor = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_B_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_B_Current = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_B_Power = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_B_Energy = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_B_Frequency = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_B_PowerFactor = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_C_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_C_Current = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_C_Power = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_C_Energy = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_C_Frequency = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.PZEM_C_PowerFactor = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.RTC_Date = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.RTC_Time = receivedData.substring(startIdx, endIdx).toFloat();

//         startIdx = endIdx + 1;
//         endIdx = receivedData.indexOf(',', startIdx);
//         SensorData.RTC_Timestamp = receivedData.substring(startIdx, endIdx).toFloat();
//     }
// }

// For Debugging Only
void DisplayResult()
{
    // Serial.printf("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f\n",
    //               SensorData.Solar_Voltage,
    //               SensorData.Solar_Current,
    //               SensorData.Wind_Voltage,
    //               SensorData.Wind_Current,
    //               SensorData.Battery_Voltage,
    //               SensorData.Battery_Percentage,
    //               SensorData.PZEM_A_Voltage,
    //               SensorData.PZEM_A_Current,
    //               SensorData.PZEM_A_Power,
    //               SensorData.PZEM_A_Energy,
    //               SensorData.PZEM_A_Frequency,
    //               SensorData.PZEM_A_PowerFactor,
    //               SensorData.PZEM_B_Voltage,
    //               SensorData.PZEM_B_Current,
    //               SensorData.PZEM_B_Power,
    //               SensorData.PZEM_B_Energy,
    //               SensorData.PZEM_B_Frequency,
    //               SensorData.PZEM_B_PowerFactor);
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