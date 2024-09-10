## <u>9/9/24</u>

### Sensor research
- **IMU (Inertial Measurement Unit):** An IMU can measure angular velocities and accelerations, which can be used to determine orientation. For azimuth, a 9-axis IMU (which includes gyroscope, accelerometer, and magnetometer) would be ideal. The magnetometer helps in determining the heading relative to the Earth's magnetic field.
- **Compass Module:** A digital compass or magnetometer, like the HMC5883L or QMC5883L, can provide direct azimuth measurements. These sensors can give you the heading relative to the magnetic north.
- **GPS and SLAM:** If you need more precise positioning and azimuth information, combining GPS data with SLAM (Simultaneous Localization and Mapping) can be effective. SLAM algorithms can help in determining the robot's orientation in a mapped environment.
- **Using ROS (Robot Operating System):** In ROS, you can integrate various sensors and use packages like `robot_localization` to fuse data from IMUs, compasses, and GPS for accurate azimuth and orientation information.

### Robot arm
- Designs
	- Supported stick tall enough for the bot to run into the wall, activating the button
	- Ramp that raises the bot to hit the tip of the button
	- Arm that rotates into the button (costly)
- Arm specifications
	- uhhh need to measure

## <u>9/10/24</u>
### Asymmetric Turtlebot Movement
- Basic Strategy
	- Use `ROS_NAMESPACE` (path variable) to access each individual Turtlebot name
	- In each script, use an `if` statement to check the namespace
	- Set a `global` direction variable that'll send each Turtlebot in its own direction, giving it asymmetric movement
- Next steps
	- Determine what to do
	- Look into detecting how many bots on the network
- **Doing thing**
	- Script in `kobuki_ws/src/turtlebot/turtlebot_teleop/scripts`

### Object Detection + Sensing
- Without purchasing extra sensors or equipment it's possible?
	- Turtlebot isn't going backwards, so 180 deg for the back isn't necessary
	- Libraries to do this exact sort of job through [ROS Kinect](https://docs.ros.org/en/kinetic/api/moveit_tutorials/html/doc/getting_started/getting_started.html)
- Basic Strategy
	- Isolate Turtlebot4
	- Install and experiment with the library...then see if more is needed