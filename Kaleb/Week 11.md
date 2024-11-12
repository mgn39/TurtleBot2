## <u>11/7/24</u>

### Moving Object Detection (Day 4)
- On `ssh -Y SaPHaRI@192.168.0.213` for the Pi
	- `ROS_MASTER_IP` should be the Desktop's (192.168.0.41)
	- Ran `minimal.launch` and the LiDAR sensor's plugged in
- On the desktop
	- `roscore`
- In another `ssh -Y ...` for the Pi...
	- `roslaunch datmo example.launch bag:=overtakes`


## <u>11/12/24</u>

### Moving Object Detection (Day 5)
Created bash to efficiently boot Turtlebot, called `turtleboot`
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
