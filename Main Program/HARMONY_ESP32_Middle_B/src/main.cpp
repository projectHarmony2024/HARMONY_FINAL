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

/* ========== CONFIGURATION ========== */
// ESP-A
#define ESP_A_init() Serial2.begin(115200, SERIAL_8N1, 14, 12)
#define SendTo_ESP_A(...) Serial2.printf(__VA_ARGS__)

// ESP-C
#define ESP_C_init() Serial1.begin(115200, SERIAL_8N1, 26, 25)
#define SendTo_ESP_C(...) Serial1.printf(__VA_ARGS__)

#include <PZEM004Tv30.h>
#define PZEM_C_RX_PIN 32
#define PZEM_C_TX_PIN 35
PZEM004Tv30 PZEM3(&Serial, PZEM_C_RX_PIN, PZEM_C_TX_PIN);

// MOVING AVERAGE FILTER
#include <MovingAverageFilter.h>
enum SensorChannel
{
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

// SENSORS DATA
struct SmoothedSensorReadings
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
};
SmoothedSensorReadings SensorData;

// FUNCTIONS
void SensorReadings();
void Read_ESP_A();
void DisplayResult();
/* ========== END OF CONFIGURATION ========== */

void setup()
{
    // Serial UART Configurations
    // Serial2.begin(9600, SERIAL_8N1, 14, 12); // ESP-A
    // Serial1.begin(9600, SERIAL_8N1, 26, 25); // ESP-C
    // Serial.begin(115200);                    // PZEM-C

    ESP_A_init();
    ESP_C_init();
}

uint32_t prev_time = 0;

void loop()
{
    // Read PZEM_C
    SensorReadings();

    // Read ESP_A SensorReadings
    Read_ESP_A();

    uint32_t current_time = millis();
    if (current_time - prev_time >= 1000)
    {
        prev_time = current_time;

        // Send to ESP-A:Main
        SendTo_ESP_A("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f\n",
                     SensorData.PZEM_C_Voltage,
                     SensorData.PZEM_C_Current,
                     SensorData.PZEM_C_Power,
                     SensorData.PZEM_C_Energy,
                     SensorData.PZEM_C_Frequency,
                     SensorData.PZEM_C_PowerFactor);

        SendTo_ESP_C("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d,%0.2f,%d,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%s,%s\n",
                     SensorData.Solar_Voltage,
                     SensorData.Solar_Current,
                     SensorData.Wind_Voltage,
                     SensorData.Wind_Current,
                     SensorData.WindSpeed_ms,
                     SensorData.WindSpeed_kph,
                     SensorData.Wind_Direction,
                     SensorData.Battery_Voltage,
                     SensorData.Battery_Percentage,
                     SensorData.PZEM_A_Voltage,
                     SensorData.PZEM_A_Current,
                     SensorData.PZEM_A_Power,
                     SensorData.PZEM_A_Energy,
                     SensorData.PZEM_A_Frequency,
                     SensorData.PZEM_A_PowerFactor,
                     SensorData.PZEM_B_Voltage,
                     SensorData.PZEM_B_Current,
                     SensorData.PZEM_B_Power,
                     SensorData.PZEM_B_Energy,
                     SensorData.PZEM_B_Frequency,
                     SensorData.PZEM_B_PowerFactor,
                     SensorData.PZEM_C_Voltage,
                     SensorData.PZEM_C_Current,
                     SensorData.PZEM_C_Power,
                     SensorData.PZEM_C_Energy,
                     SensorData.PZEM_C_Frequency,
                     SensorData.PZEM_C_PowerFactor,
                     SensorData.RTC_Date,
                     SensorData.RTC_Time);
    }
}

