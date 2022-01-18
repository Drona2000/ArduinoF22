#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
const char* ssid = "iPhone";
const char* pass = "8s5tp60rh9t66";
WiFiClient client;
unsigned long channelID = 1629357; //your TS channal
const char * APIKey = "RM3YHQXYGTNL8JTR"; //your TS API
const char* server = "api.thingspeak.com";
//const int postDelay = 20 * 1000; //post data every 20 seconds
const int postDelay = 2000;
const int ledPin = D2;
const int ldrPin = A0;
//int ledonoff = 0;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}
//float data; //measured data
void loop() {

  int ldrStatus = analogRead(ldrPin);

  if (ldrStatus <= 400) {

    digitalWrite(ledPin, HIGH);

    Serial.print("Its DARK, Turn on the LED : ");

    Serial.println(ldrStatus);

  } else {

    digitalWrite(ledPin, LOW);

    Serial.print("Its BRIGHT, Turn off the LED : ");

    Serial.println(ldrStatus);

  }

  /*if (ledonoff == 0) {
    digitalWrite(led, LOW);
    ledonoff = 1;
    } else {
    digitalWrite(led, HIGH);
    ledonoff = 0;
    }*/
  //long rssi = WiFi.RSSI();
  //10*exp(WiFi.RSSI()/10);
  //data = 42.0;
  ThingSpeak.begin(client);
  client.connect(server, 80); //connect(URL, Port)
  //ThingSpeak.setField(1, data); //set data on the X graph
  //ThingSpeak.setField(1, rssi);
  //ThingSpeak.setField(2, ledonoff);
  ThingSpeak.setField(3, ldrStatus);
  ThingSpeak.writeFields(channelID, APIKey);//post everything to TS
  client.stop();
  delay(postDelay); //wait and then post again
}
