#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// --- Configuration Setup ---
// Replace with your local network credentials
const char* ssid = "SCOE";
const char* password = "System@1";

// Replace with your MQTT Broker details (e.g., broker.emqx.io or local IP)
const char* mqtt_server = "broker.hivemq.com"; 
const int mqtt_port = 1883;

// Authentication details (Leave blank if your broker does not require them)
const char* mqtt_user = "";
const char* mqtt_pass = "";

// MQTT Publication Topics
const char* topic_sensor_data = "esp8266/sensor/reading";

// --- Object Declarations ---
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsgTime = 0;
const long interval = 5000; // Publish interval (5000ms = 5 seconds)

// --- Helper: Connect to Wi-Fi ---
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to network: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wi-Fi network connected!");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());
}

// --- Helper: Reconnect to MQTT Broker ---
void reconnect_mqtt() {
  // Loop until the client establishes a connection
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection... ");
    
    // Create a distinct Client ID for the broker using ESP's Mac address
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    // Attempt connection
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println("Connected to broker successfully!");
    } else {
      Serial.print("Connection failed, rc=");
      Serial.print(client.state());
      Serial.println(". Retrying connection in 5 seconds...");
      delay(5000);
    }
  }
}

// --- Core Initialization ---
void setup() {
  Serial.begin(115200);
  setup_wifi();
  
  // Define MQTT target configuration
  client.setServer(mqtt_server, mqtt_port);
  
  // (Optional) Initialize your hardware sensor logic here (e.g., dht.begin();)
}

// --- Continuous Runtime Loop ---
void loop() {
  // Keep MQTT connection alive and handle incoming packets
  if (!client.connected()) {
    reconnect_mqtt();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsgTime > interval) {
    lastMsgTime = now;

    // --- Read Sensor Values ---
    // Substitute this section with your hardware functions (e.g., dht.readTemperature())
    float sensorValue = random(200, 350) / 10.0; // Produces dummy reading between 20.0 and 35.0

    // Check for faulty sensor states
    if (isnan(sensorValue)) {
      Serial.println("Error: Failed to obtain data from sensor hardware!");
      return;
    }

    // Convert raw numerical data to a string container
    char msgBuffer[10];
    dtostrf(sensorValue, 4, 2, msgBuffer); 

    // Publish data payload to the dedicated topic
    Serial.print("Publishing data stream: ");
    Serial.println(msgBuffer);
    client.publish(topic_sensor_data, msgBuffer);
  }
}