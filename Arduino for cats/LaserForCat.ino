//NOTE : Digital pins #2, #13 and analog pins A0-A5 are not used by the shield.
// SUr MOsfet GDS : quand specs lisibles, dans l'ordre gate (pin commande) drain (+) source (gnd)

#include <Servo.h>

#define UPDATE_TIME 10
#define MAX_POS 60 //Angle maximal servo
#define MIN_POS 20 //Angle minimal servo
#define SensorPin 15 // A1 = GPIO15 sur arduino Uno
#define ServoPin 10   //Ser01 sur shield
#define LaserPin 17      // A2 = GPIO16 IMPORTANT : les ports ne délivrent pas assez de puissance pour alimenter le laser, il faut passer par un transistor ype 2N 3904 (note Q)

Servo myServo;
int pos = MIN_POS; //Angle servo
long randNumber1 = MIN_POS;
long randNumber2 = MAX_POS;
int varSpeed = UPDATE_TIME/3;

const int nbCycles = 10;

void setup() {
  
  pinMode(LaserPin, OUTPUT);
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  myServo.attach(ServoPin);
  myServo.write(pos);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(SensorPin) == HIGH) {
    jeu();
  }
  if (digitalRead(SensorPin) == LOW) {
    Serial.println("pas de mouvement detecte");
    //motor.run(RELEASE);

  }
  delay(1000);
}

void jeu() {
  digitalWrite(LaserPin, HIGH);
  for (int i = 0; i < nbCycles ; i += 1) {
    randNumber1 = random(MIN_POS , MAX_POS - 10);
    randNumber2 = random(randNumber1 , MAX_POS);
    for (pos = MIN_POS; pos <= randNumber2; pos += 1) {
      myServo.write(pos);
      delay(UPDATE_TIME+random(-varSpeed,varSpeed));
    }
    for (pos = randNumber2; pos >= randNumber1; pos -= 1) {
      myServo.write(pos);
      delay(UPDATE_TIME+random(-varSpeed,varSpeed));
    }
    for (pos = randNumber1; pos <= MAX_POS; pos += 1) {
      myServo.write(pos);
      delay(UPDATE_TIME+random(-varSpeed,varSpeed));
    }
    for (pos = MAX_POS; pos >= randNumber1; pos -= 1) {
      myServo.write(pos);
      delay(UPDATE_TIME+random(-varSpeed,varSpeed));
    }
    for (pos = randNumber1; pos <= randNumber2; pos += 1) {
      myServo.write(pos);
      delay(UPDATE_TIME+random(-varSpeed,varSpeed));
    }
    for (pos = randNumber2; pos >= MIN_POS; pos -= 1) {
      myServo.write(pos);
      delay(UPDATE_TIME+random(-varSpeed,varSpeed));
    }
  }
  digitalWrite(LaserPin, LOW);
}
