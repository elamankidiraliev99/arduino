
#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <dht.h>


#define dht_apin A0 // Analog Pin sensor is connected to

dht DHT;

ros::NodeHandle  nh;


std_msgs::Float32 temp_msg;
ros::Publisher pub_temp("TEMPERATURE", &temp_msg);

std_msgs::Float32 humidity_msg;
ros::Publisher pub_humidity("HUMIDITY", &humidity_msg);

//std_msgs::String pirs_msg;
//ros::Publisher pub_pirs("PIRSENSOR", &pirs_msg);

std_msgs::Float32 PIRSensorState_msg;
ros::Publisher pub_pirsstate("PIRSensorState_msg", &PIRSensorState_msg);


int ledPin = 13; // choose the pin for the LED
int inputPin = 2; // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status


void setup()
{
  pinMode(ledPin, OUTPUT); // declare LED as output
  pinMode(inputPin, INPUT); // declare sensor as input
  nh.initNode();
  nh.advertise(pub_temp);
  //nh.initNode();
  nh.advertise(pub_humidity);
  //nh.initNode();
  //nh.advertise(pub_pirs);
  //nh.initNode();
  nh.advertise(pub_pirsstate);
}



void loop()
{
  DHT.read11(dht_apin);
  temp_msg.data = DHT.temperature;
  pub_temp.publish(&temp_msg);
  humidity_msg.data = DHT.humidity;
  pub_humidity.publish(&humidity_msg);
  delay(1000);
  
  val = digitalRead(inputPin);
  
  
  if (val == HIGH) { // check if the input is HIGH
    digitalWrite(ledPin, HIGH); // turn LED ON
    if (pirState == LOW) { // we have just turned on
      //pirs_msg.data = "Motion detected!"; // We only want to print on the output change, not state
      //pub_pirs.publish(&pirs_msg);
      PIRSensorState_msg.data = 1.0;
      pub_pirsstate.publish(&PIRSensorState_msg);
      pirState = HIGH;
    }
  } 
  else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){ // we have just turned of

      //pirs_msg.data = "Motion ended!"; // We only want to print on the output change, not state
     // pub_pirs.publish(&pirs_msg);
      PIRSensorState_msg.data = 0.0;
      pub_pirsstate.publish(&PIRSensorState_msg);
      pirState = LOW; 
    } 
  }




  nh.spinOnce();
}



