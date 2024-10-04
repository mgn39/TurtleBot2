
### September 30th, 2024

**Objective:** Save the map for path planning

**Experiment:** I save the configuration first (I don't know if it's related or not).
And I try many attempts by using the command `rosrun map_sever map_saver -f /path to map/map name`. So, `rosrun map_server map_saver -f /home/SaPHaRI/kobuki_ws/src/1stmap` this map will be saved under kobuki_ws/src folder. It takes more than 30 minutes.

I changed to this command instead `rosrun map_server map_saver map:=/rtabmap/grid_prob_map -f /home/SaPHaRI/kobuki_ws/src/1stmap`. After I change the command, I can save the map within **second!**.

Need to **ensure correct topic:** If map_saver doesn't automatically save from the correct topic, you can specific the topic manually. Since you're using RTAB-MAP and your map topic is /rtabmap/grid_prob_map and in Global Options is /map so the topic does not match.

**Result:** Be able to save the map now
![[Successfully save the map.png]]
![[Open saved map.png]]

**Research:** LiDAR Sensor
- Hokuyo UTM-30LX
	- High performance and Lightweight
	- Range up to **30 meters**
	- Well with TurtleBots and ROS Noetic
- RPLIDAR A2
	- More budget-friendly
	- With 360-degree view and a range of **6-12 meters** 
	- Well with TurtleBots and ROS
- YDLIDAR X4
	- Affordable and compact option
	- Range up to **10 meters**
	- Well with ROS and Raspberry Pi, making suitable for indoor navigation
- Slamtec RPLIDAR S1
	- Ideal for larger spaces, range up to **40 meters**
	- Well with ROS for mapping and path planning

LiDAR Sensor (~100$)
- YDLIDAR Tmini
	- Price under 100$
	- Range up to **8 meters**
	- Supported by ROS. Good entry for simple indoor navigation tasks
- RPLIDAR A1M8 (Recommend)
	- Price ~100$
	- Range up to **12 meters**
	- Provides 360-degree scanning
	- Well with ROS Noetic and TurtleBot 2

Charging Station for TurtleBot 2
- Battery life of TurtleBot **~2-3 hours**, battery life can vary based of factors (sensors)
- If we can reach our goal, it will be more helpful if we have a charging station


### October 1st, 2024

**Objective:** Launch the amcl and move_base files to do path planning.

**Experiment:** After I can save the map from yesterday. I try to configuration of the amcl file.
This is what I edited by now.
```
<launch>
  <!-- 3D sensor -->
  <arg name="3d_sensor" default="freenect"/>  <!-- r200, kinect, asus_xtion_pro -->
  <include file="/home/SaPHaRI/kobuki_ws/src/freenect_stack/freenect_launch/launch/freenect.launch">
    <arg name="rgb_processing" value="false" />
    <arg name="depth_registration" value="false" />
    <arg name="depth_processing" value="false" />
    <!-- We must specify an absolute topic name because if not it will be prefixed by "$(arg camera)".
         Probably is a bug in the nodelet manager: https://github.com/ros/nodelet_core/issues/7 --> 
  </include>

  <!-- Map server -->
  <arg name="map_file" default="$(env TURTLEBOT_MAP_FILE)"/>
  <node name="map_server" pkg="map_server" type="map_server" args="$(arg map_file)" />

  <!-- AMCL -->
  <arg name="custom_amcl_launch_file" default="$(find turtlebot_navigation)/launch/includes/amcl/kinect_amcl.launch.xml"/>
  <arg name="initial_pose_x" default="0.0"/> <!-- Use 17.0 for willow's map in simulation -->
  <arg name="initial_pose_y" default="0.0"/> <!-- Use 17.0 for willow's map in simulation -->
  <arg name="initial_pose_a" default="0.0"/>
  <include file="$(arg custom_amcl_launch_file)">
    <arg name="initial_pose_x" value="$(arg initial_pose_x)"/>
    <arg name="initial_pose_y" value="$(arg initial_pose_y)"/>
    <arg name="initial_pose_a" value="$(arg initial_pose_a)"/>
  </include>

  <!-- Move base -->
  <arg name="custom_param_file" default="$(find turtlebot_navigation)/param/kinect_costmap_params.yaml"/>
  <include file="$(find turtlebot_navigation)/launch/includes/move_base.launch.xml">
    <arg name="custom_param_file" value="$(arg custom_param_file)"/>
  </include>

</launch>
```

