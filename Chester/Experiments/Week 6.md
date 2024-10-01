
### September 30th, 2024

**Objective:** Save the map for path planning

**Experiment:** I save the configuration first (I don't know if it's related or not).
And I try many attempts by using the command `rosrun map_sever map_saver -f /path to map/map name`. So, `rosrun map_server map_saver -f /home/SaPHaRI/kobuki_ws/src/1stmap` this map will be saved under kobuki_ws/src folder. It takes more than 30 minutes.

I changed to this command instead `rosrun map_server map_saver map:=/rtabmap/grid_prob_map -f /home/SaPHaRI/kobuki_ws/src/1stmap` because due to I use rtabmap for mapping. In Global Options I chose /map. But in Map I chose /rtabmap/grid_prob_map so the topic does not match.

**Result:** Be able to save the map now


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

Charging Station for TurtleBot 2
- Battery life of TurtleBot **~2-3 hours**, battery life can vary based of factors (sensors)
- If we can reach our goal, it will be more helpful if we have a charging station
