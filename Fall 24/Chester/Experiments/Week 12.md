
### November 15th, 2024

**Objective:** Mapping with only LiDAR sensor.

**Experiment:** I update the gmapping file because I will launch the LiDAR separately. (I create a new file instead of edit the original file just in case).
- `cd kobuki_ws/src/turtlebot_apps/turtlebot_navigation/launch`
- `nano gmapping_demo2.launch`
```
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

To test:
- Terminal  1 | ssh: `roslaunch turtlebot_bringup minimal.launch`
- Terminal 2 | ssh: `roslaunch rplidar_ros rplidar_a1.launch`
- Terminal 3 | ssh : `roslaunch turtlebot_navigation gmapping_demo2.launch`
- Terminal 4: `rviz`

**Result:** Fail! cannot map as expected!!!