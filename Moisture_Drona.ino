/*
 * 
 * It is a partial code for project IOT for optimal sleeping environment 
 * Plant mud moisture sensor
 * By Drona Ghimire
 */

#include <ESP8266WiFi.h>                   // Library defination
#include <WiFiClient.h>  
#include <ThingSpeak.h> 
 
const int moistPin = 12;                      // Define PIN
const int moistsens = A1;

const char* ssid = "Your SSID";             // Enter your WiFi SSID 
const char* password = "Your Password";     // Enter your WiFi Password 
WiFiClient client;  
unsigned long myChannelNumber = xxxxxxx;    // Thingspeak details
const char * myWriteAPIKey = "xxxxxxxxxxxxx"; 
const char* server = "api.thingspeak.com"; 

void setup() {
  Serial.begin(115200);
  pinMode(moistPin, OUTPUT);
  pinMode(moistsens, INPUT);

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
  // read the status of the moisture sensor
  int moistStatus = analogRead(moistsens);
  
 // if the moisture sensor status is 150 or below (it's dry)
  if (moistStatus <= 150) {
    digitalWrite(moistPin, LOW);
    Serial.print("Its DRY,: ");
    Serial.println(moistStatus);
    Serial.println();
    
  // if the moisture sensor status is above 150 (it's WET)
  } else {
    digitalWrite(moistPin, HIGH);
    Serial.print("Its WET,: ");
    Serial.println(moistStatus);
    Serial.println();
  }
   ThingSpeak.setField(1, moisture);                //set data on the X graph for light 
   ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);//post everything to TS
   client.stop();
   delay(1000);
}
