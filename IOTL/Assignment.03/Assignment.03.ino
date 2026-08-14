#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi Credentials
const char* ssid = "SCOE";
const char* password = "System@1";

// MQTT Broker
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// Built-in LED
#define LED_PIN LED_BUILTIN

void setup_wifi() {
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {

  String message = "";

  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Message Received: ");
  Serial.println(message);

  if (message == "ON") {
    digitalWrite(LED_PIN, LOW);   // Built-in LED is Active LOW
    Serial.println("LED ON");
  }
  else if (message == "OFF") {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED OFF");
  }
}

void reconnect() {

  while (!client.connected()) {

    Serial.print("Connecting to MQTT...");

    // Create a unique client ID
    String clientId = "ESP8266-";
    clientId += String(ESP.getChipId(), HEX);

    if (client.connect(clientId.c_str())) {

      Serial.println(" Connected!");
      client.subscribe("home/led");
      Serial.println("Subscribed to topic: home/led");

    } else {

      Serial.print(" Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);

    }
  }
}

void setup() {

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);   // LED OFF initially

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}