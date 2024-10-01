## <u>10/1/24</u>
### Docker Side Quest (Day 2)
- Building:
	- I'm on an M1 Macbook Pro (ARM-based), so I'm using `docker pull tiryoh/ros-desktop-vnc:noetic-arm64-20240526T0237`
		- If not on an M1 or ARM-based machine, use `docker pull osrf/ros:noetic-desktop-focal`
	- Updated [Dockerfile](../src/Dockerfile) from Day 1
		- Had to debug at least 10 errors, biggest one being to source `setup.bash` as each `RUN` command is called in a different shell environment
		- Takes a few minutes to build
- Running:
	- Challenge is to run `rviz` and other GUI components. Will be using the simple way (method 1) listed in the [ROS + Docker Wiki](https://wiki.ros.org/es/docker/Tutorials/GUI) and [XQuartz](https://www.xquartz.org/) (for MacOS)
	- Launch with: `docker run -it --env="DISPLAY" --env="QT_X11_NO_MITSHM=1" --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" ros-noetic-desktop-arm64:latest rqt && export containerId=$(docker ps -l -q)`
	- Then `export containerId=$(docker ps -l -q)`
	- 