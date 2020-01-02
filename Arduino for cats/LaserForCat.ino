// This project launches a laser for your cat to play with it 

#include <Servo.h>


#define UPDATE_TIME 5
#define MAX_POS 160
#define MIN_POS 20
#define ServoPin 5
#define LaserPin 4      //IMPORTANT : les ports ne délivrent pas assez de puissance pour alimenter le laser, il faut passer par un transistor ype 2N 3904

Servo myServo;

int pos = MIN_POS;
int jeuActif = 0;
const int nbCycles = 4;

// set up the 'digital' feed
AdafruitIO_Feed *digital = io.feed("digital");

void setup() {

  //pinMode(LED_PIN, OUTPUT);

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while (! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'digital' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  digital->onMessage(handleMessage);

  // wait for a connection
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  myServo.attach(ServoPin);
  myServo.write(pos);
  Serial.println("Moteur ok");
  
  digital->get();



}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  // A partir de la impro totale
  //Serial.println(toInt(Malifaux->toPinLevel()));
  //delay(1000);
  if (jeuActif)
    jeu();
}

// this function is called whenever an 'digital' feed message
// is received from Adafruit IO. it was attached to
// the 'digital' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");

  if (data->toPinLevel() == HIGH) {
    Serial.println("HIGH");
    jeuActif = 1;
  }
  else {
    Serial.println("LOW");
    jeuActif = 0;
  }
  //digitalWrite(LED_PIN, data->toPinLevel());
}

void jeu() {
  digitalWrite(LaserPin, HIGH);
  for (int i = 0; i < nbCycles ; i += 1) {
    for (pos = MIN_POS; pos <= MAX_POS; pos += 1) {
      myServo.write(pos);
      delay(UPDATE_TIME);
    }
    for (pos = MAX_POS; pos >= MIN_POS; pos -= 1) {
      myServo.write(pos);
      delay(UPDATE_TIME);
    }
  }
  digitalWrite(LaserPin, LOW);
}
