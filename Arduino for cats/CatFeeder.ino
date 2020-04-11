#include <Servo.h>
#include <ESP8266WiFi.h>;
#include <BlynkSimpleEsp8266.h>;
#include <DHT.h>;

#define ServoPin 2   //D4 on NodeMCU
#define SwitchPin 13 // D7 on NodeMCU
#define MAX_POS 180 // Maximal angle servo
#define MIN_POS 20 //  Minimal angle servo
#define INTERMEDIATE_POS 70
#define UPDATE_TIME 3

char auth[] = "xxx"; // Blynk credentials
char ssid[] = "xxx"; // Box id
char pass[] = "xxx"; // Box pwd

int dureeDeepsleep = 300; // deepsleep duration
const int nbEssaisMax = 10;

Servo myservo;  // create servo object to control a servo
int pos = MIN_POS;  // variable to store the servo position
int RationCount = 0;

void setup()
{
  // attaches the servo on pin 10 to the servo object
  myservo.attach(ServoPin);
  myservo.write(MIN_POS);
  pinMode(SwitchPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Let's go!");

  Blynk.begin(auth, ssid, pass);
  //witing for the wifi to be connected
  int nbEssais = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (nbEssais >= nbEssaisMax) {
      ESP.deepSleep(dureeDeepsleep);
      Serial.println("Essai wifi");
    }
    nbEssais++;
  }
  Serial.println("Connected");
  myservo.detach();
}

void loop()
{
  if (digitalRead(SwitchPin) == LOW) {
    ration();
  }
}

void ration() {
  myservo.attach(ServoPin);
  Serial.println("Here's some food!");
  Serial.println("Step 1");
  for (pos = MIN_POS; pos <= MAX_POS; pos += 1)
  {
    myservo.write(pos);
    delay(UPDATE_TIME);
    Serial.println(pos);
  }
  Serial.println("Step 2");
  for (pos = MAX_POS; pos >= INTERMEDIATE_POS; pos -= 1)
  {
    myservo.write(pos);
    delay(UPDATE_TIME);
    Serial.println(pos);
  }
  Serial.println("Step 3");
  for (pos = INTERMEDIATE_POS; pos <= MAX_POS; pos += 1)
  {
    myservo.write(pos);
    delay(UPDATE_TIME);
    Serial.println(pos);
  }
  Serial.println("Step 4");
  for (pos = MAX_POS; pos >= MIN_POS; pos -= 1)
  {
    myservo.write(pos);
    delay(UPDATE_TIME);
    Serial.println(pos);
  }
  RationCount += 1;
  Blynk.virtualWrite(V4, RationCount);
  myservo.detach();
}
