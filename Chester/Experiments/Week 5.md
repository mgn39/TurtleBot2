
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