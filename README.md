# simple_2wd_robot
ROS packages related to control of a simple 2WD Arduino robot
![Simple 2WD robot image](https://lh3.googleusercontent.com/BvtUXjKdmP9ZFf6rqAhnwhfMwPTbDkJF1-_1UoZdOzmAnBbqAbKIojLRd94mfqM9Apja4ILEiv5511mXcOXMYy1exIGwXnCGWrQC56MANwDkPASTiDOzjxTASYPqsTu96uW6_r52ElSmg80_XwtMEppFf7apCHLCIlV6IHtOpqp2V0NRRpF3JxqHAIcmJZpbp7fpXaCYM3GiqfQQx1RgM_gEfcz1YqQsqx9ZEpXmE2utquOI5TpCgV_oFG1pvfePka-VTVH-xU5fprPdxbh16rZSLhbeTf7dwVQ_XvJOzqAe63UgVBSbNzhau_jA-HR0y_kOz8sGQtErl8XCPU5VWC1Tdq6xqRCq68AL9gUUOQvejOofBu7yG3hI3eEartdgmD9mPqbGuKAtUBMNdz-3ZqZob7u--T4oMAeKb_CuLPf_kkaedJCWja-Iqwq6sqfRLEbsrMVeVfHTSltHcYuC8OcghZuDsUZMudBwsCjbUaVgFp_5JAbuF9-05YsnaomoRrUCVTndofj0D2k0H75-YNHd2KVouKDijAwM4pN7ldLtlPkEfmUDUMLB49mxwFIZQlZOpw=w2690-h1990-no)

The following ROS packages are part of this repo:

* [simple_2wd_bringup](https://github.com/skohlbr/simple_2wd_robot/tree/master/simple_2wd_bringup) provides a launch file for starting up all onboard systems of the robot

* [simple_2wd_control_arduino](https://github.com/skohlbr/simple_2wd_robot/tree/master/simple_2wd_control_arduino) contains the controller that has to be flashed to the Arduino. From the root of your workspace use the following command for flashing:
```
rosrun simple_2wd_control_arduino upload.sh
```
* [simple_arduino_control](https://github.com/skohlbr/simple_2wd_robot/tree/master/simple_arduino_control) contains a node for translating standard ROS control commands (joy and cmd_vel) to commands for the Arduino.

* [simple_arduino_control_msgs](https://github.com/skohlbr/simple_2wd_robot/tree/master/simple_arduino_control_msgs) contains lightweight custom messages for comunicating between ROS and the Arduino.
