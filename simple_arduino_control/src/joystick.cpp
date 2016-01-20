#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/QuaternionStamped.h>

#include <simple_arduino_control_msgs/DiffDriveCommand.h>

namespace simple_joy_control {

  ros::Subscriber joyInput;
  ros::Subscriber twistInput;

  ros::Publisher motionCommandOutput;

  ros::Publisher twistCommandOutput;
  //ros::Publisher cameraCommandOutput;

  simple_arduino_control_msgs::DiffDriveCommand motionCommand;
  geometry_msgs::Twist twistCommand;
  geometry_msgs::QuaternionStamped cameraCommand;

  int axis_speed;
  int axis_steer;
  double axis_speed_dead_zone;
  double axis_steer_dead_zone;

  void updateCommand(float speed_in, float angRate_in)
  {
    float speed = speed_in;
    float angRate = speed_in;

    if (std::abs(speed) < axis_speed_dead_zone){
     speed = 0.0f;
    }

    if(std::abs(angRate) < axis_steer_dead_zone){
      angRate = 0.0f;
    }

    //motionCommand.angularRate = -angRateSpeed;

    //twistCommand.linear.x = speed;
    //twistCommand.angular.z = angRateSpeed;

    float mag_left = speed - angRate;
    float mag_right = speed + angRate;

    float mag_max = std::max(mag_left, mag_right);

    if (mag_max > 1.0f){
      mag_left = mag_left / mag_max;
      mag_right = mag_right / mag_max;
    }

    motionCommand.left_motor_cmd = static_cast<int8_t>(mag_left * 127.0);
    motionCommand.right_motor_cmd = static_cast<int8_t>(mag_right * 127.0);

  }
  
  void twistCallback(const geometry_msgs::TwistConstPtr twist)
  {
    float speed = twist->linear.x;
    float angRate = twist->angular.z;
    
    updateCommand(speed, angRate);
  }

  void joyCallback(const sensor_msgs::JoyConstPtr joystick) {

    float speed = joystick->axes[axis_speed];
    float angRate = joystick->axes[axis_steer];
    
    updateCommand(speed, angRate);
  }
  
};



using namespace simple_joy_control;

int main(int argc, char **argv) {
  ros::init(argc, argv, ROS_PACKAGE_NAME);
  ros::NodeHandle n;

  joyInput = n.subscribe("joy", 10, joyCallback);
  twistInput = n.subscribe("cmd_vel", 10, twistCallback);
  motionCommandOutput = n.advertise<simple_arduino_control_msgs::DiffDriveCommand>("/move_command_raw", 10, false);

  //twistCommandOutput = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10, false);
  //cameraCommandOutput = n.advertise<geometry_msgs::QuaternionStamped>("camera/command", 10, false);

  ros::param::param("~axis_speed", simple_joy_control::axis_speed, 0);
  ros::param::param("~axis_steer", simple_joy_control::axis_steer, 1);
  ros::param::param("~axis_speed_dead_zone", simple_joy_control::axis_speed_dead_zone, 0.1);
  ros::param::param("~axis_steer_dead_zone", simple_joy_control::axis_steer_dead_zone, 0.1);

  //ros::param::param("~speed", Thumper::speed, 1.0);
  //ros::param::param("~speedTurn", Thumper::speedTurn, 1.0);
//  ros::param::param("~axis_steer", Monstertruck::axis_steer, 0);
//  ros::param::param("~steerAngle", Monstertruck::steerAngle, 30.0);
//  ros::param::param("~button_crab", Monstertruck::button_crab, 0);
//  ros::param::param("~button_slow", Monstertruck::button_slow, 0);
//  ros::param::param("~slowFactor", Monstertruck::slowFactor, 0.2);

//  ros::param::param("~axis_cameraPan", Monstertruck::axis_cameraPan, 0);
//  ros::param::param("~axis_cameraTilt", Monstertruck::axis_cameraTilt, 0);
//  ros::param::param("~button_cameraReset", Monstertruck::button_cameraReset, 0);
//  ros::param::param<std::string>("~cameraMode", Monstertruck::cameraMode, "stabilized");
//  ros::param::param("~cameraSpeed", Monstertruck::cameraSpeed, 30.0);
//  ros::param::param("~cameraMaxPan", Monstertruck::cameraMaxPan, 120.0);
//  ros::param::param("~cameraMaxTiltDown", Monstertruck::cameraMaxTiltDown, 30.0);
//  ros::param::param("~cameraMaxTiltUp", Monstertruck::cameraMaxTiltUp, 30.0);

  ros::Rate rate(20.0);
  while(ros::ok()) {
    //moveCamera(rate.expectedCycleTime().toSec());
    motionCommandOutput.publish(motionCommand);
    //twistCommandOutput.publish(twistCommand);
    //cameraCommandOutput.publish(cameraCommand);
    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}

