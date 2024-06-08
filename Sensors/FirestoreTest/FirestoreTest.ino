#include "Firebase.h"

unsigned long previousMillis = 0; // Stores the last time the loop action was performed
const unsigned long interval = 5000; // Time interval between readings in milliseconds (5 seconds)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi_Init();
  firebaseUserAuth();
  firebaseConfig();
}

void loop() {
  // Check if the desired interval has passed since the last reading
  int pot = random(0, 255);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Update the last read time

    // Path to the Firestore document
    String documentPath = "Test/try";

    // Create a FirebaseJson object for storing data
    FirebaseJson content;

    Serial.printf("Value: ", pot);
    Serial.println();

    // Data validation (not NaN)
    if (!isnan(pot)) {
      content.set("fields/Potentiometer/stringValue", String(pot));

      Serial.println("Added potentiometer value...");

      if (Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw(), "Potentiometer")) {
        Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
      } else {
        Serial.println(fbdo.errorReason());
      }
    } else {
      Serial.println("Failed to read Potentiometer");
    }
  }
}
