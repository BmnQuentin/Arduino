/******************************************************************************
  Attention, think of adding a 100kOhm between Gnd and A0 to prevent floating value, around 350
******************************************************************************/

const int SOFT_POT_PIN = A0; // Pin connected to softpot wiper
const int etatNul = 10; // Defines state where no value has to be considered
const int dureeFrappe = 100; // Minimal duration of a stroke
int etatCourant;
const int tolerance = 10;
long derniereFrappe; // to prevent accidentl double letter
const int pinEspace = 2;
const int pinMaj = 3;
boolean etatEspace;
boolean etatMaj;

void setup()
{
  Serial.begin(9600);
  pinMode(SOFT_POT_PIN, INPUT);
  etatCourant = etatNul - 1;
  derniereFrappe=millis();
  pinMode(pinEspace,INPUT_PULLUP);
  pinMode(pinMaj, INPUT_PULLUP);
}

void loop()
{
  // Lecture du softpot
  int softPotADC = analogRead(SOFT_POT_PIN);
  etatEspace = !digitalRead(pinEspace);
  etatMaj=!digitalRead(pinMaj);

  if ((etatCourant - tolerance < softPotADC && softPotADC < etatCourant + tolerance) && millis()-derniereFrappe<dureeFrappe ) {
    
  }
  else {
    if(etatEspace) {
      Serial.print(" ");
    }
    if (softPotADC > etatNul) {
      Serial.println(softPotADC);
      etatCourant = softPotADC;
      if (etatMaj) {
        alphabetMax(softPotADC);
      }
      else {
      alphabetMin(softPotADC);
      }
      derniereFrappe=millis();
    }
  }
  delay(dureeFrappe);
}

void alphabetMin(int entree)
{
  if (entree < 25)
  {
    Serial.print("a");
  }
  else if (entree<40)
  {
    Serial.print("q");
  }
    else if (entree<70)
  {
    Serial.print("é");
  }
      else if (entree<90)
  {
    Serial.print("w");
  }
    else if (entree<110)
  {
    Serial.print("z");
  }
    else if (entree<140)
  {
    Serial.print("s");
  }
    else if (entree<160)
  {
    Serial.print("\"");
  }
    else if (entree<180)
  {
    Serial.print("x");
  }
    else if (entree<200)
  {
    Serial.print("e");
  }
    else if (entree<220)
  {
    Serial.print("d");
  }
    else if (entree<240)
  {
    Serial.print("'");
  }
    else if (entree<260)
  {
    Serial.print("c");
  }
    else if (entree<290)
  {
    Serial.print("r");
  }
    else if (entree<310)
  {
    Serial.print("f");
  }
    else if (entree<330)
  {
    Serial.print("(");
  }
    else if (entree<360)
  {
    Serial.print("v");
  }
    else if (entree<380)
  {
    Serial.print("t");
  }
    else if (entree<400)
  {
    Serial.print("g");
  }
    else if (entree<430)
  {
    Serial.print("-");
  }
    else if (entree<450)
  {
    Serial.print("b");
  }
    else if (entree<480)
  {
    Serial.print("y");
  }
    else if (entree<500)
  {
    Serial.print("h");
  }
    else if (entree<530)
  {
    Serial.print("è");
  }
    else if (entree<560)
  {
    Serial.print("n");
  }
    else if (entree<580)
  {
    Serial.print("u");
  }
    else if (entree<600)
  {
    Serial.print("j");
  }
    else if (entree<630)
  {
    Serial.print("_");
  }
    else if (entree<650)
  {
    Serial.print(",");
  }
      else if (entree<680)
  {
    Serial.print("i");
  }
      else if (entree<710)
  {
    Serial.print("k");
  }
    else if (entree<730)
  {
    Serial.print("ç");
  }
    else if (entree<760)
  {
    Serial.print(";");
  }
    else if (entree<780)
  {
    Serial.print("o");
  }
    else if (entree<800) 
  {
    Serial.print("l");
  }
    else if (entree<830)
  {
    Serial.print("à");
  }
    else if (entree<860)
  {
    Serial.print(":");
  }
    else if (entree<880)
  {
    Serial.print("p");
  }
    else if (entree<910)
  {
    Serial.print("m"); 
  }
    else if (entree<940)
  {
    Serial.print(")"); 
  }
    else if (entree<970)
  {
    Serial.print("="); 
  }
    else if (entree<990)
  {
    Serial.print("^"); 
  }
    else if (entree<1020)
  {
    Serial.print("ù"); 
  }
}

void alphabetMax(int entree)
{
  if (entree < 25)
  {
    Serial.print("A");
  }
  else if (entree<40)
  {
    Serial.print("Q");
  }
    else if (entree<70)
  {
    Serial.print("2");
  }
      else if (entree<90)
  {
    Serial.print("W");
  }
    else if (entree<110)
  {
    Serial.print("Z");
  }
    else if (entree<140)
  {
    Serial.print("S");
  }
    else if (entree<160)
  {
    Serial.print("3");
  }
    else if (entree<180)
  {
    Serial.print("X");
  }
    else if (entree<200)
  {
    Serial.print("E");
  }
    else if (entree<220)
  {
    Serial.print("D");
  }
    else if (entree<240)
  {
    Serial.print("4");
  }
    else if (entree<260)
  {
    Serial.print("C");
  }
    else if (entree<290)
  {
    Serial.print("R");
  }
    else if (entree<310)
  {
    Serial.print("F");
  }
    else if (entree<330)
  {
    Serial.print("5");
  }
    else if (entree<360)
  {
    Serial.print("V");
  }
    else if (entree<380)
  {
    Serial.print("T");
  }
    else if (entree<400)
  {
    Serial.print("G");
  }
    else if (entree<430)
  {
    Serial.print("6");
  }
    else if (entree<450)
  {
    Serial.print("B");
  }
    else if (entree<480)
  {
    Serial.print("Y");
  }
    else if (entree<500)
  {
    Serial.print("H");
  }
    else if (entree<530)
  {
    Serial.print("7");
  }
    else if (entree<560)
  {
    Serial.print("N");
  }
    else if (entree<580)
  {
    Serial.print("U");
  }
    else if (entree<600)
  {
    Serial.print("J");
  }
    else if (entree<630)
  {
    Serial.print("8");
  }
    else if (entree<650)
  {
    Serial.print("?");
  }
      else if (entree<680)
  {
    Serial.print("I");
  }
      else if (entree<710)
  {
    Serial.print("K");
  }
    else if (entree<730)
  {
    Serial.print("9");
  }
    else if (entree<760)
  {
    Serial.print(".");
  }
    else if (entree<780)
  {
    Serial.print("O");
  }
    else if (entree<800) 
  {
    Serial.print("L");
  }
    else if (entree<830) // we turn the & in a 1
  {
    Serial.print("1");
  }
    else if (entree<860)
  {
    Serial.print("/");
  }
    else if (entree<880)
  {
    Serial.print("P");
  }
    else if (entree<910)
  {
    Serial.print("M"); 
  }
    else if (entree<940) // we turn the ° in 0
  {
    Serial.print("0"); 
  }
    else if (entree<970)
  {
    Serial.print("+"); 
  }
    else if (entree<990)
  {
    Serial.print("!"); // we turn the ¨ in !
  }
    else if (entree<1020)
  {
    Serial.print("%");
  }
}

