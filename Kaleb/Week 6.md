## <u>10/1/24</u>
### Docker Side Quest (Day 2)
- Building:
	- NOTE: I'm on an M1 Macbook Pro (ARM-based), so I'm using `tiryoh/ros-desktop-vnc:noetic-arm64-20240526T0237`
		- If on an M1 or ARM-based machine, no change is necessary
		- If not on an M1 or ARM-based machine i.e. amd64 systems, change the first line of the Dockerfile to `FROM osrf/ros:noetic-desktop-focal`
	- Revamped [Dockerfile](../src/Dockerfile) from Day 1
		- Removed the zsh shell and created a soft link to ince `source` doesn't come natively
		- Source `setup.bash` for each `RUN` command is called in a different subshell
		- `root` and `~` are the same when called as the root user, else `~` refers to the home directory $-->$ use `root` whenever possible, not `~`
		- `rosdep update` should be called right before `catkin_make` to resolve deps, not need to `rosdep init` though...don't delete the list either
		- Adding the `ping` command with `iputils`
	- Navigate to the directory with the Dockerfile, then build with `docker build -t ros-noetic-desktop-full .`
- Running (networking + rviz):
	- In one terminal, launch: 
	  ```bash
	    docker run -t \
			--env="DISPLAY=host.docker.internal:0" \
			--env="QT_X11_NO_MITSHM=1" \
			--volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
			-p 25565:80 -p 11311:11311 \
			ros-noetic-desktop-full \
		    rviz
		```
	- In another terminal, run `docker exec -it $(docker ps -l -q) /bin/bash`. Breakdown:
		- `docker exec` executes a container
		- `-i` enables interaction and `-t` for pseudo-TTY
		- `$docker ps -l -q` extracts the latest (`-l`) container ID `-q`
		- `/bin/bash` ensures we're using the bash shell _(though not fully necessary since we deleted zsh and hard linked it to /bin/bash already)_
- Networking:
	- Redoing the networking setup since I couldn't figure out how to ping right. The goal right now is to ping from my host machine (Macbook) to the container IP
	- The [Docker documentation](https://docs.docker.com/engine/network/) is a great resource, but appears it's mainly for container-to-container networking?
	- HOW IN THE WORLD DO YOU DO THIS IT DOESN'T MAKE SENSE AM I STUPID
- GUI:
	- Trying to run `rviz` and other GUI components. It's kinda broken and I need to figure out X11 forward and such
	- Will be using the simple way (method 1) listed in the [ROS + Docker Wiki](https://wiki.ros.org/es/docker/Tutorials/GUI) and [XQuartz](https://www.xquartz.org/) (for MacOS)

## <u>10/3/24</u>
### Docker Side Quest (Day 3)
- Networking:
	- Again, updated [Dockerfile](../src/Dockerfile)
	- There are issues with MacOS that prevent a direct pinging of the container from host
	- When running a container on Docker Desktop, port forward for `25565:80` and `11311:11311`.
		- If running from CLI, this is done through the flag `-p 25565:80 -p 11311:11311`
		- Planning to use `25565` as a web server for port forwarding
		- Planning to use `11311` for internal ROS communication
	- The Pi should connect to the host over a port that bridges to the container; where the MASTER_URI should point to
	- Pinging uses the Internet Communication Messaging Protocol (ICMP) instead of Transmission Control Protocol (TCP), which doesn't matter cause ROS will be communicating with 