
### November 25th, 2024

**Objective:** Make LiDAR compatible with TurtleBot 2.

**Experiment:** Need to fix the orientation of the LiDAR by fix digits in this command `rosrun tf2_ros static_transform_publisher 0 0 0 0 0 0 1 base_link base_laser`.

The first three digits (in meters) correspond to the following: 1) the forward/backward distance from the center of the robot, 2) the side-to-side offset, and 3) the height of the LiDAR sensor above the ground. The subsequent three digits signify the axes of rotation (x, y, z), while the last digit denotes the rotation itself. The final configuration I used was "0 0 0.6 0 1 0 0".

This is the result command `rosrun tf2_ros static_transform_publisher 0 0 0.6 0 1 0 0 base_link base_laser`
