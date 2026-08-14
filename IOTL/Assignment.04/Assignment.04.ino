#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

// =====================================================
// Wi-Fi Configuration
// =====================================================

const char* ssid = "Abhi";
const char* password = "Abhijeet@41";

// =====================================================
// ThingSpeak Configuration
// =====================================================

unsigned long myChannelNumber = 3445933;
const char* myWriteAPIKey = "67QX1LS7KRMKFE00";

WiFiClient client;

// =====================================================
// Canteen Configuration
// =====================================================

const int totalSeats = 50;

// Starting occupied seats
int occupiedSeats = 10;

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("====================================");
  Serial.println("   CANTEEN SEAT AVAILABILITY SYSTEM");
  Serial.println("====================================");

  // Wi-Fi Station mode
  WiFi.mode(WIFI_STA);

  // Start ThingSpeak
  ThingSpeak.begin(client);

  // Connect to Wi-Fi
  connectWiFi();
}

// =====================================================
// WIFI CONNECTION
// =====================================================

void connectWiFi() {

  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop() {

  // Check Wi-Fi connection
  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("Wi-Fi disconnected!");

    connectWiFi();
  }

  // ===================================================
  // SIMULATE CANTEEN SEAT DATA
  // ===================================================

  // Generate a random number of occupied seats
  occupiedSeats = random(0, totalSeats + 1);

  // Calculate available seats
  int availableSeats = totalSeats - occupiedSeats;

  // Calculate occupancy percentage
  float occupancyPercentage =
      (occupiedSeats * 100.0) / totalSeats;

  // Calculate availability percentage
  float availabilityPercentage =
      (availableSeats * 100.0) / totalSeats;


  // ===================================================
  // DETERMINE CANTEEN STATUS
  // ===================================================

  String canteenStatus;

  if (availabilityPercentage == 0) {

    canteenStatus = "FULL";

  }
  else if (occupancyPercentage >= 80) {

    canteenStatus = "CROWDED";

  }
  else if (occupancyPercentage >= 50) {

    canteenStatus = "MODERATE";

  }
  else {

    canteenStatus = "AVAILABLE";
  }


  // ===================================================
  // DISPLAY DATA ON SERIAL MONITOR
  // ===================================================

  Serial.println();
  Serial.println("------------------------------------");

  Serial.print("Total Seats          : ");
  Serial.println(totalSeats);

  Serial.print("Occupied Seats       : ");
  Serial.println(occupiedSeats);

  Serial.print("Available Seats      : ");
  Serial.println(availableSeats);

  Serial.print("Occupancy Percentage : ");
  Serial.print(occupancyPercentage);
  Serial.println("%");

  Serial.print("Availability         : ");
  Serial.print(availabilityPercentage);
  Serial.println("%");

  Serial.print("Canteen Status       : ");
  Serial.println(canteenStatus);

  Serial.println("------------------------------------");


  // ===================================================
  // SEND DATA TO THINGSPEAK
  // ===================================================

  ThingSpeak.setField(1, availableSeats);

  ThingSpeak.setField(2, occupiedSeats);

  ThingSpeak.setField(3, occupancyPercentage);

  ThingSpeak.setField(4, availabilityPercentage);


  // Send all fields
  int httpCode = ThingSpeak.writeFields(
      myChannelNumber,
      myWriteAPIKey
  );


  // ===================================================
  // CHECK THINGSPEAK RESPONSE
  // ===================================================

  if (httpCode == 200) {

    Serial.println("ThingSpeak update successful!");

  }
  else {

    Serial.print("ThingSpeak update failed.");
    Serial.print(" HTTP error code: ");
    Serial.println(httpCode);
  }


  // ===================================================
  // WAIT
  // ===================================================

  Serial.println("Waiting 20 seconds...");

  delay(20000);
}