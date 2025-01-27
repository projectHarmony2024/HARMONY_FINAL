/* --------- DEBUGGING MODE --------- */
#define DEBUG 1
#define MAIN 1
#define CURRENT_SENSOR 1
#define VOLTAGE_SENSOR 1
#define ULTRASONIC_ANEMOMETER 1
#define PZEM004T 1
#define RTC_DS3231 1
#define MICRO_SD_CARD 1
#define ESPNOW_LVGL 1
/* --------- END OF DEBUGGING MODE --------- */

/* --------- 1. LIBRARIES --------- */
// 1.1 External Libraries
#include <Arduino.h>
#include <Debug.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// 1.2 Internal Libraries
#include <RTC_DS3231.h>
#include <UltrasonicAnemometer.h>
#include <PowerConsumptionSensor.h>
#include <VoltageSensor.h>
#include <CurrentSensor.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>
/* --------- END OF LIBRARIES --------- */

/* --------- 2. FIREBASE AND WIFI SETUP --------- */
// 2.1. Define the WiFi credentials
#define WIFI_SSID "WARNING!!!! VIRUS DETECTED"
#define WIFI_PASSWORD "Maytoyosirexie10000"

// 2.2. Define the API Key
#define API_KEY "AIzaSyDF1f5EeF6cIsldc6FnyspmIgFFOLojwKk"

// 2.3. Define the project ID
#define FIREBASE_PROJECT_ID "harmony-testing-c67ff"

// 2.4. Define the user Email and password that alreadey registerd or added in your project
#define USER_EMAIL "projectharmonyesp@gmail.com"
#define USER_PASSWORD "projectHarmony_ESP32"

// 2.5. Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

// 2.6. The Firestore payload upload callback function
void fcsUploadCallback(CFS_UploadStatusInfo info)
{
  if (info.status == firebase_cfs_upload_status_init)
  {
    debugf("\nUploading data (%d)...\n", info.size);
  }
  else if (info.status == firebase_cfs_upload_status_upload)
  {
    debugf("Uploaded %d%s\n", (int)info.progress, "%");
  }
  else if (info.status == firebase_cfs_upload_status_complete)
  {
    debugln("Upload completed ");
  }
  else if (info.status == firebase_cfs_upload_status_process_response)
  {
    debug("Processing the response... ");
  }
  else if (info.status == firebase_cfs_upload_status_error)
  {
    debugf("Upload failed, %s\n", info.errorMsg.c_str());
  }
}
/* --------- END OF FIREBASE AND WIFI SETUP --------- */

/* --------- 3. VARIABLES --------- */
unsigned long dataMillis = 0;
int count = 0;
/* --------- END OF VARIABLES --------- */

/* --------- SETUP --------- */
void setup()
{
  init_RTC();

  debug_init(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  debugf("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    debug(".");
    delay(300);
  }
  debugln("");
  debug("Connected with IP: ");
  debugln(WiFi.localIP());
  debugln("");

  debugf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
  Firebase.reconnectNetwork(true);

  // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
  // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
  fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

  // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  // For sending payload callback
  // config.cfs.upload_callback = fcsUploadCallback;
}
/* --------- END OF SETUP --------- */

/* --------- LOOP --------- */
void loop()
{

  if (Firebase.ready() && (millis() - dataMillis > 60000 || dataMillis == 0))
  {
    dataMillis = millis();

    FirebaseJson content;
    String documentPath = "HARMONY_SENSORS/";
    documentPath += RTCcurrentDateTime();

    // double
    content.set("fields/sampleSensor1/doubleValue", random(1, 500) / 100.0);

    // boolean
    content.set("fields/isOnline/booleanValue", true);

    // integer
    content.set("fields/sampleSensor2/integerValue", String(random(500, 1000)));

    // null
    content.set("fields/myNull/nullValue");

    String doc_path = "projects/";
    doc_path += FIREBASE_PROJECT_ID;
    doc_path += "/databases/(default)/documents/coll_id/doc_id"; // coll_id and doc_id are your collection id and document id

    // reference
    content.set("fields/myRef/referenceValue", doc_path.c_str());

    // timestamp
    String RTCtime = RTCgetTimestamp();
    content.set("fields/myTimestamp/timestampValue", RTCtime); // RFC3339 UTC "Zulu" format

    // bytes
    content.set("fields/myBytes/bytesValue", "aGVsbG8="); // base64 encoded

    // array
    content.set("fields/myArray/arrayValue/values/[0]/stringValue", "test");
    content.set("fields/myArray/arrayValue/values/[1]/integerValue", "20");
    content.set("fields/myArray/arrayValue/values/[2]/booleanValue", true);

    // map
    content.set("fields/myMap/mapValue/fields/name/stringValue", "wrench");
    content.set("fields/myMap/mapValue/fields/mass/stringValue", "1.3kg");
    content.set("fields/myMap/mapValue/fields/count/integerValue", "3");

    // lat long
    content.set("fields/myLatLng/geoPointValue/latitude", 1.486284);
    content.set("fields/myLatLng/geoPointValue/longitude", 23.678198);

    count++;

    debugln("Create a document... ");

    if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, documentPath.c_str(), content.raw()))
    {
      debugf("ok\n%s\n\n", fbdo.payload().c_str());
    }
    else
    {
      debugln(fbdo.errorReason());
    }
  }
}
/* --------- END OF LOOP --------- */
