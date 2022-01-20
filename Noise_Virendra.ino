/*
 * 
 * It is a partial code for project IOT for optimal sleeping environment 
 * Noise intensity sensor
 * By Virendra
 */

#include <ESP8266WiFi.h>                   // Library defination
#include <WiFiClient.h>  
#include <ThingSpeak.h> 
 
int ledpinG=D7;                                  // Define PIN
int ledpinY=D6;
int ledpinR=D5;
int soundpin=A0;
int soundpinDigital=2;

const char* ssid = "Your SSID";             // Enter your WiFi SSID 
const char* password = "Your Password";     // Enter your WiFi Password 
WiFiClient client;  
unsigned long myChannelNumber = xxxxxxx;    // Thingspeak details
const char * myWriteAPIKey = "xxxxxxxxxxxxx"; 
const char* server = "api.thingspeak.com"; 

void setup() {
  Serial.begin(115200);
  pinMode(ledpinG, OUTPUT);                     // led pin connected to D7
  pinMode(ledpinY, OUTPUT);                     // led pin connected to D6
  pinMode(ledpinR, OUTPUT);                     // led pin connected to D5
  pinMode(soundpin, INPUT);                     // analog pin from sound sensor connected to A0 
  pinMode(soundpinDigital, INPUT);              // digital pin from sound sensor connected to D4

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
  // read the status of the noise sensor
  int sound=analogRead(soundpin);
       
// Condition for noise intensity   
 if (sound>=80){
    digitalWrite(ledpinR, HIGH);                 // intensity high
    digitalWrite(ledpinY, HIGH); 
    digitalWrite(ledpinG, HIGH);
  }
  else if (sound>=75){
    digitalWrite(ledpinY, HIGH);                 // intensity medium
    digitalWrite(ledpinG, HIGH);
    digitalWrite(ledpinR, LOW);
  }
  else{
    digitalWrite(ledpinG, HIGH);                 // intensity low
    digitalWrite(ledpinY, LOW);
    digitalWrite(ledpinR, LOW);
      }
   ThingSpeak.setField(1, sound);                //set data on the X graph for light 
   ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);//post everything to TS
  client.stop();
   delay(1000);
}