You can find this file by `cd kobuki_ws/src/turtlebot_apps/turtlebot_navigation/launch` amd then `nano amcl_demo.launch`

**Result:** I got big error after I launched the amcl file, it kill freenect.

**Notes:** Most errors from amcl file are in the original file setting the path different from yours. Thus, you need to set a new path to make sure that when you launch the amcl file, the file can indicate another relative file correctly.


### October 3rd, 2024

**Objective:** Fix the errors.

**Problem:** After I launch the amcl file it will kill the freenect launch file.

**Solution:** I found out that I lunching the freenect twice. One is in the freenect launch and another one is in the amcl file.

To avoid launching freenect twice I will delete the freenct section in amcl file.
```
<launch>
  <!-- Map server -->
  <arg name="map_file" default="$(env TURTLEBOT_MAP_FILE)"/>
  <node name="map_server" pkg="map_server" type="map_server" args="$(arg map_file)" />

  <!-- AMCL -->
  <arg name="custom_amcl_launch_file" default="$(find turtlebot_navigation)/launch/includes/amcl/kinect_amcl.launch.xml"/>
  <arg name="initial_pose_x" default="0.0"/> <!-- Use 17.0 for willow's map in simulation -->
  <arg name="initial_pose_y" default="0.0"/> <!-- Use 17.0 for willow's map in simulation -->
  <arg name="initial_pose_a" default="0.0"/>
  <include file="$(arg custom_amcl_launch_file)">
    <arg name="initial_pose_x" value="$(arg initial_pose_x)"/>
    <arg name="initial_pose_y" value="$(arg initial_pose_y)"/>
    <arg name="initial_pose_a" value="$(arg initial_pose_a)"/>
  </include>

  <!-- Move base -->
  <arg name="custom_param_file" default="$(find turtlebot_navigation)/param/kinect_costmap_params.yaml"/>
  <include file="$(find turtlebot_navigation)/launch/includes/move_base.launch.xml">
    <arg name="custom_param_file" value="$(arg custom_param_file)"/>
  </include>

</launch>
```

After I configured the amcl file, I found important warning that make me cannot set the initial pose of the robot is **No laser scan received** but when I run `rostopiclist`, the /scan is exist. Then I run `rostopic echo /scan`. So, if **don't see any data**, it means the topic exists but isn't publishing scan messages. And Yes, I did not see any data lol.

Kinect: It doesn't produce a LaserScan directly; instead, it produces a point cloud. So, need to convert the point cloud to LaserScan.

Install pointcloud_to_laserscan
- `sudo apt-get install ros-noetic-pointcloud-to-laserscan -y`

Modify the amcl file.
```
<launch>
<!-- Convert PointCloud to LaserScan -->
  <node pkg="pointcloud_to_laserscan" type="pointcloud_to_laserscan_node" name="pointcloud_to_laserscan">
    <!-- Remap input from the Kinect's point cloud -->
    <remap from="cloud_in" to="/camera/depth/points"/>
    <param name="scan_time" value="0.033"/>  <!-- Adjust based on desired scan frequency -->
    <param name="range_min" value="0.5"/>    <!-- Minimum range for laser scan -->
    <param name="range_max" value="5.0"/>    <!-- Maximum range (based on Kinect's range) -->
    <param name="use_inf" value="true"/>     <!-- Use infinity for out-of-range values -->
    <param name="angle_min" value="-1.57"/>  <!-- Start angle for scan (in radians) -->
    <param name="angle_max" value="1.57"/>   <!-- End angle for scan (in radians) -->
    <param name="target_frame" value="base_link"/>  <!-- Target frame for the scan -->
  </node>

  <!-- Map server -->
  <arg name="map_file" default="$(env TURTLEBOT_MAP_FILE)"/>
  <node name="map_server" pkg="map_server" type="map_server" args="$(arg map_file)" />

  <!-- AMCL -->
  <arg name="custom_amcl_launch_file" default="$(find turtlebot_navigation)/launch/includes/amcl/kinect_amcl.launch.xml"/>
  <arg name="initial_pose_x" default="0.0"/> <!-- Use 17.0 for willow's map in simulation -->
  <arg name="initial_pose_y" default="0.0"/> <!-- Use 17.0 for willow's map in simulation -->
  <arg name="initial_pose_a" default="0.0"/>
  <include file="$(arg custom_amcl_launch_file)">
    <arg name="initial_pose_x" value="$(arg initial_pose_x)"/>
    <arg name="initial_pose_y" value="$(arg initial_pose_y)"/>
    <arg name="initial_pose_a" value="$(arg initial_pose_a)"/>
  </include>
  
  <!-- Move base -->
  <arg name="custom_param_file" default="$(find turtlebot_navigation)/param/kinect_costmap_params.yaml"/>
  <include file="$(find turtlebot_navigation)/launch/includes/move_base.launch.xml">
    <arg name="custom_param_file" value="$(arg custom_param_file)"/>
  </include>

</launch>
```

