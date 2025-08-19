
### November 22nd, 2024

**Objective:** Fix TF of LiDAR

**Experiment:** Check the rqt of the systems and it turn out that parent node (base_link) cannot find their child node (base_laser). By fixing this by use this command `rosrun tf2_ros static_transform_publisher 0 0 0 0 0 0 1 base_link base_laser` and it fixed!

But we don't want to launch this every single time so I put this into rplidar_a1 file
- `cd kobuki_ws/src/rplidar_ros/launch/`
- `nano rplidar_a1.launch`
```
<launch>
  <!-- RPLIDAR Node -->
  <node name="rplidarNode" pkg="rplidar_ros" type="rplidarNode" output="screen">
    <param name="serial_port" type="string" value="/dev/ttyUSB0"/>
    <param name="serial_baudrate" type="int" value="115200"/>
    <param name="frame_id" type="string" value="base_laser"/>
    <param name="inverted" type="bool" value="true"/>
    <param name="angle_compensate" type="bool" value="true"/>
  </node>

  <!-- Static Transform Publisher -->
  <node name="static_transform_publisher" pkg="tf2_ros" type="static_transform_publisher" output="screen" args="0 0 0 0 0 0 1 base_link base_laser"/>

</launch>
```