/* ========== SENSOR READINGS ========== */
void SensorReadings()
{
    // RAW READINGS
#define SAMPLEDATA 1
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
    SensorData.Solar_Voltage = random(0, 60);
    SensorData.Solar_Current = random(0, 60);
    SensorData.Wind_Voltage = random(0, 60);
    SensorData.Wind_Current = random(0, 60);
    SensorData.WindSpeed_ms = random(0, 60);
    SensorData.WindSpeed_kph = random(0, 60);
    SensorData.Wind_Direction = random(0, 60);
    SensorData.Battery_Voltage = random(0, 60);
    SensorData.Battery_Percentage = random(0, 60);
    SensorData.PZEM_A_Voltage = random(0, 60);
    SensorData.PZEM_A_Current = random(0, 60);
    SensorData.PZEM_A_Power = random(0, 60);
    SensorData.PZEM_A_Energy = random(0, 60);
    SensorData.PZEM_A_Frequency = random(0, 60);
    SensorData.PZEM_A_PowerFactor = random(0, 60);
    SensorData.PZEM_B_Voltage = random(0, 60);
    SensorData.PZEM_B_Current = random(0, 60);
    SensorData.PZEM_B_Power = random(0, 60);
    SensorData.PZEM_B_Energy = random(0, 60);
    SensorData.PZEM_B_Frequency = random(0, 60);
    SensorData.PZEM_B_PowerFactor = random(0, 60);
#endif
}
/* ========== END OF SENSOR READINGS ========== */

void SendToESP_A(const char *format, ...)
{
    char buffer[256]; // Buffer to hold the formatted string
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    Serial2.printf(buffer);

    /* This is similar to this function but more clarity
            Serial2.printf("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f\n",
                       SensorData.PZEM_C_Voltage,
                       SensorData.PZEM_C_Current,
                       SensorData.PZEM_C_Power,
                       SensorData.PZEM_C_Energy,
                       SensorData.PZEM_C_Frequency,
                       SensorData.PZEM_C_PowerFactor);
    */
}

void Read_ESP_A()
{
    if (Serial2.available())
    {
        String receivedData = Serial2.readStringUntil('\n');

        int startIdx = 0;
        int endIdx = receivedData.indexOf(',');
        SensorData.Solar_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.Solar_Current = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.Wind_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.Wind_Current = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.WindSpeed_ms = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.WindSpeed_kph = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.Wind_Direction = receivedData.substring(startIdx, endIdx).toInt();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.Battery_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.Battery_Percentage = receivedData.substring(startIdx, endIdx).toInt();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.PZEM_A_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.PZEM_A_Current = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.PZEM_A_Power = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.PZEM_A_Energy = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.PZEM_A_Frequency = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.PZEM_A_PowerFactor = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.PZEM_B_Voltage = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.PZEM_B_Current = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.PZEM_B_Power = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.PZEM_B_Energy = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.PZEM_B_Frequency = receivedData.substring(startIdx, endIdx).toFloat();

        startIdx = endIdx + 1;
        endIdx = receivedData.indexOf(',', startIdx);
        SensorData.PZEM_B_PowerFactor = receivedData.substring(startIdx, endIdx).toFloat();
    }
}

void DisplayResult()
{
    Serial.printf("%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%d,%0.2f,%d,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f,%0.2f\n",
                  SensorData.Solar_Voltage,
                  SensorData.Solar_Current,
                  SensorData.Wind_Voltage,
                  SensorData.Wind_Current,
                  SensorData.WindSpeed_ms,
                  SensorData.WindSpeed_kph,
                  SensorData.Wind_Direction,
                  SensorData.Battery_Voltage,
                  SensorData.Battery_Percentage,
                  SensorData.PZEM_A_Voltage,
                  SensorData.PZEM_A_Current,
                  SensorData.PZEM_A_Power,
                  SensorData.PZEM_A_Energy,
                  SensorData.PZEM_A_Frequency,
                  SensorData.PZEM_A_PowerFactor,
                  SensorData.PZEM_B_Voltage,
                  SensorData.PZEM_B_Current,
                  SensorData.PZEM_B_Power,
                  SensorData.PZEM_B_Energy,
                  SensorData.PZEM_B_Frequency,
                  SensorData.PZEM_B_PowerFactor,
                  SensorData.PZEM_C_Voltage,
                  SensorData.PZEM_C_Current,
                  SensorData.PZEM_C_Power,
                  SensorData.PZEM_C_Energy,
                  SensorData.PZEM_C_Frequency,
                  SensorData.PZEM_C_PowerFactor);
}