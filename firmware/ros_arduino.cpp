//#define USE_USBCON
#include <ros.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt64.h>
#include <std_msgs/Bool.h>

#include <Arduino.h>
#define Encoder1A  2  //left encode
#define Encoder1B  3  //left encoder

#define motorIn1 4
#define motorIn2 5
#define LOOPTIME        50
ros::NodeHandle nh;

bool set_; 

geometry_msgs::Vector3 vel_msg;
std_msgs::UInt64 uint_msg;
std_msgs::Bool bool_msg;

ros::Publisher debug_1("DEBUG_1", &uint_msg);
ros::Publisher debug_2("DEBUG_2", &bool_msg);
int pin1A = 0;
int pin1AOld = 0;
int pin1B = 0;
int pin1BOld = 0;
int pin2A = 0;
int pin2AOld = 0;
int pin2B = 0;
int pin2BOld = 0;

volatile long Encoder1pos = 0;
unsigned long lastMilli = 0;                    // loop timing 
long dT = 0;


void left_encoder() 
{   pin1A = digitalRead(Encoder1A); pin1B = digitalRead(Encoder1B);
    if (pin1A == 0 && pin1B == 0) 
    {
      if (pin1AOld == 1 && pin1BOld == 0)   Encoder1pos --;
      if (pin1AOld == 0 && pin1BOld == 1)   Encoder1pos ++;
    }
    if (pin1A == 0 && pin1B == 1) 
    {
      if (pin1AOld == 0 && pin1BOld == 0)   Encoder1pos --;
      if (pin1AOld == 1 && pin1BOld == 1)   Encoder1pos ++;
    }
    if (pin1A == 1 && pin1B == 1) 
    {
      if (pin1AOld == 0 && pin1BOld == 1)   Encoder1pos --;
      if (pin1AOld == 1 && pin1BOld == 0)   Encoder1pos ++;
    }
    if (pin1A == 1 && pin1B == 0) 
    {
      if (pin1AOld == 1 && pin1BOld == 1)   Encoder1pos --;
      if (pin1AOld == 0 && pin1BOld == 0)   Encoder1pos ++;
    }
  pin1AOld = pin1A; pin1BOld = pin1B;
	bool_msg.data=1;
//        debug_2.publish(&bool_msg);

}


 


void setup() 
{
  nh.initNode();
  nh.advertise(debug_1);
  nh.advertise(debug_2);
  bool_msg.data=0;
  uint_msg.data=0.0;
  debug_1.publish(&uint_msg);

  pinMode(motorIn1,OUTPUT);   pinMode(motorIn2,OUTPUT);   
  pinMode(Encoder1A, INPUT);  pinMode(Encoder1B, INPUT);  
  
  digitalWrite(Encoder1A, HIGH);  digitalWrite(Encoder1B, HIGH);  

  attachInterrupt(0, left_encoder, CHANGE); attachInterrupt(1, left_encoder, CHANGE); 
  
  //Serial.begin (115200);
  //Serial.println("start"); 
}

void loop() 
{
     
     if((millis()-lastMilli) >= LOOPTIME)   
     {                                    // enter tmed loop
        lastMilli = millis();

	analogWrite(motorIn1,abs(5));  
	analogWrite(motorIn2,0);
       
        uint_msg.data=Encoder1pos;
        debug_1.publish(&uint_msg);
        debug_2.publish(&bool_msg);

        nh.spinOnce();
        //printMotorInfo();
     }

}

