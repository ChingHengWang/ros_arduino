#include <Metro.h>

#define encoder0PinA  2
#define encoder0PinB  3
#define MotorPin1  9
#define MotorPin2  10
int pinAState = 0;
int pinAStateOld = 0;
int pinBState = 0;
int pinBStateOld = 0;
int error=0;
int cmd0Pos=0;
int cmdPwm=0;
int vPlus=0;
int vMinus=0;
int Sum_e=0;
volatile long encoder0Pos = 0;
volatile long unknownvalue = 0;
Metro mainTimer = Metro(10);

void setup() { 
  
 pinMode(MotorPin2, OUTPUT); 
 pinMode(MotorPin1, OUTPUT);  
  
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
/*
    Serial.print("Encoder: ");
    Serial.print(encoder0Pos, DEC);
    Serial.print("     unKnown: ");
    Serial.print(unknownvalue, DEC);
    Serial.println("");
*/

    Sum_e=error+Sum_e;
    
    cmd0Pos=0;
    error=cmd0Pos-encoder0Pos;
    cmdPwm=0.5*(error)+0.01*Sum_e;
    
    
    //error=250;
    if(cmdPwm>=0)
    {
      vPlus=cmdPwm;
      vMinus=0;
    }
    else if(cmdPwm<0)
     {
      vPlus=0;
      vMinus=-cmdPwm;
    }   
    
     if(vPlus>=255)
        vPlus=255;
     else if(vPlus<-255)
          vPlus=-255;
          
          
     if(vMinus>=255)
        vMinus=255;
     else if(vMinus<-255)
          vMinus=-255;      
    
    Serial.print("error  ");Serial.print(error); Serial.print("     vPlus  ");Serial.print(vPlus);Serial.print("     vMinus  ");  Serial.print(vMinus);    Serial.print("Encoder: ");  Serial.print(encoder0Pos);      
    Serial.print(" unKnown: ");
    Serial.print(unknownvalue, DEC);  
    Serial.println("");
    
    analogWrite(MotorPin2,vPlus);
    analogWrite(MotorPin1,vMinus);
    
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



