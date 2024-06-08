#include <Firebase_ESP_Client.h>
#include <WiFi.h>


#define WIFI_NAME "WARNING!!!! VIRUS DETECTED"
#define WIFI_PASSWORD "Maytoyosirexie10000"

#define API_KEY "AIzaSyDF1f5EeF6cIsldc6FnyspmIgFFOLojwKk"

#define DATABASE_URL "https://harmony-testing-c67ff-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define USER_EMAIL "projectharmonyesp@gmail.com"
#define USER_PASSWORD "projectHarmony_ESP32"

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

const int ledpin = 33;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);

  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.printf("Connected with IP: ", WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  config.database_url = DATABASE_URL;

  Firebase.reconnectNetwork(true);

  fbdo.setBSSLBufferSize(4096, 1024);

  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    int ledState;
    if (Firebase.RTDB.getInt(&fbdo, "led/state", &ledState)) {
      digitalWrite(ledpin, ledState);
    } else {
      Serial.println(fbdo.errorReason().c_str());
    }
  }
}
