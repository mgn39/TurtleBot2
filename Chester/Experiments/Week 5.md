
### September 23th, 2024

**Objective:** Path Planing

**Experiment:** Try to do path planning.

**Problem:** I cannot bringup after ran `sudo apt autoremove`

**Fix:** Install some packages
- Install kdl_conversions package
	- `sudo apt-get install ros-noetic-kdl-conversions -y`
- Install camera_info_manager package
	- `sudo apt-get install ros-noetic-camera-info-manager -y`
- Install cmake_modules package
	- `sudo apt-get install ros-noetic-cmake-modules -y`
- Install visualization_msgs package
	- `sudo apt-get install ros-noetic-visualization-msgs -y`
- Install angles package
	- `sudo apt-get install ros-noetic-angles -y`


**Result:** Can work again.


### September 24th, 2024

**Objective:** Path Planing (Configuration)

**Experiment:** Configure the move_base file by setting up.
- Create the global_costmap
	- `cd kobuki_ws/src/turtlebot_apps/turtlebot_navigation/config`
	- `nano global_costmap_params.yaml`
```
global_costmap:
  global_frame: map
  robot_base_frame: base_link
  update_frequency: 5.0
  publish_frequency: 2.0
  static_map: true
  rolling_window: false
  width: 10.0
  height: 10.0
  resolution: 0.05
  transform_tolerance: 0.3

  plugins:
    - {name: inflation_layer, type: "costmap_2d::InflationLayer"}
    - {name: obstacle_layer, type: "costmap_2d::ObstacleLayer"}
```
- Create the local_costmap
	- `nano local_costmap_params.yaml`
```
local_costmap:
  global_frame: odom
  robot_base_frame: base_link
  update_frequency: 5.0
  publish_frequency: 2.0
  rolling_window: true
  width: 2.0
  height: 2.0
  resolution: 0.05
  transform_tolerance: 0.3

  plugins:
    - {name: obstacle_layer, type: "costmap_2d::ObstacleLayer"}
    - {name: inflation_layer, type: "costmap_2d::InflationLayer"}
```
- Create the costmap_common
	- `nano costmap_common_params.yaml`
```
obstacle_range: 2.5
raytrace_range: 3.0
footprint: [[-0.15, -0.15], [-0.15, 0.15], [0.15, 0.15], [0.15, -0.15]]
robot_radius: 0.2

inflation_radius: 0.55

observation_sources: laser_scan
laser_scan: {
  sensor_frame: laser_frame,
  data_type: LaserScan,
  topic: scan,
  marking: true,
  clearing: true
}
```
- Create move_base file
	- `cd kobuki_ws/src/turtlebot_apps/turtlebot_navigation/launch`
	- `nano move_base.launch`
```
<launch>
  <!-- Map server (optional if RTAB-Map is running) -->
  <!-- <node name="map_server" pkg="map_server" type="map_server" args="$(find turtlebot_navigation)/maps/map.yaml" /> -->

  <!-- Move Base -->
  <node name="move_base" pkg="move_base" type="move_base" respawn="false" output="screen">
    <rosparam file="$(find turtlebot_navigation)/config/global_costmap_params.yaml" command="load" ns="global_costmap" />
    <rosparam file="$(find turtlebot_navigation)/config/local_costmap_params.yaml" command="load" ns="local_costmap" />
    <rosparam file="$(find turtlebot_navigation)/config/costmap_common_params.yaml" command="load" />
  </node>

  <!-- RViz for Visualization -->
  <node name="rviz" pkg="rviz" type="rviz" args="-d $(find turtlebot_navigation)/launch/move_base.rviz" />
</launch>
```
- After create all files
	- `cd ~/kobuki_ws`
	- `catkin_make`
	- `source devel/setup.bash`
- To launch the file
	- `roslaunch turtlebot_navigation move_base.launch`

**Result:** Still got 2 warnings
`[ WARN] [1727194190.269365876]: The robot's start position is off the global costmap. Planning will always fail, are you sure the robot has been properly localized?`

`[ WARN] [1727201530.070138681]: Unable to get starting pose of robot, unable to create global plan`


### September 25th, 2024

**Objective:** Path Planning

**Experiment:** Trying on new command for rtabmap
`roslaunch rtabmap_ros rtabmap.launch rtabmap_args:="--delete_db_on_start" depth_topic:=/camera/depth_registered/image_raw rgb_topic:=/camera/rgb/image_raw camera_info_topic:=/camera/rgb/camera_info`

Trying on new move_base file (include in the turtlebot_navigation = move_base_laser.launch)
`roslaunch turtlebot_navigation move_base_laser.launch` still got same error "The robot's start position is off the global costmap. Planning will always fail"

Use this `rosrun map_server map_saver -f /kobuki_ws/src/hfi_map` still cannot save the map either in the pink computer or ssh to Raspberry Pi.

The robot might not be publishing the correct transform (TFs) between frames. Try run this command `rosrun tf view_frames` and got some error. After some configuration nothing different. And use `rostopic echo /tf` to check they are publish or not -> can ping.

**Result:** All failed. But in rtabmap command still got some warning but less.


### September 26th, 2024

**Objective:** Path Planning

**Experiment:** Config the move_base and global_costmap file.
- global_costmap
	- Change from `update_frequency: 5.0` into `update_frequency: 1`
	- Change from `publish_frequency: 2.0` into `publish_frequency: 1`
	- Add `- {name: static_layer, type: "rtabmap_ros::StaticLayer"}` under plugins:
- move_base
```
  <arg name="odom_frame_id"   default="t265_odom_frame"/>
  <arg name="base_frame_id"   default="robot_center"/>
  <arg name="global_frame_id" default="map"/>
  <arg name="odom_topic" default="t265/odom/sample" />

  <arg name="laser_topic" default="scan" />

<!--Added statement-->
  <remap from="map" to="/rtabmap/grid_map"/>
    
    
      <node pkg="move_base" type="move_base" respawn="false" name="move_base" output="screen">
        <rosparam file="$(find realsense_controls)/config/costmap_common_params.yaml" command="load" ns="global_costmap" />
        <rosparam file="$(find realsense_controls)/config/costmap_common_params.yaml" command="load" ns="local_costmap" />   
        <rosparam file="$(find realsense_controls)/config/local_costmap_params_3d.yaml" command="load" />   
        <rosparam file="$(find realsense_controls)/config/global_costmap_params.yaml" command="load" />
        <rosparam file="$(find realsense_controls)/config/base_local_planner_params.yaml" command="load" />

        <!-- reset frame_id parameters using user input data -->
        <param name="global_costmap/global_frame" value="$(arg global_frame_id)"/>
        <param name="global_costmap/robot_base_frame" value="$(arg base_frame_id)"/>
        <param name="local_costmap/global_frame" value="$(arg odom_frame_id)"/>
        <param name="local_costmap/robot_base_frame" value="$(arg base_frame_id)"/>
        <param name="DWAPlannerROS/global_frame_id" value="$(arg odom_frame_id)"/>
       
       
        <remap from="odom" to="$(arg odom_topic)"/>
        <remap from="scan" to="$(arg laser_topic)"/>
      </node>
    </launch>
```

**Result:** Not help. I cannot launch the move_base file. But still can launch move_base_laser file (in turtlebot_navigation).


### September 27th, 2024

**Objective:** Path Planning

**Experiment:** 