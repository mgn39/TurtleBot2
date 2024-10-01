# Use the official ROS Noetic desktop image
FROM tiryoh/ros-desktop-vnc:noetic-arm64-20240526T0237

# Ensure the environment is set up whenever a new shell is started
RUN rm /bin/sh && ln -s /bin/bash /bin/sh

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
RUN apt update && apt install -y curl gnupg2 lsb-release \
    python3-catkin-tools ros-noetic-desktop-full python3-rosdep \
    ros-noetic-openslam-gmapping ros-noetic-base-local-planner ros-noetic-clear-costmap-recovery ros-noetic-move-base-msgs ros-noetic-navfn ros-noetic-rotate-recovery xsltproc ros-noetic-map-server ros-noetic-amcl ros-noetic-dwa-local-planner ros-noetic-rosbridge-* ros-noetic-ecl-console ros-noetic-ecl-command-line ros-noetic-ecl-converters ros-noetic-ecl-devices ros-noetic-ecl-geometry ros-noetic-ecl-mobile-robot ros-noetic-ecl-sigslots ros-noetic-ecl-time python3-empy ros-noetic-ddynamic-reconfigure ros-noetic-teb-local-planner \
    && rm -rf /var/lib/apt/lists/*

# Initialize rosdep if it hasn't been alr
RUN if [ ! -f /etc/ros/rosdep/sources.list.d/20-default.list ]; then \
        rosdep init && rosdep update; \
    fi

# Set up ROS environment variables, change 192.168.0.8 to Turtlebot's
RUN echo ". /opt/ros/noetic/setup.bash" >> /root/.bashrc && \
    echo "export ROS_MASTER_URI=http://192.168.0.8:11311" >> /root/.bashrc && \
	echo "export ROS_IP=$(hostname -I)" >> /root/.bashrc && \
	echo "export ROS_HOSTNAME=$(hostname -I)" >> /root/.bashrc && \
    source /root/.bashrc
ENV CMAKE_PREFIX_PATH=/opt/ros/noetic

# stinky catkin
# following commands are from https://gist.github.com/jeremyfix/0c5973aba508ee8b6e8d3c3077c6db1e
RUN mkdir -p /root/catkin_ws/src && \
    . /opt/ros/noetic/setup.bash && \
    cd /root/catkin_ws && \
    catkin_make
RUN apt-get update && apt-get install -y git vim iputils-ping

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

# Install necessary packages
RUN . /opt/ros/noetic/setup.bash && \
    apt-get update && rosdep update && \
    apt-get install -y liborocos-kdl-dev ros-noetic-joy && \
    rosdep install --from-paths . --ignore-src -r -y

# Build the Catkin workspace
WORKDIR /root/catkin_ws
RUN . /opt/ros/noetic/setup.bash && \
    catkin_make

# Set default shell to bash
# CMD ["/bin/bash"]