#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// WiFi
const char* ssid = "SCOE";
const char* password = "System@1";

// XAMPP Server
const char* serverName = "http://10.136.168.74/IoT_Project/receive.php";

// HiveMQ
const char* mqtt_server = "YOUR_HIVEMQ_HOST";
const int mqtt_port = 8883;
const char* mqtt_user = "A03";
const char* mqtt_pass = "SCOE";

WiFiClientSecure secureClient;
PubSubClient client(secureClient);

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Connecting MQTT...");

    if(client.connect("ESP8266Client",mqtt_user,mqtt_pass))
    {
      Serial.println("Connected");
    }
    else
    {
      Serial.print("Failed : ");
      Serial.println(client.state());
      delay(3000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");

  secureClient.setInsecure();

  client.setServer(mqtt_server,mqtt_port);

  randomSeed(analogRead(A0));
}

void loop()
{
  if(!client.connected())
      reconnect();

  client.loop();

  float temperature=random(250,350)/10.0;
  float humidity=random(500,800)/10.0;

  String json="{\"temperature\":";
  json+=temperature;
  json+=",\"humidity\":";
  json+=humidity;
  json+="}";

  client.publish("iot/sensor",json.c_str());

  Serial.println("MQTT Published:");
  Serial.println(json);

  if(WiFi.status()==WL_CONNECTED)
  {
      WiFiClient clientHTTP;
      HTTPClient http;

      String url=String(serverName)
      +"?temperature="+String(temperature)
      +"&humidity="+String(humidity);

      http.begin(clientHTTP,url);

      int code=http.GET();

      Serial.print("HTTP Code: ");
      Serial.println(code);

      http.end();
  }

  delay(5000);
}