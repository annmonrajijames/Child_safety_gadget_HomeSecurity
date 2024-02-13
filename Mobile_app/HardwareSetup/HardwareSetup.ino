#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Annmon";
const char* password = "childsafe";

#include <String.h>

#define RED D0
#define GREEN D6
#define BLUE  D7

const char* ap_ssid = "Annmon_ESP_Hotspot";
const char* ap_password = "childsafe";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  WiFi.softAP(ap_ssid, ap_password); 
  server.begin();
  Serial.println("Access Point started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());  //  

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

}

void loop() {

  String all_command = "";

  WiFiClient client = server.available();

  if (client) {
    String request = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        if (c == '\r') {
          // End of line reached, check if next character is newline

          Serial.println(request);  // full HTTP command line including GET  and HTTP 1

          // Extract command from request string
          int start = request.indexOf("GET /") + 5;
          int end = request.indexOf("HTTP/");
          String command = request.substring(start, end);

          //Purify the command
          command.replace("\n", "");
          command.replace("\r", "");
          command.replace(" ", ""); // removes all space characters
          command.replace("\t", ""); // removes all tab characters
          command.trim();

          Serial.println(command);

          all_command =  command + " is on";  // green is on 


          if (command.equals("red")) {
            digitalWrite(RED, HIGH);
            digitalWrite(GREEN, LOW);
            digitalWrite(BLUE, LOW);

          }

          if (command.equals("green")) {
            digitalWrite(GREEN, HIGH);
            digitalWrite(RED, LOW);
            digitalWrite(BLUE, LOW);


          }


          if (command.equals("blue")) {
            digitalWrite(BLUE, HIGH);
            digitalWrite(RED, LOW);
            digitalWrite(GREEN, LOW);
          }



          if (client.peek() == '\n') {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            String commandWithTags = "<html><body>" + all_command + "</body></html>";
            client.println(commandWithTags);
            break;

          }
        }
      }
    }
  }
}

