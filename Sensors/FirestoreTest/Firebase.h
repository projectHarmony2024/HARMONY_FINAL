#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_NAME "WARNING!!!! VIRUS DETECTED"
#define WIFI_PASSWORD "Maytoyosirexie10000"

#define API_KEY "AIzaSyDF1f5EeF6cIsldc6FnyspmIgFFOLojwKk"
#define DATABASE_URL "https://harmony-testing-c67ff-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_PROJECT_ID "harmony-testing-c67ff"

#define USER_EMAIL "projectharmonyesp@gmail.com"
#define USER_PASSWORD "projectHarmony_ESP32"

//for firebase
unsigned long sendDataPrevMillis = 0;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void WiFi_Init() {
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.printf("Connected with IP: ", WiFi.localIP());
  Serial.println();
}

void firebaseUserAuth() {
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
}

void firebaseConfig() {
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void sendToDbFloat(String dbPath, float data) {
  if (Firebase.RTDB.setFloat(&fbdo, dbPath, data)) {
    Serial.print(data);
    Serial.print(" - successfully saved to: " + fbdo.dataPath());
    Serial.print(" (" + fbdo.dataType() + ")");
  } else {
    Serial.print("FAILED: " + fbdo.errorReason());
  }
  Serial.println();
}
