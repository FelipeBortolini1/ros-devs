#include<Embedded_Protocol_2.h>
#include<ArduinoJson.h>
#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle nh;
//ros::NodeHandle ns;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

Communication communication;
const int capacity = JSON_OBJECT_SIZE(6);
StaticJsonDocument<capacity> doc;

const int LIGHT = 10;

int delay_time;
int light_state = 1;

void messageCb(const std_msgs::String &msg)
{
  if(msg.data == "light_on"){
    digitalWrite(LIGHT,1);
    light_state = 1;
    communication.startBelief("light_state");
    communication.beliefAdd(light_state);
    communication.endBelief();
    communication.publishROSMessage(chatter, str_msg);
  }
}

ros::Subscriber<std_msgs::String> sub("chatter", &messageCb);

void setup()
{
  Serial.begin(9600);
  nh.initNode();
  nh.advertise(chatter);

//  nh.initNode();
  nh.subscribe(sub);

  pinMode(LIGHT,OUTPUT);
  digitalWrite(LIGHT,1);  //light starts on

  
  Serial.print("iniciando....");
  /* Build perception that the lihgt is on and send it to the upper layers */
  communication.startBelief("light_state");
  communication.beliefAdd(1);
  communication.endBelief();
  communication.publishROSMessage(chatter, str_msg);
  //delay(10000); //wait 30 seconds (to set up the multi-agent system)
}

void loop()
{
  // while(Serial.available() > 0){ //check whether there is some information from the serial (possibly from the agent)
  //    String s = Serial.readString();
  //    if(s.equals("light_on")){ //if the agent sends "light_on", then switch the light on
  //       digitalWrite(LIGHT,1);
  //       light_state = 1;
  //       communication.startBelief("light_state");
  //       communication.beliefAdd(light_state);
  //       communication.endBelief();
  //       communication.publishROSMessage(chatter, str_msg);
  //    }
  //  }

  if(light_state==1){
    /* wait a random time and switch the light off if it is on */
     delay_time = random(2,15)*1000;
     delay(delay_time);
     digitalWrite(LIGHT,0);
     light_state = 0;
     communication.startBelief("light_state");
     communication.beliefAdd(light_state);
     communication.endBelief();
     communication.publishROSMessage(chatter, str_msg);
     nh.spinOnce();
  }

  delay(1000);
}
