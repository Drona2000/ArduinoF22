#include <DHT.h>                                 // Library defination
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h> 


#define DHTPIN 0                                 // Connect DHT sensor to D3 in ESP module
#define DHTTYPE DHT11                            // Select type of DHT module

DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "Your SSID";                  // Enter your WiFi SSID 
const char* password = "WiFi Password";          // Enter your WiFi Password 
WiFiClient client;  
unsigned long myChannelNumber = xxxxxxxx;         // Thingspeak details
const char * myWriteAPIKey = "xxxxxxxxxxxx"; 
const char* server = "api.thingspeak.com"; 
uint8_t temperature, humidity;  


void setup()  
{  
  Serial.begin(115200);                          // Serial Monitor initilized with bud rate 115200
  dht.begin(); 
  delay(10);

  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);
  delay(500);
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");
  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
  }  


void loop()   
{  
  client.connect(server, 80);                   //connect(URL, Port)
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity();

  Serial.print("Temperature Value is :");       // Serial Monitor print
  Serial.print(temperature);  
  Serial.println("°C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%");

   // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel. Here, we write for different fields.  
 
  
  ThingSpeak.setField(1, temperature);          //set data on the X graph for temperature
  ThingSpeak.setField(2, humidity);             //set data on the X graph for hummidity
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);//post everything to TS
  client.stop();
  delay(10000);
}
  
