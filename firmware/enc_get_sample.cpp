#include <Metro.h>

#define encoder0PinA  2
#define encoder0PinB  3

int pinAState = 0;
int pinAStateOld = 0;
int pinBState = 0;
int pinBStateOld = 0;

volatile long encoder0Pos = 0;
volatile long unknownvalue = 0;
Metro mainTimer = Metro(10);

void setup() { 
  
  
 pinMode(encoder0PinA, INPUT); 
 digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor
 pinMode(encoder0PinB, INPUT); 
 digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor

 attachInterrupt(0, doEncoder, CHANGE);  // encoder pin on interrupt 0 - pin 2
 attachInterrupt(1, doEncoder, CHANGE);
 
 Serial.begin (115200);
 Serial.println("start");                // a personal quirk

} 

void loop(){
// do some stuff here - the joy of interrupts is that they take care of themselves
  if (mainTimer.check() == true) {

    
    Serial.print("Encoder: ");  Serial.print(encoder0Pos);      
    Serial.print(" unKnown: ");Serial.print(unknownvalue, DEC);  
    Serial.println("");
    
  }
}

void doEncoder() {
//   encoder0Pos++;
  pinAState = digitalRead(2);
  pinBState = digitalRead(3);

  if (pinAState == 0 && pinBState == 0) {
    if (pinAStateOld == 1 && pinBStateOld == 0) // forward
      encoder0Pos ++;
    if (pinAStateOld == 0 && pinBStateOld == 1) // reverse
      encoder0Pos --;
    if (pinAStateOld == 1 && pinBStateOld == 1) // unknown
      unknownvalue ++;
    if (pinAStateOld == 0 && pinBStateOld == 0) // unknown
      unknownvalue ++;
  }
  if (pinAState == 0 && pinBState == 1) {
    if (pinAStateOld == 0 && pinBStateOld == 0) // forward
      encoder0Pos ++;
    if (pinAStateOld == 1 && pinBStateOld == 1) // reverse
      encoder0Pos --;
    if (pinAStateOld == 1 && pinBStateOld == 0) // unknown
      unknownvalue ++;
    if (pinAStateOld == 0 && pinBStateOld == 1) // unknown
      unknownvalue ++;
  }
  if (pinAState == 1 && pinBState == 1) {
    if (pinAStateOld == 0 && pinBStateOld == 1) // forward
      encoder0Pos ++;
    if (pinAStateOld == 1 && pinBStateOld == 0) // reverse
      encoder0Pos --;
    if (pinAStateOld == 0 && pinBStateOld == 0) // unknown
      unknownvalue ++;
    if (pinAStateOld == 1 && pinBStateOld == 1) // unknown
      unknownvalue ++;
  }

  if (pinAState == 1 && pinBState == 0) {
    if (pinAStateOld == 1 && pinBStateOld == 1) // forward
      encoder0Pos ++;
    if (pinAStateOld == 0 && pinBStateOld == 0) // reverse
      encoder0Pos --;
    if (pinAStateOld == 0 && pinBStateOld == 1) // unknown
      unknownvalue ++;
    if (pinAStateOld == 1 && pinBStateOld == 0) // unknown
      unknownvalue ++;
  }
  pinAStateOld = pinAState;
  pinBStateOld = pinBState;
}

