#include <ros.h>
#include <std_msgs/String.h>
//#include <std_msgs/UInt16.h>
#include <simple_arduino_control_msgs/DiffDriveCommand.h>

//#include "../ros_lib/simple_arduino_control_msgs/DiffDriveCommand.h"


#include <Arduino.h>
#include <AFMotor.h>

ros::NodeHandle nh;

AF_DCMotor left_motor(2, MOTOR12_64KHZ);
AF_DCMotor right_motor(1, MOTOR12_64KHZ);

int led = 13;


unsigned long last_cmd_time;

void command_cb( const simple_arduino_control_msgs::DiffDriveCommand& cmd_msg){

  if (cmd_msg.left_motor_cmd == 0){
    left_motor.run(RELEASE);
    left_motor.setSpeed(0);
  }else if (cmd_msg.left_motor_cmd > 0){
    left_motor.run(FORWARD);
    left_motor.setSpeed( cmd_msg.left_motor_cmd*2);
  }else{
    left_motor.run(BACKWARD);
    left_motor.setSpeed(-cmd_msg.left_motor_cmd*2);
  }

  if (cmd_msg.right_motor_cmd == 0){
    right_motor.run(RELEASE);
    right_motor.setSpeed(0);
  }else if (cmd_msg.right_motor_cmd > 0){
    right_motor.run(FORWARD);
    right_motor.setSpeed( cmd_msg.right_motor_cmd*2);
  }else{
    right_motor.run(BACKWARD);
    right_motor.setSpeed(-cmd_msg.right_motor_cmd*2);
  }

}


ros::Subscriber<simple_arduino_control_msgs::DiffDriveCommand> sub("move_command_raw", command_cb);

void setup()
{

  nh.initNode();

  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
