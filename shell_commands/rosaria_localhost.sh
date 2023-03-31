#!/bin/bash
cd $HOME
cd catkin_ws
export ROS_HOSTNAME=localhost
export ROS_MASTER_URI=http://localhost:11311
. devel/setup.bash
gnome-terminal -- rosrun rosaria RosAria 
