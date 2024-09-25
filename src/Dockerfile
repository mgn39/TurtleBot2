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
    git clone https://github.com/yujinrobot/yujin_ocs && \
    git clone https://github.com/yujinrobot/kobuki.git

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