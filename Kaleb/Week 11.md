## <u>11/7/24</u>

### Moving Object Detection (Day 4)
- On `ssh -Y SaPHaRI@192.168.0.213` for the Pi
	- `ROS_MASTER_IP` should be the Desktop's (192.168.0.41)
	- Ran `minimal.launch` and the LiDAR sensor's plugged in
- On the desktop
	- `roscore`
- In another `ssh -Y ...` for the Pi...
	- `roslaunch datmo example.launch bag:=overtakes`