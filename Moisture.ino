//https://techatronic.com/water-level-indicator-using-nodemcu/

#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
const char* ssid = "Tenda_F46078";
const char* pass = "12345678";

WiFiClient client;
unsigned long channelID = 1629388; //your TS channal
const char * APIKey = "NTII9WTNFZH9ZB7S"; //your TS API
const char* server = "api.thingspeak.com";
int val = 0 ; 
  
 void setup()  
 {  
   Serial.begin(115200); // sensor buart rate  
   WiFi.begin(ssid, pass);
   pinMode(14,HIGH);  // Blue led Pin Connected To D5 Pin   
   pinMode(13,HIGH);  // Red Led Pin Connected To D7 Pin   
   pinMode(12,HIGH);  // Green Led Connected To D6 Pin    
 }  
 void loop()   
 {  
  int s1=analogRead(A0); // Water Level Sensor output pin connected A0  
  ThingSpeak.begin(client);
  client.connect(server, 80); //connect(URL, Port)
  ThingSpeak.setField(1, s1); //set data on the X graph
  ThingSpeak.writeFields(channelID, APIKey);//post everything to TS
  client.stop();
  Serial.println(s1);  // See the Value In Serial Monitor     
  delay(1000);      // for timer  
 /* if(s1>200 && s1<=400 )  
   {   
    digitalWrite(14,HIGH);   // Blue led ON   
   }   
  else   
   {   
   digitalWrite(14,LOW);    // Blue led OFF  
   }   
  if(s1>400 )  
   {   
   digitalWrite(12,HIGH);   // Green led ON   
   }  
   else   
   {   
   digitalWrite(12,LOW);   // Green led OFF   
   }   
   if(s1<200)   
   {  
   digitalWrite(13,HIGH);  // Red led ON   
   }  
   else  
   {  
   digitalWrite(13,LOW);   // Red led OFF   
   }*/  
  }  



/*float data; //measured data
void loop() {
//data = 42.0;
long rssi= WiFi.RSSI();
ThingSpeak.begin(client);
client.connect(server, 80); //connect(URL, Port)
//ThingSpeak.setField(1, data); //set data on the X graph
ThingSpeak.setField(1, rssi); //set data on the X graph
ThingSpeak.writeFields(channelID, APIKey);//post everything to TS
client.stop();
delay(postDelay); //wait and then post again
}*/
