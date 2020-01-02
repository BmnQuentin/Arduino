//Quentin Bonnemaison, 08/01/2019
//Module autonome DHT11 sur NodemCU avec mode deespleep optimisé pour economie batterie
//Points d'attention :
//   - Attention au cable usb : s'il est de mauvaise qualité on peut avoir un problème pour téléverser le programme
//   - Le Baudrate peut être diminué ou augmenté, selon l'humeur du pc
//   - Reglages NodeMcu 1.0/57600/80MHz/1MSPIFFS/DIsabled/rien/lower/FLash/Only sketch
//   - Le COM peut être réglé également selon le port usb
//   - POUR LE DEEPSLEEP PENSER A CONNECTER LA BROCHE D0 DU NODEMCU A LA BROCHE RST MAIS LE RETIRER POUR UPLOAD
//   - Les serial sont interessants mais desactivés pour economiser la batterie
//Next steps : désactiver la led d'état lors d'envoi wifi


//#define BLYNK_PRINT Serial // Comment this out to disable prints and save space
//#include <SPI.h>;
#include <ESP8266WiFi.h>;
#include <BlynkSimpleEsp8266.h>;
//#include <SimpleTimer.h>; Désactivé pour le deepsleep mode
#include <DHT.h>;

int h, t = 0;
int delai = 10; // durée du délai entre deux envois en secondes
int dureeDeepsleep = 300; //durée en secondes du deepsleep
const int nbEssaisMax = 10;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxx"; // Your Blynk auth ket here
char ssid[] = "xxx"; // Your Wifi ssid here
char pass[] = "xxx"; // Your Wifi pwd here

#define DHTPIN 2 // What digital pin we're connected to : sur nodemcu, le 2 correspond au D4
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5, 6, 7 &amp;amp;amp;amp;amp;amp; 8).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  //Serial.println("Dans la boucle"); 
  //dht.begin();
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // boucle car il arrive que le dht ne retourne aucune valeur (nan)
  while (isnan(h) || isnan(t)) {
    //Serial.println("Failed to read from DHT sensor!");
    h = dht.readHumidity();
    t = dht.readTemperature();
    delay(500);
  }
  
  Blynk.virtualWrite(V5, h); // Humidity for gauge
  Blynk.virtualWrite(V6, t); // Temperature for gauge
  //Serial.println("valeurs envoyées");
}

void setup()
{
  //wifi_status_led_uninstall(); ne marche pas
  dureeDeepsleep = dureeDeepsleep * 1000000; // de base, en microsecondes
  //delai = delai * 1000; // de base, en millisecondes
  //Serial.begin(57600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  //On attend que le wifi soit connecté
  int nbEssais = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (nbEssais >= nbEssaisMax) {
      ESP.deepSleep(dureeDeepsleep);
    }
    nbEssais++;
  }
  //
  //Serial.println("Wifi COnnecté");
  // Setup a function to be called every second
  //timer.setInterval(delai, sendSensor);

  sendSensor();
  //Serial.println("Sensor passé");
  delay(1000); //nécessaire pour s'assurer que les virtualcwrite sont bien comptabilises
  // ATTENTION !!!!! POUR LE DEEPSLEEP PENSER A CONNECTER LA BROCHE D0 DU NODEMCU A LA BROCHE RST 
  //MAIS LE RETIRER POUR L UPLOAD
  ESP.deepSleep(dureeDeepsleep);
}

void loop()
{
  //La loop ne sert à rien pendant le deepsleep mode
  
  // Serial.println(WiFi.status());
  // Blynk.run(); // Initiates Blynk
  // timer.run(); // Initiates SimpleTimer

  //h = dht.readHumidity(0); //calculés avant pour cause de latence dans acquisition
  //t = dht.readTemperature(0);
  //Serial.print("Humidite : ");
  //Serial.println(h);
  //Serial.print("Temperature : ");
  //Serial.println(t);
  //sendSensor(); //inclus dans le timer ?
  //delay(delai);

}
