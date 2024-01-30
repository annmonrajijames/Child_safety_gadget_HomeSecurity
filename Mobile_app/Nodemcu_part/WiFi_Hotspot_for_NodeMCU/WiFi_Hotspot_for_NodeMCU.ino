#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "JioFiber-KmsXk";
const char* password = "12345678";

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
  Serial.print("IP Address for Wi-Fi: "); // Print the IP address for the Wi-Fi network
  Serial.println(WiFi.localIP());
  // Start the access point
  WiFi.softAP(ap_ssid, ap_password);
  Serial.println("ESP8266 is now acting as an access point");
  Serial.print("IP Address for AP: "); // Print the IP address for the access point
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Your code here, for example, handling client connections
}
