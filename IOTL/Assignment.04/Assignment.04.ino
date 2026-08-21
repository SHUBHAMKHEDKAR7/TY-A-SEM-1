#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

// =====================================================
// Wi-Fi Configuration
// =====================================================

const char* ssid = "SCOE";
const char* password = "System@1";

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

// Current occupied seats
int occupiedSeats = 10;

// =====================================================
// Variables for simulation
// =====================================================

int availableSeats;

float occupancyPercentage;
float availabilityPercentage;

int studentsEntering;
int studentsLeaving;

int waitingStudents;

int crowdLevel;


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("==========================================");
  Serial.println("     CANTEEN SEAT AVAILABILITY SYSTEM");
  Serial.println("==========================================");

  // ESP8266 Station Mode
  WiFi.mode(WIFI_STA);

  // Start ThingSpeak
  ThingSpeak.begin(client);

  // Random seed
  randomSeed(analogRead(A0));

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

  // ===================================================
  // Check Wi-Fi
  // ===================================================

  if (WiFi.status() != WL_CONNECTED) {

    Serial.println("Wi-Fi disconnected!");

    connectWiFi();
  }


  // ===================================================
  // SIMULATE STUDENTS ENTERING
  // ===================================================

  studentsEntering = random(0, 6);


  // ===================================================
  // SIMULATE STUDENTS LEAVING
  // ===================================================

  studentsLeaving = random(0, 5);


  // ===================================================
  // UPDATE OCCUPIED SEATS
  // ===================================================

  occupiedSeats =
      occupiedSeats
      + studentsEntering
      - studentsLeaving;


  // Prevent occupied seats from going below 0
  if (occupiedSeats < 0) {

    occupiedSeats = 0;
  }


  // Prevent occupied seats from exceeding total seats
  if (occupiedSeats > totalSeats) {

    occupiedSeats = totalSeats;
  }


  // ===================================================
  // AVAILABLE SEATS
  // ===================================================

  availableSeats =
      totalSeats - occupiedSeats;


  // ===================================================
  // OCCUPANCY PERCENTAGE
  // ===================================================

  occupancyPercentage =
      (occupiedSeats * 100.0) / totalSeats;


  // ===================================================
  // AVAILABILITY PERCENTAGE
  // ===================================================

  availabilityPercentage =
      (availableSeats * 100.0) / totalSeats;


  // ===================================================
  // SIMULATE WAITING STUDENTS
  // ===================================================

  if (availableSeats == 0) {

    waitingStudents = random(1, 11);

  }
  else if (availableSeats <= 5) {

    waitingStudents = random(0, 6);

  }
  else {

    waitingStudents = 0;
  }


  // ===================================================
  // DETERMINE CROWD LEVEL
  // ===================================================

  if (occupancyPercentage >= 90) {

    crowdLevel = 4;
  }

  else if (occupancyPercentage >= 75) {

    crowdLevel = 3;
  }

  else if (occupancyPercentage >= 50) {

    crowdLevel = 2;
  }

  else if (occupancyPercentage >= 25) {

    crowdLevel = 1;
  }

  else {

    crowdLevel = 0;
  }


  // ===================================================
  // DISPLAY DATA
  // ===================================================

  Serial.println();
  Serial.println("==========================================");

  Serial.print("Total Seats          : ");
  Serial.println(totalSeats);

  Serial.print("Available Seats      : ");
  Serial.println(availableSeats);

  Serial.print("Occupied Seats       : ");
  Serial.println(occupiedSeats);

  Serial.print("Occupancy Percentage : ");
  Serial.print(occupancyPercentage);
  Serial.println("%");

  Serial.print("Availability         : ");
  Serial.print(availabilityPercentage);
  Serial.println("%");

  Serial.print("Students Entering    : ");
  Serial.println(studentsEntering);

  Serial.print("Students Leaving     : ");
  Serial.println(studentsLeaving);

  Serial.print("Waiting Students     : ");
  Serial.println(waitingStudents);

  Serial.print("Crowd Level          : ");
  Serial.println(crowdLevel);

  Serial.println("==========================================");


  // ===================================================
  // SEND DATA TO THINGSPEAK
  // ===================================================

  // Graph 1
  // Available Seats
  // Occupied Seats

  ThingSpeak.setField(1, availableSeats);
  ThingSpeak.setField(2, occupiedSeats);


  // Graph 2
  // Occupancy Percentage
  // Availability Percentage

  ThingSpeak.setField(3, occupancyPercentage);
  ThingSpeak.setField(4, availabilityPercentage);


  // Graph 3
  // Students Entering
  // Students Leaving

  ThingSpeak.setField(5, studentsEntering);
  ThingSpeak.setField(6, studentsLeaving);


  // Graph 4
  // Waiting Students
  // Crowd Level

  ThingSpeak.setField(7, waitingStudents);
  ThingSpeak.setField(8, crowdLevel);


  // ===================================================
  // SEND ALL 8 FIELDS
  // ===================================================

  int httpCode =
      ThingSpeak.writeFields(
          myChannelNumber,
          myWriteAPIKey
      );


  // ===================================================
  // CHECK RESULT
  // ===================================================

  if (httpCode == 200) {

    Serial.println();
    Serial.println("ThingSpeak update successful!");

  }

  else {

    Serial.print("ThingSpeak update failed.");
    Serial.print(" HTTP error code: ");
    Serial.println(httpCode);
  }


  Serial.println();
  Serial.println("Next update after 20 seconds...");
  Serial.println();


  // ===================================================
  // WAIT 20 SECONDS
  // ===================================================

  delay(20000);
}