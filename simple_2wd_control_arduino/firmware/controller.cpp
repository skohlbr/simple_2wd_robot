#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

#include <Arduino.h>
#include <AFMotor.h>

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";
char bla[13] = "bla";
uint16_t val_;

void servo_cb( const std_msgs::UInt16& cmd_msg){
  val_ = cmd_msg.data;
  //servo.write(cmd_msg.data); //set servo angle, should be from 0-180  
  //digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}


ros::Subscriber<std_msgs::UInt16> sub("servo", servo_cb);

void setup()
{
  val_ = 0;

  nh.initNode();
  nh.advertise(chatter);

  nh.subscribe(sub);
}

void loop()
{
  if (val_ < 10)
    str_msg.data = hello;
  else
    str_msg.data = bla;
  
  chatter.publish( &str_msg );
  nh.spinOnce();
  delay(1000);
}
