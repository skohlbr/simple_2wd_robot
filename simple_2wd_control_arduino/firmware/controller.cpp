

//#define USE_USBCON 0

#include <ros.h>
#include <simple_arduino_control_msgs/DiffDriveCommand.h>


#include <Arduino.h>
int led = 13;
bool led_on = false;


//#include <AFMotor.h>
//AF_DCMotor left_motor(2, MOTOR12_64KHZ);
//AF_DCMotor right_motor(1, MOTOR12_64KHZ);

#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100

/*  VNH2SP30 pin definitions
 xxx[0] controls '1' outputs
 xxx[1] controls '2' outputs */
int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int cspin[2] = {2, 3}; // CS: Current sense ANALOG input
int enpin[2] = {0, 1}; // EN: Status of switches output (Analog pin)



ros::NodeHandle nh;

simple_arduino_control_msgs::DiffDriveCommand cmd_debug;
ros::Publisher cmd_debug_pub("cmd_debug", &cmd_debug);

unsigned long last_cmd_time;



/* motorGo() will set a motor going in a specific direction
 the motor will continue going in that direction, at that speed
 until told to do otherwise.

 motor: this should be either 0 or 1, will selet which of the two
 motors to be controlled

 direct: Should be between 0 and 3, with the following result
 0: Brake to VCC
 1: Clockwise
 2: CounterClockwise
 3: Brake to GND

 pwm: should be a value between ? and 1023, higher the number, the faster
 it'll go
 */
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
  }
}

void motorOff(int motor)
{
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}



void command_cb( const simple_arduino_control_msgs::DiffDriveCommand& cmd_msg){

  cmd_debug = cmd_msg;


  if (cmd_msg.left_motor_cmd == 0){
    motorOff(0);
  }else if (cmd_msg.left_motor_cmd > 0){
    motorGo(0, CW, cmd_msg.left_motor_cmd * 2);
  }else{
    motorGo(0, CCW, -cmd_msg.left_motor_cmd * 2);
  }

  if (cmd_msg.right_motor_cmd == 0){
    motorOff(1);
  }else if (cmd_msg.right_motor_cmd > 0){
    motorGo(1, CW, cmd_msg.right_motor_cmd * 2);
  }else{
    motorGo(1, CCW, -cmd_msg.right_motor_cmd * 2);
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

  // Initialize digital pins as outputs
  for (int i=0; i<2; i++)
  {
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
  }
  // Initialize braked
  for (int i=0; i<2; i++)
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }

  nh.initNode();

  nh.advertise(cmd_debug_pub);

  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  //cmd_debug_pub.publish(&cmd_debug);
  delay(10);
}
