#include <Arduino.h>

#include <WiFi.h>

#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#define WIFI_SSID "hehez"
#define WIFI_PASSWORD "qwertyuiop"

#define API_KEY "AIzaSyDF1f5EeF6cIsldc6FnyspmIgFFOLojwKk"

#define DATABASE_URL "https://harmony-testing-c67ff-default-rtdb.asia-southeast1.firebasedatabase.app/"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

// ==========================================================
#include <UltrasonicAnemometer.h>
#define RO_PIN 27
#define DI_PIN 13
#define DE_PIN 12
#define RE_PIN 14
#define MAX485_PIN 26

UltrasonicAnemometer Anemometer(RO_PIN, DI_PIN, DE_PIN, RE_PIN, MAX485_PIN);

void setup()
{
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;

    /* Sign up */
    if (Firebase.signUp(&config, &auth, "", ""))
    {
        Serial.println("ok");
        signupOK = true;
    }
    else
    {
        Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Anemometer.begin();
    Anemometer.setOffsetDirection(195);
}

void loop()
{
    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
    {
        sendDataPrevMillis = millis();

        // For Ultrasonic Anemometer
        // Wind Speed
        if (Firebase.RTDB.setFloat(&fbdo, "UltrasonicAnemometer/Wind_Speed_ms", Anemometer.getWindSpeed_ms()))
        {
            Serial.println("SUCCESS!");
            Serial.printf("PATH: %s\n", fbdo.dataPath());
            Serial.printf("TYPE: %s\n", fbdo.dataType());
        }
        else
        {
            Serial.println("FAILED");
            Serial.printf("REASON: %s\n", fbdo.errorReason());
        }

        if (Firebase.RTDB.setFloat(&fbdo, "UltrasonicAnemometer/Wind_Speed_kph", Anemometer.getWindSpeed_kph()))
        {
            Serial.println("SUCCESS!");
            Serial.printf("PATH: %s\n", fbdo.dataPath());
            Serial.printf("TYPE: %s\n", fbdo.dataType());
        }
        else
        {
            Serial.println("FAILED");
            Serial.printf("REASON: %s\n", fbdo.errorReason());
        }

        // Wind Direction
        if (Firebase.RTDB.setInt(&fbdo, "UltrasonicAnemometer/Wind_Direction", Anemometer.getWindDirectionDegrees()))
        {
            Serial.println("PASSED");
            Serial.printf("PATH: %s\n", fbdo.dataPath());
            Serial.printf("TYPE: %s\n", fbdo.dataType());
        }
        else
        {
            Serial.println("FAILED");
            Serial.printf("REASON: %s\n", fbdo.errorReason());
        }
    }
}