But I still get the same warning **No laser scan received**.

I also check the frame transformation (TF) is correctly set up by running.
- `rosrun tf view_frames`

I get error an incompatibility in Python versions, where the data being passed is in bytes format but is expected to be a string. This issue is related to the TF package in ROS Noetic.

To fix the error
- `sudo nano /opt/ros/noetic/lib/tf/view_frames`
- Add `.decode('utf.8')` after `m = r.search(vstr)` 
- Should be like this `m = r.search(vstr.decode('utf.8'))`
Reference: [TypeError: string pattern on a bytes-like object](https://github.com/ros/geometry/pull/193)

**Problem:** No laser scan received

**Experiment:** I add this `<arg name="scan_topic" default="/scan"/>`  into amcl file.
This is my amcl file by now.
```
<launch>
  <!-- Convert PointCloud to LaserScan -->
  <node pkg="pointcloud_to_laserscan" type="pointcloud_to_laserscan_node" name="pointcloud_to_laserscan">
    <!-- Remap input from the Kinect's point cloud -->
    <remap from="cloud_in" to="/camera/depth/points"/>
    <param name="scan_time" value="0.033"/>  
    <param name="range_min" value="0.5"/>    
    <param name="range_max" value="5.0"/>    
    <param name="use_inf" value="true"/>     
    <param name="angle_min" value="-1.57"/>  
    <param name="angle_max" value="1.57"/>   
    <param name="target_frame" value="base_link"/>  
  </node>

  <!-- Map server -->
  <arg name="map_file" default="$(env TURTLEBOT_MAP_FILE)"/>
  <node name="map_server" pkg="map_server" type="map_server" args="$(arg map_file)" />

  <!-- AMCL -->
  <arg name="custom_amcl_launch_file" default="$(find turtlebot_navigation)/launch/includes/amcl/kinect_amcl.launch.xml"/>
  <arg name="initial_pose_x" default="0.0"/> 
  <arg name="initial_pose_y" default="0.0"/> 
  <arg name="initial_pose_a" default="0.0"/>
  <include file="$(arg custom_amcl_launch_file)">
    <arg name="initial_pose_x" value="$(arg initial_pose_x)"/>
    <arg name="initial_pose_y" value="$(arg initial_pose_y)"/>
    <arg name="initial_pose_a" value="$(arg initial_pose_a)"/>
    
    <!-- Add scan topic remapping here -->
    <arg name="scan_topic" default="/scan"/>
  </include>
  
  <!-- Move base -->
  <arg name="custom_param_file" default="$(find turtlebot_navigation)/param/kinect_costmap_params.yaml"/>
  <include file="$(find turtlebot_navigation)/launch/includes/move_base.launch.xml">
    <arg name="custom_param_file" value="$(arg custom_param_file)"/>
  </include>

</launch>
```

**Result:**
WARN 1727995162.007876729: No laser scan received (and thus no pose updates have been published) for 1727995162.007561 seconds.  Verify that data is being published on the /scan topic


### October 4th, 2024

**Objective:** Fix the error (No laser scan).

**Assumption:** It is suspected that I did not add PointCloud2 when I mapped the lab area and another suspect is after I added the PointCloud2 I chose `/rtabmap/cloud_map` instead of `/camera/depth/points`

**Experiment:** I config the amcl file by put `/rtabmap/cloud_map`