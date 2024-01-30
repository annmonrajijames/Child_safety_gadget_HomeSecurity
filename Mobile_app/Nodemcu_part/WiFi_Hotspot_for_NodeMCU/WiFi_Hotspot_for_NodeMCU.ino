#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "Annmon";
const char* password = "childsafe";

// Settings for the AP mode (ESP8266 Access Point)
const char* ap_ssid = "ESP8266-AP";
const char* ap_password = "12345678"; // Password should be at least 8 characters long

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start the access point
  WiFi.softAP(ap_ssid, ap_password);
  Serial.println("ESP8266 is now acting as an access point");
}

void loop() {
  // Your code here, for example, handling client connections
}
