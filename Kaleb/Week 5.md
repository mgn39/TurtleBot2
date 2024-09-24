## <u>9/23/24</u>

### Networking
- How can we communicate effectively between a publisher and subscriber?
	- https://learn.turtlebot.com/2015/02/01/11/
	- https://answers.ros.org/question/406424/send-data-from-robot-to-pc-for-visualization/
	- https://dabit-industries.github.io/turtlebot2-tutorials/02b-Network_Setup.html <-- good setup resource

### Scripting & Object Avoidance
- All reference files for scripted movement and object avoidance in this repo:
	- https://github.com/markwsilliman/turtlebot/
### <u>9/24/24</u>
### Robostack Side Quest
- Following instructions on https://robostack.github.io/GettingStarted.html
	- Installation
		- Requires `miniforge`, downloadable [here](https://github.com/conda-forge/miniforge?tab=readme-ov-file) 
		- For the conda option, I didn't set it to startup by default. We'll interchangeably be using conda, a cross-platform system package manager, and mamba, a drop-in replacement for conda that resolves dependencies better.
		- To modify conda shell startup default:
			- `conda config --set auto_activate_base false`
			- Undo it by running `conda init --reverse $SHELL
		- To activate conda's base environment in shell session:
			- `eval "$(/Users/kaleb/miniforge3/bin/conda shell.YOUR_SHELL_NAME hook)" `
			- Then run `conda init`
	- Networking Setup
		- Using Pi #4 + Katherine Howard (Bot 5) -> IP: 192.168.0.8
		- To configure the network, use `cd $CONDA_PREFIX` to enter the `ros_env`
		- Edit `setup.bash` and add the following network config lines:
			- `export ROS_MASTER_URI=http://192.168.0.8:11311`
			- `export ROS_IP=<workstation ip address>`
			- `export ROS_HOSTNAME=<workstation ip address>`
		- Then as usual, run `source $CONDA_PREFIX/setup.bash`
		- To test, just ping each other's IPs
	- Rebuild all Turtlebot2 packages...
		- Follow [README](./../README.md) instructions, then use the following script for all the required packages in `/kobuki_ws/src:
       ```
		# standard Turtlebot packages with some pizza
		conda install python-orocos-kdl
		git clone https://github.com/yujinrobot/kobuki.git
		git clone https://github.com/yujinrobot/kobuki_description.git
		git clone https://github.com/yujinrobot/yocs_virtual_sensor.git
		git clone https://github.com/yujinrobot/yujin_ocs.git
		git clone https://github.com/turtlebot/turtlebot.git
		git clone https://github.com/turtlebot/turtlebot_msgs.git
		git clone https://github.com/turtlebot/turtlebot_apps.git
		git clone https://github.com/turtlebot/turtlebot_simulator.git
		
		# for Robostack specifically
		git clone https://github.com/osrf/capabilities
		git clone https://github.com/AutonomyLab/create_robot/tree/noetic
		git clone https://github.com/ros-perception/depthimage_to_laserscan
		git clone https://github.com/stonier/ecl_core/tree/release/0.62-noetic
		git clone https://github.com/ros-drivers/linux_peripheral_interfaces
		git clone https://github.com/ros-drivers/openni_camera
		git clone https://github.com/ros-planning/robot_pose_ekf
		
		rosdep install --from-paths . --ignore-src -r -y # produces errors
		```
	- **SIKE** this sucks we're moving to Docker, deleting conda env with:
		- `conda remove -n ros_env --all`
### Docker Side Quest
- No more headaches trying to rebuild every single thing from source. Screw Robostack.
	- Downloading [Docker Desktop](https://docs.docker.com/desktop/)
	- Created a new repository
### Door Opening Side Quest
- Remote-controlled lever that actuates the disability button
	- 