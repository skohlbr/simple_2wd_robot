#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/QuaternionStamped.h>

#include <simple_arduino_control_msgs/DiffDriveCommand.h>

namespace simple_joy_control {

  ros::Subscriber joyInput;
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



  void joyCallback(const sensor_msgs::JoyConstPtr joystick) {

    float speed = joystick->axes[axis_speed];

    if (std::abs(speed) < axis_speed_dead_zone){
     speed = 0.0f;
    }

    float angRate = joystick->axes[axis_steer];

    if(std::abs(angRate) < axis_steer_dead_zone){
      angRate = 0.0f;
    }

    //motionCommand.angularRate = -angRateSpeed;

    //twistCommand.linear.x = speed;
    //twistCommand.angular.z = angRateSpeed;
    
    float mag_left = speed + angRate;
    float mag_right = speed - angRate;
    
    float mag_max = std::max(mag_left, mag_right);
    
    if (mag_max > 1.0f){
      mag_left = mag_left / mag_max;
      mag_right = mag_right / mag_max;
    }
    
    motionCommand.left_motor_cmd = static_cast<int8_t>(mag_left * 127.0);
    motionCommand.right_motor_cmd = static_cast<int8_t>(mag_right * 127.0);
    
           
    //pwm_left = round(self._Max_PWM*mag_left)                      
    //pwm_right = round(self._Max_PWM*mag_right)


    /*
    if (axis_speed > 0 && (size_t) axis_speed <= joystick->axes.size()) {
      float value = joystick->axes[axis_speed-1];
      if (value >= 0.0)
        motionCommand.speed = value * speedForward;
      else
        motionCommand.speed = value * speedBackward;

      if (button_slow > 0 && (size_t) button_slow <= joystick->buttons.size() && joystick->buttons[button_slow-1]) {
        motionCommand.speed *= slowFactor;
      }
    }

    if (axis_steer > 0 && (size_t) axis_steer <= joystick->axes.size()) {
      motionCommand.steerAngleFront = joystick->axes[axis_steer-1] * steerAngle * M_PI/180.0;
      motionCommand.steerAngleRear  = motionCommand.steerAngleFront;

      if (button_crab > 0 && (size_t) button_crab <= joystick->buttons.size()) {
        if (joystick->buttons[button_crab-1]) motionCommand.steerAngleRear = -motionCommand.steerAngleRear;
      }
    }

    motionCommandOutput.publish(motionCommand);

    if (axis_cameraPan > 0 && (size_t) axis_cameraPan <= joystick->axes.size()) {
      cameraPanSpeed = joystick->axes[axis_cameraPan-1] * cameraSpeed * M_PI/180.0;
    }
    if (axis_cameraTilt > 0 && (size_t) axis_cameraTilt <= joystick->axes.size()) {
      cameraTiltSpeed = joystick->axes[axis_cameraTilt-1] * cameraSpeed * M_PI/180.0;
    }
    if (button_cameraReset > 0 && (size_t) button_cameraReset <= joystick->buttons.size() && joystick->buttons[button_cameraReset-1]) {
      cameraPan = 0;
      cameraTilt = 0;
    }
    */
  }
};



using namespace simple_joy_control;

int main(int argc, char **argv) {
  ros::init(argc, argv, ROS_PACKAGE_NAME);
  ros::NodeHandle n;

  joyInput = n.subscribe("joy", 10, joyCallback);
  motionCommandOutput = n.advertise<simple_arduino_control_msgs::DiffDriveCommand>("/move_command_raw", 10, false);

  twistCommandOutput = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10, false);
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

