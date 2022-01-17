#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
const char* ssid = "VPRIME";
const char* pass = "virendra";
WiFiClient client;

unsigned long channelID = 1633876; //your TS channal
const char * APIKey = "8AKFKWP4151FANXM"; //your TS API
const char* server = "api.thingspeak.com";
const int postDelay = 5 * 1000; //post data every 20 seconds

int ledpin=13; 
int soundpin=A0;
int soundpinDigital=2;
int threshold=200;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //sensor baud rate
  WiFi.begin(ssid, pass);
  pinMode(ledpin, OUTPUT); // led pin connected to D7
  pinMode(soundpin, INPUT);// analog pin connected to A0 
  pinMode(soundpinDigital, INPUT); // digital pin connected to 2 
}


void loop() {
  // put your main code here, to run repeatedly:
  // int soundsense=analogRead(soundpin);
  int soundsense=digitalRead(soundpin); //Noise level sensor output pin 
    ThingSpeak.begin(client);
  client.connect(server, 80); //connect(URL, Port)
  ThingSpeak.setField(1, soundsense); //set data on the X graph
  ThingSpeak.writeFields(channelID, APIKey);//post everything to TS
  client.stop();
  Serial.print("Analog data is: "); // print as Analog data is 
  Serial.print(soundsense);
  Serial.println();
  delay(postDelay); //wait and then post again

 if (soundsense>=threshold){
    digitalWrite(ledpin, HIGH); // led is on
  }
  else{
    digitalWrite(ledpin, LOW); // led is off
  }
  delay(100);

}
