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
### Docker Side Quest (Day 1)
- No more headaches trying to rebuild every single thing from source. Screw Robostack.
	- Downloading [Docker Desktop](https://docs.docker.com/desktop/)
- Created a custom [Dockerfile](./../src/Dockerfile) to create our Turtlebot2-ready image `ros-noetic-desktop-arm64`:
```Dockerfile
FROM arm64v8/ubuntu:focal

# Set up your ROS environment
RUN apt update && apt install -y curl gnupg2 lsb-release

# Add the ROS repository
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add - \
  && echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list \
  && apt update

# Install the desktop-full version of ROS Noetic
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
RUN apt install -y ros-noetic-desktop-full

# Initialize rosdep
RUN apt-get install -y python3-rosdep
RUN rosdep init && rosdep update

# Set up ROS environment variables, change 192.168.0.8 to Turtlebot's
RUN echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
RUN echo "export ROS_MASTER_URI=http://192.168.0.8:11311" >> ~/.bashrc && \
	echo "export ROS_IP=$(hostname -I)" >> ~/.bashrc && \
	echo "export ROS_HOSTNAME=$(hostname -I)" >> ~/.bashrc
RUN source ~/.bashrc

## TURTLEBOT STUFF AAAAAAAAAAAAHHHHHHHHHH

# https://gist.github.com/jeremyfix/0c5973aba508ee8b6e8d3c3077c6db1e
RUN mkdir -p ~/catkin_ws/src && \
    cd ~/catkin_ws && \
    catkin_make
RUN apt-get update && apt-get install -y git vim

WORKDIR /root/catkin_ws/src

# Clone the required repositories
RUN git clone https://github.com/turtlebot/turtlebot && \
    git clone https://github.com/turtlebot/turtlebot_msgs && \
    git clone https://github.com/turtlebot/turtlebot_apps && \
    git clone https://github.com/turtlebot/turtlebot_simulator && \
    git clone https://github.com/yujinrobot/yujin_ocs

# Keep 'yocs_cmd_vel_mux', 'yocs_controllers', and 'yocs_velocity_smoother'
RUN mv yujin_ocs/yocs_cmd_vel_mux yujin_ocs/yocs_controllers yujin_ocs/yocs_velocity_smoother ./ \
    && rm -rf yujin_ocs

# Add the battery monitor package
RUN git clone https://github.com/ros-drivers/linux_peripheral_interfaces \
    && mv linux_peripheral_interfaces/laptop_battery_monitor ./ \
    && rm -rf linux_peripheral_interfaces

# Clone the MELODIC branch of the kobuki git
RUN git clone -b melodic https://github.com/yujinrobot/kobuki.git

# Install necessary packages
RUN apt-get update && \
    apt-get install -y liborocos-kdl-dev ros-noetic-joy && \
    rosdep init && \
    rosdep update && \
    rosdep install --from-paths . --ignore-src -r -y

# Build the Catkin workspace
WORKDIR /root/catkin_ws
RUN catkin_make

# Set default shell to bash
CMD ["/bin/bash"]
```
- To build the Dockerfile container, navigate to it in the terminal and run `docker build -t ros-noetic-desktop-arm64 .`
- To run the container, run `docker run -it ros-noetic-desktop-arm64`, then I lost braincells for 3 hours!
- **ISSUE:** Keyboard Teleop file works, but pressing buttons don't make the Turtlebot move, odd...
- For later: https://wiki.ros.org/docker/Tutorials/GUI

## <u>9/29/24</u>
### Door Opening Side Quest
- Remote-controlled lever that actuates the disability button ([push plate actuator](https://www.constructionspecifier.com/understanding-new-accessibility-requirements-for-doors/)), thinking of two methods:
	- Method 1: Sending a signal (preferred)
	- Method 2: Arduino + servo + transmitter setup
- Method 1
	- Technology required:
		- Radio Frequency (RF) Reader ($40) or FlipperZero ($170) -- standard EMF reader might be too sensitive to receive signals of 390 MHz?
		- USB transmitter, should connect to Pi or the FlipperZero
	- Spoke w/ friend (Shashank) from Amateur Radio Club who has RF detection equipment
		- Garage door openers usually range 300-390 MHz, this [disability door opening system](https://www.amazon.com/Handicap-Opener-Disabled-People-Operator/dp/B00XHN3QT4/ref=asc_df_B00XHN3QT4/?tag=hyprod-20&linkCode=df0&hvadid=692875362841&hvpos=&hvnetw=g&hvrand=13777473852223583244&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9015305&hvtargid=pla-2281435183818&psc=1&mcid=0352452fadc43f1ca9075d633446a027&hvocijid=13777473852223583244-B00XHN3QT4-&hvexpln=73)'s remote is 315 MHz
		- Highly recommends FlipperZero to avoid hassle and for quick, simple testing
	- **PROBLEM**: Likely needs to bypass rolling codes to send proper signal, [source](https://www.reddit.com/r/flipperzero/comments/v2sfha/handicap_push_doors/)
		- FlipperZero would help with this task, but this blog to [hack car doors](https://hackaday.io/project/164566-how-to-hack-a-car) is useful
	- This legal? Probably if it's for research...
- Method 2
	- Technology required:
		- ESP32 (microcontroller)
		- MG996R (servo motor)
		- 3D printed lever with some styrofoam
		- Power source...(**problem**)
	- Requires a strong servo motor that provides enough force to push the metal button.
		- The MG996R is rated for a starting torque of up to 11 kg cm ([source](https://www.rajguruelectronics.com/ProductView?tokDatRef=MTA1MA==&tokenId=NjY=&product=MG996%20SERVO%20MOTOR%20(180%20DEGREE)#:~:text=Servo%20Motor%20-%20MG996R%20servo%20motor%20(180%20DEGREE),-Add%20to%20Cart&text=It%20can%20generate%20a%20torque,handle%20demanding%20tasks%20with%20ease.))
		- Need to test, not entirely sure how much this means for the button