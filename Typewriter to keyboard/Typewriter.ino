#include <Keyboard.h>
#include <HID.h>

/******************************************************************************
  Beware, think of adding a 100kOhm between Gnd and A0 to prevent floating value, around 350
******************************************************************************/

const int SOFT_POT_PIN = A0; // Pin connected to softpot wiper
const int stateNull = 1020; // Defines state where no value has to be considered
int pinEspace = 2;
int pinMaj = 4;
int pinBack = 6;
int pinEnter = 8;
boolean stateEspace;
boolean stateMaj;
boolean stateBack;
boolean stateEnter;
const int delayKey = 50; //delay before taking value after  character is typed
const int delayThreshold = 50; // delay in measuring loop when a key is pressed
bool valueToPrint;
bool specialValueToPrint;
int currentKey;
int currentSpecialKey;
int keyToPrint;
boolean spaceAllowed; // flag to prevent us from having multiple spaces
boolean enterAllowed;
boolean backAllowed;

void setup()
{
  Serial.begin(9600);
  Keyboard.begin();
  pinMode(SOFT_POT_PIN, INPUT);
  pinMode(pinEspace, INPUT_PULLUP);
  pinMode(pinMaj, INPUT_PULLUP);
  pinMode(pinBack, INPUT_PULLUP);
  pinMode(pinEnter, INPUT_PULLUP);
  valueToPrint = 0;
  spaceAllowed = 0;
  enterAllowed = 0;
  backAllowed = 0;
}

void loop()
{
  // Lecture du softpot
  delay(delayKey);
  int softPot = analogRead(SOFT_POT_PIN);
  stateEspace = digitalRead(pinEspace);
  stateBack = digitalRead(pinBack);
  stateEnter = digitalRead(pinEnter);
  //Serial.println(softPot);

  //We decide if space is maintained it enables us to have special values or special controls
  while (!digitalRead(pinEspace)) {
    delay(delayThreshold); //Necessary to avoid hysteresis
    softPot = analogRead(SOFT_POT_PIN);
    if (softPot <= stateNull) {
      specialValueToPrint = 1;
      if (softPot < currentSpecialKey ) {
        currentSpecialKey = softPot;
      }
    }
    else {
      spaceAllowed = 1;
    }
  }

  if (specialValueToPrint) {
    //Serial.println(currentKey);
    keyToPrint = currentSpecialKey;
    currentSpecialKey = stateNull + 1;
    specialValueToPrint = 0;
    spaceAllowed = 0;
    alphabetSpecial(keyToPrint);
  }

  if (!stateEspace && spaceAllowed) {
    sendtext(" ");
    spaceAllowed = 0;
  }

  //Back
  if (stateBack) {
    backAllowed = 1;
  }

  if (!stateBack && backAllowed) {
    backspacekey(1);
    backAllowed = 0;
  }

  //Enter
  if (stateEnter) {
    enterAllowed = 1;
  }

  if (!stateEnter && enterAllowed) {
    sendkeypad("E");
    enterAllowed = 0;
  }

  // All maj and min characters
  while (softPot <= stateNull ) {
    //Serial.println(softPot);
    valueToPrint = 1;
    stateMaj = !digitalRead(pinMaj);
    softPot = analogRead(SOFT_POT_PIN);
    //Serial.println(currentKey);
    if (softPot < currentKey ) {
      currentKey = softPot;
    }
    delay(delayThreshold);
  }

  if (valueToPrint) {
    //Serial.println(currentKey);
    keyToPrint = currentKey;
    currentKey = stateNull + 1;
    valueToPrint = 0;
    if (stateMaj) {
      alphabetMax(keyToPrint);
    }
    else {
      alphabetMin(keyToPrint);
    }
  }
}
