
### October 21st, 2024

**Objective:** Test on LiDAR Sensor again.

**Experiment:** You can check the [RPLIDAR Wiki](https://wiki.youyeetoo.com/en/Lidar/A1M8) here.

Source workspace, catkin_make, reinstall won't help.

**Result:** Still cannot use it.


### October 23rd, 2024

**Objective:** Still test on LiDAR Sensor.

**Experiment:** Follow advice from Dr. Block instead of launch the whole file run each file instead (individually). I run `rplidar_a1.launch` and `rviz` separately. LiDAR can publish the data normally but cannot show in the rviz, in rviz shown that status is error.

I run `rosrun tf view_frames` but I did not see any thing that related to LiDAR. I tried to publish a static transform manually by using `rosrun tf static_transform_publisher 0 0 0 0 0 0 base_link laser_link 100` still not help.

I think it all about topic name (Fixed Frame). So, I have no `laser` or `base_laser_link` in my rviz. And I know that I use `map` in rtabmap. So, I config the `rplidar_a1.launch` file.
```
<launch>
  <node name="rplidarNode"          pkg="rplidar_ros"  type="rplidarNode" output="screen">
  <param name="serial_port"         type="string" value="/dev/ttyUSB0"/>
  <param name="serial_baudrate"     type="int"    value="115200"/>
  <param name="frame_id"            type="string" value="map"/>
  <param name="inverted"            type="bool"   value="false"/>
  <param name="angle_compensate"    type="bool"   value="true"/>
  </node>
</launch>
```

**Result:** I can use LiDAR and Kinect (rtabmap) simultaneously.
![[LiDAR + RTABMAP.png]]
Adding the area in rviz in the grid `Plane Cell Count` it seem larger but did not test yet.

Get rid off 2 warnings from `roslaunch freenect_launch freenect.launch` by add 2 files
- Calibration file
	- `nano /home/SaPHaRI/.ros/camera_info/rgb_B70773100531325B.yaml`
```
image_width: 640
image_height: 480
camera_name: rgb_B70773100531325B
camera_matrix:
  rows: 3
  cols: 3
  data: [525.0, 0.0, 319.5, 0.0, 525.0, 239.5, 0.0, 0.0, 1.0]
distortion_model: plumb_bob
distortion_coefficients:
  rows: 1
  cols: 5
  data: [0.0, 0.0, 0.0, 0.0, 0.0]
rectification_matrix:
  rows: 3
  cols: 3
  data: [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
projection_matrix:
  rows: 3
  cols: 4
  data: [525.0, 0.0, 319.5, 0.0, 0.0, 525.0, 239.5, 0.0, 0.0, 0.0, 1.0, 0.0]
```
- Depth Calibration file
	- `nano /home/SaPHaRI/.ros/camera_info/depth_B70773100531325B.yaml`
```
image_width: 640
image_height: 480
camera_name: depth_B70773100531325B
camera_matrix:
  rows: 3
  cols: 3
  data: [580.0, 0.0, 319.5, 0.0, 580.0, 239.5, 0.0, 0.0, 0.0, 1.0]
distortion_model: plumb_bob
distortion_coefficients:
  rows: 1
  cols: 5
  data: [0.0, 0.0, 0.0, 0.0, 0.0]
rectification_matrix:
  rows: 3
  cols: 3
  data: [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
projection_matrix:
  rows: 3
  cols: 4
  data: [580.0, 0.0, 319.5, 0.0, 0.0, 580.0, 239.5, 0.0, 0.0, 0.0, 1.0, 0.0]
```



### October 24th, 2024

Preparing the demo for pre demo tomorrow.


### October 25th, 2024

Do the pre demo.