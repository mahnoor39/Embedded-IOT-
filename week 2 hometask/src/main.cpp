#include <Arduino.h>


// Week-2-HomeTask
// Reg. No.: 23-NTY-CS-1042
//name : mahnoor shahid 

const int buttonPin = 32;
const int ledPin1 = 16;
const int ledPin2 = 17;

bool toggleState = false;        
bool lastButtonState = HIGH;      

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentButtonState == LOW) {
    toggleState = !toggleState;   // flip state

    if (toggleState) {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
    } else {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
    }

    delay(200); 
  }

  lastButtonState = currentButtonState;
}