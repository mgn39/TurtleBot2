
### September 12th, 2024

Stream data to another computer. Can try to use ssh into it. But the thing is I’ve tried via Mac but doesn’t work. I will try on another computer whether the one that you fixed or the one beside the Baxter robot.

IP Address of the pink computer
	192.168.0.41


### September 16th, 2024

To do ssh don't forget to check the WiFi is that the same one or not.


### October 17th, 2024

Normally I use `nano` to config the file in the terminal but if you wanna see the text in the file you can use `cat` instead.
- Example
	- `cat file_name`
	- `cat rpi-rf_receive`


### October 21st, 2024

Efficient command to delete/uninstall package `rm -rf package_name`


### October 28th, 2024

Remote host identification has changed fix by `ssh-keygen -R IP Address` 
For example: `ssh-keygen -R 192.168.0.190`


### November 11th, 2024

When you launch the file then facing usage over 1 GB. Use `rosclean purge`


### November 12th, 2024

Instead of `ssh`-ing and opening 5 terminals, `ssh` once into the Pi, then place all commands into a file:
```bash
#!/bin/bash

source .bashrc

# 1: turtlebot
roslaunch turtlebot_bringup minimal.launch &
PID_1=$!

# wait for bringup to complete
sleep 5

# 2: freenect
roslaunch freenect_launch freenect.launch depth_registration:=true &
FREENECT_PID=$!

# 3: rtabmap
roslaunch rtabmap_ros rtabmap.launch rtabmap_args:="--delete_db_on_start" depth_topic:=/camera/depth_registered/image_raw rgb_topic:=/camera/rgb/image_raw camera_info_topic:=/camera/rgb/camera_info
& RTAB_PID=$!

# 4: map (only works on Pi 5)
# roslaunch turtlebot_navigation amcl_demo.launch map_file:=/home/SaPHaRI/kobuki_ws/src/map/4thmap.yaml
# & MAP_PID=$!

# 5: doorbell (only works on Pi 5)
# sudo -python3 ~/kobuki_ws/src/rpi-rf_receive+launch.py
# & DOORBELL_PID=$!

# 6: rplidar (only works on Pi 6)
roslaunch rplidar_ros rplidar_a1.launch
& LIDAR_PID=$!
```