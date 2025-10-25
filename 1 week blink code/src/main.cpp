// reg number :23-ntu-cs-1042 
// name : mahnoor shahid 

#include <Arduino.h> 

int ledPin = 13;  

void setup() {
  pinMode(ledPin, OUTPUT);  //13 as output
}

void loop() {
  digitalWrite(ledPin, HIGH);  
  delay(1000);                 
  digitalWrite(ledPin, LOW);   
  delay(1000);                 
}
