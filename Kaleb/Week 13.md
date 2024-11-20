## <u>11/20/24</u>

### The LiDAR Sensor
Created `gmapping_demo2.launch` in `kobuki_ws/src/turtlebot_apps/turtlebot_navigation/launch/`: same process from [[Chester/Experiments/Week 12|Chester]]
```roslaunch
<launch>
  <!-- RPLIDAR node should be launched separately, as you are already doing -->

  <!-- Gmapping -->
  <include file="$(find turtlebot_navigation)/launch/includes/gmapping/gmapping.launch.xml">
    <arg name="scan_topic" value="/scan" /> <!-- Use RPLIDAR scan topic -->
  </include>

  <!-- Move base -->
  <include file="$(find turtlebot_navigation)/launch/includes/move_base.launch.xml"/>

</launch>
```

Now, my `turtleboot` file (all-in-one launch) has been updated to not use the Kinect camera:
```bash
#!/bin/bash

source .bashrc

# 1: turtlebot
roslaunch turtlebot_bringup minimal.launch &
PID_TURTLE=$!

# wait for bringup to complete
sleep 5

# 6: rplidar activation (only works on Pi 5/6)
roslaunch rplidar_ros rplidar_a1.launch &
PID_LIDAR=$!

# 4: rplidar mapping (only works on Pi 5/6)
roslaunch turtlebot_navigation gmapping_demo2.launch &
PID_MAP=$!

# _: doorbell testing (only works on Pi 5 --> will be moved to ESP32)
# sudo -python3 ~/kobuki_ws/src/rpi-rf_receive+launch.py &
# DOORBELL_PID=$!

# On the main desktop, run rviz
```
- Note: Run `rosnode kill -a` to terminate all 3 nodes

We plan to map and autonomously drive the Turtlebot using the LiDAR sensor, without the help of the Kinect camera. In doing so, we reduce the computational overhead required and fix the issue in which the camera has trouble distinguishing between glass and valid space.

In rviz:
- Add `RobotModel` (Turtlebot)
- Add `Laserscan`, set the topic if necessary
- Add `Map`, set to the map topic

The LiDAR sensor builds a limited, initial map but doesn't create a map of the actual space