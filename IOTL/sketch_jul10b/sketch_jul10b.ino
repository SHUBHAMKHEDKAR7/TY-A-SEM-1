#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "SCOE";
const char* password = "System@1";

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.println();

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  // Wait for the connection to establish
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address once connected
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Put your main code here, to run repeatedly:
}
