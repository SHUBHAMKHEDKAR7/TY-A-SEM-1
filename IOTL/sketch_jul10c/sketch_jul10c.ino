#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your actual Wi-Fi credentials
const char* ssid     = "SCOE";
const char* password = "System@1";

ESP8266WebServer server(80); // Start server on port 80

const int ledPin = 2; // Pin D1. Change to 2 if using the built-in ESP8266 LED

void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<style>body { text-align: center; font-family: Arial, sans-serif; margin-top: 50px; }";
  html += "a { display: inline-block; width: 150px; padding: 20px; font-size: 24px; text-decoration: none; border-radius: 5px; color: white; margin: 10px; }";
  html += ".btn-on { background-color: #4CAF50; }";
  html += ".btn-off { background-color: #f44336; }</style>";
  html += "</head><body>";
  html += "<h1>ESP8266 Built-in LED Control</h1>";
  html += "<a class=\"btn-on\" href=\"/on\">Turn OFF</a>";
  html += "<a class=\"btn-off\" href=\"/off\">Turn ON</a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(ledPin, HIGH); // Turn LED ON
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  digitalWrite(ledPin, LOW); // Turn LED OFF
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Default to OFF

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());

  // Define server routes
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
