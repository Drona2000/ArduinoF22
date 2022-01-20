 
/* IOT for Optimal Sleeping environment
 *  The purpose of this project is to create a device/program which measures 
 *  the room environment and gives feedback based on the observations. Experts 
 *  recommend a specific environment in a room for a individual to get 
 *  opti- mal sleep, and this program will be able to give feedback to the user. 
 *  This program will measure the room temperature, humidity, brightness and 
 *  noise and will make a RGB light up in either green, yellow or red based on 
 *  the sleeping environment. The project will use an ESP to upload the 
 *  observations to ThingSpeak.
 * 
 */



#include <DHT.h>                                 // Library defination
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h>  
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 0                                 // Connect DHT sensor to D3 in ESP module
#define DHTTYPE DHT11                            // Select type of DHT module

DHT dht(DHTPIN, DHTTYPE);  
const char* ssid = "Tenda_F46078";               // Enter your WiFi SSID 
const char* password = "12345678";               // Enter your WiFi Password 
WiFiClient client;  
unsigned long myChannelNumber = 1629388;         // Thingspeak details
const char * myWriteAPIKey = "NTII9WTNFZH9ZB7S"; 
const char* server = "api.thingspeak.com"; 
uint8_t temperature, humidity;  

int ledpinG=D7;                                  // Define PIN
int ledpinY=D6;
int ledpinR=D5;
int soundpin=A0;
int soundpinDigital=2;
int lightPin=D8;
int moistPin=D0;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup()  
{  
  Serial.begin(115200);                          // Serial Monitor initilized with bud rate 115200
  dht.begin(); 
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();                                  
  delay(10);
  pinMode(moistPin, INPUT);                     // led pin connected to D0  
  pinMode(lightPin, INPUT);                     // led pin connected to D8  
  pinMode(ledpinG, OUTPUT);                     // led pin connected to D7
  pinMode(ledpinY, OUTPUT);                     // led pin connected to D6
  pinMode(ledpinR, OUTPUT);                     // led pin connected to D5
  pinMode(soundpin, INPUT);                     // analog pin from sound sensor connected to A0 
  pinMode(soundpinDigital, INPUT);              // digital pin from sound sensor connected to D4 

  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid); 
  lcd.setCursor(0,0);
  lcd.print("IOT for Optimal"); 
  lcd.setCursor(0,1);
  lcd.print("Sleeping Enviro"); 
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting to"); 
  lcd.setCursor(0,1);
  lcd.print("WiFi."); 
  delay(500);
  lcd.print("."); 
  delay(500);
  lcd.print("."); 
  delay(500);
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connected");
  delay(1500);
  lcd.clear();
  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
}  


void loop()   
{  
  client.connect(server, 80);                   //connect(URL, Port)
  int sound=analogRead(soundpin);
  int light=digitalRead(lightPin);
  int moisture=digitalRead(moistPin);
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity();  
  
  Serial.print("Temperature Value is :");       // Serial Monitor print
  Serial.print(temperature);  
  Serial.println("°C");  
  Serial.print("Humidity Value is :");  
  Serial.print(humidity);  
  Serial.println("%");
  Serial.print("Sound level is: ");  
  Serial.print(sound); 
  Serial.println("dB");
  
// Conditiion for Light
if (light>=1){
  Serial.println("Light is ON");                 // Light ON
  //Serial.println("");  
}
else{
  Serial.println("Light is OFF");                // Light OFF 
    //Serial.println("");
      }
      
// Conditiion for Moisture
if (moisture>=1){
  Serial.println("Plant moisture wet");          // Plant moisture wet
  Serial.println("");  
}
else{
  Serial.println("Plant moisture dry");          // Plant moisture dry
    Serial.println("");
      }
      
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

 // LCD display for temperature and humidity 
  lcd.setCursor(0,0);
  lcd.print("Temperature ");
  lcd.setCursor(12,0);
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C"); 
  lcd.setCursor(0,1);
  lcd.print("Humidity");
  lcd.setCursor(12,1);
  lcd.print(humidity); 
  lcd.print("%");
   
  
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel. Here, we write for different fields.  
 
  
  ThingSpeak.setField(1, temperature);          //set data on the X graph for temperature
  ThingSpeak.setField(2, humidity);             //set data on the X graph for hummidity
  ThingSpeak.setField(3, sound);                //set data on the X graph for sound
  ThingSpeak.setField(4, light);                //set data on the X graph for light 
  ThingSpeak.setField(5, moisture);             //set data on the X graph for moisture
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);//post everything to TS
  client.stop();
    
 // delay(100);      // for timer   
} 
