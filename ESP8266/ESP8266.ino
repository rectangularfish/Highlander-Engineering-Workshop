#include <ESP8266WiFi.h>     // Include the ESP8266 Wi-Fi library 
                             // for network connectivity.
                             
#include <ESP8266HTTPClient.h> // Include the ESP8266 HTTP client 
                               // library for making HTTP requests.

WiFiClient client;           // Create a Wi-Fi client object for managing the Wi-Fi connection.

// set the pin of the ultrasonic sensor
const int trigPin = 12;
const int echoPin = 14;

// define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
float threshold = 20;

void setup() {
  Serial.begin(115200); // Starts the serial communication

  // Connect to the Wi-Fi network
  WiFi.begin(ssid, password); // ssid = network name and password = network password
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
  Serial.println("Connected to WiFi Network");

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { // Check WiFi connection status

    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance in centimeters
    distanceCm = duration * SOUND_VELOCITY / 2;

    // Prints the distance on the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);

    if (distanceCm < threshold) {
      // If the distance is less than the threshold, send an HTTP GET request

      HTTPClient http;
      http.begin(client, "http://192.168.3.62:8090/helloesp");
      int httpCode = http.GET(); // Send the request
      Serial.println("Sending a request");
      http.end(); // Close the connection

      delay(10000); // Wait for a while before sending another request
    }
  }

  delay(50); // Delay to control the loop frequency
}