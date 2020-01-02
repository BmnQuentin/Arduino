// So i guess all cats are the same and don't like to drink from their bowl.
// This project aims to launch a water pump when some movement is detected nearby



//#define BLYNK_PRINT Serial // Comment this out to disable prints and save space
//#include <SPI.h>;
#include <ESP8266WiFi.h>;
#include <BlynkSimpleEsp8266.h>;
//#include <SimpleTimer.h>; Désactivé pour le deepsleep mode

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxx"; // Your Blynk auth ket here
char ssid[] = "xxx"; // Your Wifi ssid here
char pass[] = "xxx"; // Your Wifi pwd here

#define PIRPIN D2 // capteur de mvt sur pin digital : sur nodemcu, le 4 correspond au D2
#define PUMPPIN D1 // mosfet connecté pompe, D3 = 5 sur nodemcu v3

const int duree = 3000; //durée pompe en ms
int PirSTate = LOW;
int val=1;

// This function sends Arduino's up time every second to Virtual Pin (5, 6, 7 &amp;amp;amp;amp;amp;amp; 8).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  //Serial.println("Dans la boucle"); 

  //Blynk.virtualWrite(V5, h); // Humidity for gauge
  //Blynk.virtualWrite(V6, t); // Temperature for gauge
  //Serial.println("valeurs envoyées");
}

void setup()
{

  pinMode(PUMPPIN, OUTPUT);      // declare LED as output
  pinMode(PIRPIN, INPUT);     // declare sensor as input
  Serial.begin(57600);
  
  Blynk.begin(auth, ssid, pass);
  
  //On attend que le wifi soit connecté
  int nbEssais = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  digitalWrite(PUMPPIN, LOW);
  //sendSensor();
  Serial.println("Wifi OK");
}

void loop()
{
val=digitalRead(PIRPIN);
if (val==HIGH){
  Serial.println("Mouvement");
  digitalWrite(PUMPPIN, HIGH);
  delay(duree);
  digitalWrite(PUMPPIN, LOW);
}else{
  Serial.println("Rien ne bouge");
  delay (3000);
}

}
