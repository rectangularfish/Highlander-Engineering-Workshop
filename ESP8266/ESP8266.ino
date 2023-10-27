#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


WiFiClient client;


// set the pin of the ultrasonic sensor
const int trigPin = 12;
const int echoPin = 14;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
float threshold = 20;


void setup() {
  Serial.begin(115200); // Starts the serial communication

  WiFi.begin("fisch4", "cmsptani1a");


  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.println("Connecting..");

  }

  Serial.println("Connected to WiFi Network");



  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance
    distanceCm = duration * SOUND_VELOCITY / 2;

    // Prints the distance on the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);

    if (distanceCm < threshold) {


    HTTPClient http;

        
      http.begin(client, "http://192.168.3.62:8090/helloesp");
      int httpCode = http.GET(); //Send the request

      Serial.println("sending a request");


      http.end();   //Close connection

      delay(10000);
    }
  }


  delay(50);
}
