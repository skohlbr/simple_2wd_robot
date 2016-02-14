# simple_2wd_robot
ROS packages related to control of a simple 2WD Arduino robot
![Simple 2WD robot image](https://lh3.googleusercontent.com/54K4BoiJXCHz7SdUnQgj7-VRpP4BZP9tUA9VVgRpytdwFHVAY9o6GYjZDaAGOLHaBq7eirQ9xLdIDKsIi5RniRJygUUAYIkgRi6huq0mYnVe1qnNmICjFPFRVWFn2qB-lEvH1m6GCcad0wEHgvOOkt7zaBy7D7pKduia6f2-akz6dy8lhPRv9uLNrm2VHCJQO1SZE00Auj0pbKmorJDnxzL4g_ZSOXuFcOrr4wzOuhZCeytCWYoZZkkvNj1lsZnd9BiqVvKXju0Gd__RjBI18uFu5ZmXGwUdoFT-I5kO6aPIwhqsh4hxr6hIoXIDjKepM8jWVYroC3fryRjXW5kyUNb19ZAxNYg3ZtKqdBe5uVYGB0jX6y-OrVJqWxf_qMC3RWDuyu31czNs_fCwGV483Fy1obFHbZFqD4uK0F685ezNlSKnWjgZ9ksj6T6xO-f8CoZYNDW1tWGWD-VS8WrduEe7-UmYwdtit98HZx-N32NMA5fnGacz79Ja51lOr9hnGhBTXDe0EqW30CMXQqdLgpHZsx846iMWBxTa_ii6h0ByBj10oaQh7c81IIICDJqMv7ro-g=w2690-h1990-no)

The following ROS packages are part of this repo:

* [simple_2wd_bringup](https://github.com/skohlbr/simple_2wd_robot/tree/master/simple_2wd_bringup) provides a launch file for starting up all onboard systems of the robot

* [simple_2wd_control_arduino](https://github.com/skohlbr/simple_2wd_robot/tree/master/simple_2wd_control_arduino) contains the controller that has to be flashed to the Arduino. From the root of your workspace use the following command for flashing:
```
rosrun simple_2wd_control_arduino upload.sh
```
* [simple_arduino_control](https://github.com/skohlbr/simple_2wd_robot/tree/master/simple_arduino_control) contains a node for translating standard ROS control commands (joy and cmd_vel) to commands for the Arduino.

* [simple_arduino_control_msgs](https://github.com/skohlbr/simple_2wd_robot/tree/master/simple_arduino_control_msgs) contains lightweight custom messages for comunicating between ROS and the Arduino.
