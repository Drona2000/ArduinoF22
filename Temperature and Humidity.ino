#include <DHT.h>
#include <ESP8266WiFi.h>

String apiKey = "0PL7AFG5PNAUSDWM";//TS channel
const char* ssid = "WiFimodem-7E70";
const char* password = "etm4mgmwaz";
const char* server = "api.thingspeak.com";
 
#define DHTPIN 2 //Connected to Data pin D4
#define DHTTYPE DHT22 
 
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
 
void setup() 
{
Serial.begin(115200);// Sensor baud rate
delay(10);
dht.begin();
 
WiFi.begin(ssid, password);
 
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
 
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) //Checking condition for Wifi Connection
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
 
}
 
void loop() 
{
 
float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t)) //Checking if sensor is  not reading any of temperature and Humidity values.
{
Serial.println("Failed to read from DHT sensor!");
return;
}
 
if (client.connect(server,80)) {//api.thingspeak.com
String postStr = apiKey;
postStr +="&field1=";
postStr += String(t);//field 1 is displaying graph of Temperature values 
postStr +="&field2=";
postStr += String(h);//field 2 is displayig graph of Humidity Values
postStr += "\r\n\r\n";
 
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);
 
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" degrees Celsius Humidity: ");
Serial.print(h);
Serial.println("Sending data to Thingspeak");
}
client.stop();
 
Serial.println("Waiting 20 secs");
// thingspeak needs at least a 20 sec delay between updates
// 20 seconds to be safe
delay(20000);
} 
