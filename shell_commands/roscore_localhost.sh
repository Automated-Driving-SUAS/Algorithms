#!/bin/bash
cd $HOME
export ROS_HOSTNAME=localhost
export ROS_MASTER_URI=http://localhost:11311
gnome-terminal -- roscore 
