//
// The Annoying Maze
// -----------------
// Authors: Daniel Yamin, Tabitha Grace Royal
//

// pins definitions
const int btnPin = 2;
const int motorPin = 5;
const int ledPin = 13;
const int piezoPin = A0;

// tone freq constans
const int LOW_FREQ = 490;
const int HIGH_FREQ = 530;

// states
volatile int oppositeBtnState = 1;
int ledState = HIGH;
int toneState = HIGH_FREQ;

// timing vars
unsigned long previousMillisForLeds = 0;
unsigned long previousMillisForTone = 0;
const long interval = 100;

void setup() {
  pinMode(btnPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin , OUTPUT);
  pinMode(motorPin , OUTPUT);

  // init state
  digitalWrite(motorPin, oppositeBtnState);
  digitalWrite(ledPin, ledState);
  tone(piezoPin, toneState);
  
  Serial.begin(9600);
}


void loop() {
  oppositeBtnState = !digitalRead(btnPin);
  ledsController();
  piezoController();
  motorController();
}

void ledsController() {
  if (oppositeBtnState) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillisForLeds >= interval) {
        previousMillisForLeds = currentMillis;
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }
      }
      digitalWrite(ledPin, ledState);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void piezoController() {
  if (oppositeBtnState) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillisForTone >= interval) {
        previousMillisForTone = currentMillis;
        if (toneState == HIGH_FREQ) {
          toneState = LOW_FREQ;
        } else {
          toneState = HIGH_FREQ;
        }
      }
      tone(piezoPin, toneState);
  } else {
      noTone(piezoPin);
  }
}

void motorController() {
   digitalWrite(motorPin, oppositeBtnState);
}
