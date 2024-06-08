#define WIFI_NAME "WARNING!!!! VIRUS DETECTED"
#define WIFI_PASSWORD "Maytoyosirexie10000"

#define API_KEY "AIzaSyDF1f5EeF6cIsldc6FnyspmIgFFOLojwKk"
#define DATABASE_URL "https://harmony-testing-c67ff-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define USER_EMAIL "projectharmonyesp@gmail.com"
#define USER_PASSWORD "projectHarmony_ESP32"

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

void userAuth() {
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
}

void dbConfig() {
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void sendToDbFloat(String dbPath, float data) {
  if (Firebase.RTDB.setFloat(&fbdo, dbPath, data)) {
    Serial.println();
    Serial.print(data);
    Serial.print(" - successfully saved to: " + fbdo.dataPath());
    Serial.println(" (" + fbdo.dataType() + ")");
  } else {
    Serial.println("FAILED: " + fbdo.errorReason());
  }
}