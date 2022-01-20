/*
 * 
 * It is a partial code for project IOT for optimal sleeping environment 
 * LDR sensor
 * By Simon Friis
 */

#include <ESP8266WiFi.h>                   // Library defination
#include <WiFiClient.h>  
#include <ThingSpeak.h> 
 
const int ledPin = 13;                      // Define PIN
const int ldrPin = A0;

const char* ssid = "Your SSID";             // Enter your WiFi SSID 
const char* password = "Your Password";     // Enter your WiFi Password 
WiFiClient client;  
unsigned long myChannelNumber = xxxxxxx;    // Thingspeak details
const char * myWriteAPIKey = "xxxxxxxxxxxxx"; 
const char* server = "api.thingspeak.com"; 

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);

   WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");
  ThingSpeak.begin(client);
  }

  
void loop() {
   client.connect(server, 80);                   //connect(URL, Port)
  // read the status of the LDR
  int ldrStatus = analogRead(ldrPin);
  
  // if the LDR status is 80 or below (it's dark)
  if (ldrStatus <= 80) {
    digitalWrite(ledPin, LOW);
    Serial.print("Its DARK,: ");
    Serial.println(ldrStatus);

    
  // if the LDR status is above 80 (it's bright)
  } else {
    digitalWrite(ledPin, HIGH);
    Serial.print("Its BRIGHT,: ");
    Serial.println(ldrStatus);
   }
   ThingSpeak.setField(1, light);                //set data on the X graph for light 
   ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);//post everything to TS
  client.stop();
   delay(1000);
}
