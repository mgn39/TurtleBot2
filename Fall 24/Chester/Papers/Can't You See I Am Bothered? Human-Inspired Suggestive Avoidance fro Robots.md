Du, Kanda | ACM\IEEE International Conference on Human-Robot Interaction 2024 | March 11th, 2024

**Links:** [Can't You See I Am Bothered?](https://dl.acm.org/doi/abs/10.1145/3610977.3634954)

**Conclusion:**

They studied how robots could stop people from repeatedly obstructing them. Suggestive avoidance it consists of making a quick movement to the side while rotating the body and gaze toward the obstructing person. Implemented it on a robot, and tested it both in a lab experiment and a field study. The field study showed that when a robot uses suggestive avoidance people are less likely to bother it again.

Modeling of Suggestive Avoidance:
- Bothering person appears
- Gazing
- Step aside
- Rotation
- Back on their way

Robot Hardware:
- Humanoid robot
	- with an omnidirectional base
- LiDAR sensor
	- a Velodyne HDL-32E
- Laser range finder
	- Hokuyo UTM-30LX

Path Planner and Path Follower
- Used a classic A* search algorithm
- Dynamic window approach (DWA)

Localization was based on matching the point cloud data from both laser range finders and the LiDAR on the robot to a 3D occupancy map, using a particle filter. People were tracked using point cloud data from the LiDAR.

Method
- Proposed model (suggestive avoidance): The robot uses suggestive avoidance
- Baseline (standard navigation): The robot uses standard navigation (A* path planning and DWA path following) without modifications and people are treated as normal obstacles