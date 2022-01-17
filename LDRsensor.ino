const int ledPin = 13;
const int ldrPin = A0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);

}

void loop() {
  // read the status of the LDR
  int ldrStatus = analogRead(ldrPin);
  // if the LDR status is 100 or below the LED is turned on (it's dark)
  if (ldrStatus <= 100) {

    digitalWrite(ledPin, HIGH);
    Serial.print("Its DARK, Turn on the LED : ");
    Serial.println(ldrStatus);
  // if the LDR status is above 100, turn off the LED (it's bright)
  } else {

    digitalWrite(ledPin, LOW);
    Serial.print("Its BRIGHT, Turn off the LED : ");
    Serial.println(ldrStatus);

  }
  delay(2000);
}
