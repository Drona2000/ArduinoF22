/*
 * 
 * It is a partial code for project IOT for optimal sleeping environment 
 * 
 */
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_G 4                   //define green LED pin
#define LED_R 5                   //define red LED 
const int ledPin = 8;
const int moistPin = 7;
const int ldrPin = A0;
const int moistsens = A1;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo;                     //define servo name

void setup() {
  Serial.begin(115200);           // Initiate a serial communication
  SPI.begin();                     // Initiate  SPI bus
  mfrc522.PCD_Init();              // Initiate MFRC522
  myServo.attach(3);              //servo pin
  myServo.write(0);               //servo start position
  
  pinMode(moistPin,OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(moistsens, INPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  Serial.println("Put your card to the reader...");
  Serial.println();
}

void loop() {

  
  // read the status of the LDR
  int ldrStatus = analogRead(ldrPin);

    // read the status of the moisture sensor
  int moistStatus = analogRead(moistsens);
  
  // if the LDR status is 80 or below (it's dark)
  if (ldrStatus <= 80) {
    digitalWrite(ledPin, LOW);
    Serial.print("Its DARK,: ");
    Serial.println(ldrStatus);
    //Serial.println(ledPin);
    
  // if the LDR status is above 80 (it's bright)
  } else {
    digitalWrite(ledPin, HIGH);
    Serial.print("Its BRIGHT,: ");
    Serial.println(ldrStatus);
    //Serial.println(ledPin);
  }
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
  delay(1000);
  // Look for new cards to RFID read
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "C3 E5 97 1A") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
    Serial.println("Door Open");
    delay(300);
    myServo.write(180);
    delay(5000);
    myServo.write(0);
    digitalWrite(LED_G, LOW);
    Serial.println("Door Locked");
  }
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(LED_R, HIGH);
    delay(1000);
    digitalWrite(LED_R, LOW);
  }
  delay(2000);
}
