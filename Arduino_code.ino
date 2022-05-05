#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;

std_msgs::String OurLedState;
ros::Publisher LEDstate("state", &OurLedState);

char RedState[20] = "The Red LED blinks!";
char BlueState[21] = "The Blue LED Blinks!";
char GreenState[22] = "The Green LED blinks!";

boolean red = false;
void RedOne( const std_msgs::Empty& toggle_msg) 
{  
  
digitalWrite(13, red);
red = !red;
OurLedState.data = RedState;
} 

boolean blue = false;
void BlueOne( const std_msgs::Empty& toggle_msg) 
{  
digitalWrite(12, blue);
blue = !blue;
OurLedState.data = BlueState;
} 

boolean green = false;
void GreenOne( const std_msgs::Empty& toggle_msg) 
{  
digitalWrite(11, green);
green = !green;
OurLedState.data = BlueState;
}

ros::Subscriber<std_msgs::Empty> RedLED("r", &RedOne ); 
ros::Subscriber<std_msgs::Empty> BlueLED("b", &BlueOne ); 
ros::Subscriber<std_msgs::Empty> GreenLED("g", &GreenOne );
void setup()  
{ 
pinMode(13, OUTPUT);
pinMode(12, OUTPUT); 
pinMode(11,OUTPUT);

nh.initNode(); 
nh.subscribe(RedLED);
nh.subscribe(BlueLED);
nh.subscribe(GreenLED);
nh.advertise(LEDstate);
} 

void loop()  
{  
LEDstate.publish( &OurLedState );
nh.spinOnce();  
delay(1);  
}
