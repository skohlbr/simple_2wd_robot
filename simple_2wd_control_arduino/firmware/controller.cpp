

//#define USE_USBCON 0

#include <ros.h>
#include <simple_arduino_control_msgs/DiffDriveCommand.h>


#include <Arduino.h>
int led = 13;
bool led_on = false;


#include <AFMotor.h>
AF_DCMotor left_motor(2, MOTOR12_64KHZ);
AF_DCMotor right_motor(1, MOTOR12_64KHZ);


ros::NodeHandle nh;

simple_arduino_control_msgs::DiffDriveCommand cmd_debug;
ros::Publisher cmd_debug_pub("cmd_debug", &cmd_debug);

unsigned long last_cmd_time;

void command_cb( const simple_arduino_control_msgs::DiffDriveCommand& cmd_msg){

  cmd_debug = cmd_msg;


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


  if (led_on){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }

  led_on = !led_on;

}


ros::Subscriber<simple_arduino_control_msgs::DiffDriveCommand> sub("move_command_raw", command_cb);


void setup()
{
  pinMode(led, OUTPUT);

  nh.initNode();

  nh.advertise(cmd_debug_pub);

  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  cmd_debug_pub.publish(&cmd_debug);
  delay(10);
}
