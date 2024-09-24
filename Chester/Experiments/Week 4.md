
### September 16th, 2024

**Objective:** Try to do path planning via pink computer. 

**Problem:** Cannot open Rviz.

**Experiment:** ssh from pink computer into Raspberry Pi. After I ran all command whether bring up, rtammap, etc. Found out that Rviz cannot open it up. "qt.qpa.xcb: Could not connect to display". So, need to check the X11Forwarding in `sudo nano /etc/ssh/sshd_config` that are indicated yes or no. If no, change it into yes.

On the pink computer use `ssh -Y SaPHaRI@192.168.0.213` (adding -Y).

**Result:** I can open Rviz from pink computer. And mapping the lab area is a lot **faster.**


### September 17th, 2024

**Objective:** Continue from yesterday.

**Experiment:** After I map the lab area, I can save the map but cannot find the saved file; I just reboot it. It turns out that it does not save the map, it saves just configuration so that means I cannot save the map but I can run the move_base file that I cannot run earlier on the Raspberry Pi itself.

To create **move_base** file
- Create a package for the navigation configuration
	- `cd kobuki_ws/src/`
	- `catkin_create_pkg my_navigation` (my_navigation just the name can be change)
- Create a config directory
	- `cd my_navigation`
	- `mkdir config`
- Create a configuration file (cost map)
	- `cd config`
	- `nano costmap_common_params.yaml`
```
obstacle_range: 2.5
raytrace_range: 3.0
footprint: [[-0.35, -0.35], [-0.35, 0.35], [0.35, 0.35], [0.35, -0.35]]
inflation_radius: 0.55
```
- Create more configuration file (local cost map)
	- `nano local_costmap_params.yaml`
```
local_costmap:
  global_frame: odom
  robot_base_frame: base_link
  update_frequency: 5.0
  publish_frequency: 2.0
  rolling_window: true
  width: 2.5
  height: 2.5
  resolution: 0.05
  static_map: false
  
  plugins:
    - {name: obstacle_layer, type: "costmap_2d::ObstacleLayer"}
    - {name: inflation_layer, type: "costmap_2d::InflationLayer"}
```
- Create last configuration file (global cost map)
	- `nano global_costmap_params.yaml`
```
global_costmap:
  global_frame: map
  robot_base_frame: base_link
  update_frequency: 5.0
  publish_frequency: 2.0
  static_map: true
  
  plugins:
    - {name: obstacle_layer, type: "costmap_2d::ObstacleLayer"}
    - {name: inflation_layer, type: "costmap_2d::InflationLayer"}
```
- Create a lunch directory
	- `cd ..`
	- `mkdir launch`
- Create a launch file (move_base)
	- `cd launch` 
	- `nano move_base.launch`
```
<launch>
  <node pkg="move_base" type="move_base" name="move_base" output="screen">
    <param name="base_global_planner" value="navfn/NavfnROS"/>
    <rosparam file="$(find my_navigation)/config/costmap_common_params.yaml" command="load" />
    <rosparam file="$(find my_navigation)/config/global_costmap_params.yaml" command="load" />
    <rosparam file="$(find my_navigation)/config/local_costmap_params.yaml" command="load" />
  </node>
</launch>
```
- Build the workspace
	- `cd ~/kuboki_ws`
	- `catkin_make`
	- `source devel/setup.bash`
- Then try launch the file
	- `roslaunch my_navigation move_base.launch`

**Problem:** If I use ssh in every single terminal; workload in Raspberry Pi is still heavy even though it is faster.

**Fix:** I run the Rviz in the pink computer (not ssh into Raspberry Pi).

**Result:** I can run the move_base file but still have an error.
![[Screenshot 2024-09-18 at 11.24.53 AM.png]]
And mapping the lab area is a lot faster if compared to when open Rviz via ssh. 


### September 19th, 2024

**Objective:** Path Planning

**Experiment:** To streaming data
- Install image_transport for efficient image transfer
	- `sudo apt install ros-noetic-image-transport`
- Use compressed_image_transport to minimize bandwidth usage
	- `rosrun image_transport republish raw in:=/kinect/rgb/image_raw compressed out:=/kinect/rgb/image_compressed` 

**Problem:** When run the command `roslaunch turtlebot_bringup minimal.launch` I got some warning; disk usage in log directory is over 1 GB recommended to use "rosclean" command. After that I checking all Raspberry Pi and found out in Raspberry Pi 1 have changed the IP Address.

**Fix:** running `rosclean check` to see the amount of usage. I copy the all files just in case.
- Locate the Log Files: ROS log files are usually stored in here
	- `cd ~/.ros/log`
- Create a Backup Directory
	- `mkdif ~/ros_logs_backup`
- Copy the Log Files: this command will copy all the files without deleting them from the original location
	- `cp -r ~/.ros/log/* ~/ros_logs_backup/`
- Verify Backup
	- `ls ~/ros_logs_backup`
- Then clean it up
	- `rosclean purge`

**Result:** Error. I cannot streaming efficient data.

Raspberry Pi 1: 192.168.0.92 | 101M ROS node logs.
Raspberry Pi 2: Same | 45M ROS node logs.
Raspberry Pi 3: Same | 28M ROS node logs.
Raspberry Pi 4: Same | 25M ROS node logs.
Raspberry Pi 5: Same | 8.3M ROS node logs.
Raspberry Pi 6: Same | 1.1GB ROS node logs. -> **Raspberry Pi 6: Same | 0GB ROS node logs.**
Raspberry Pi 7: Same | 1.3M ROS node logs.


### September 20th, 2024

**Objective:**

**Experiment:**

**Result:** 