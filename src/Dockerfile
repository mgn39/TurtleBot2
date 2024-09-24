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
RUN apt-get install python3-rosdep
RUN rosdep init && rosdep update

# Set up ROS environment variables
RUN echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc

# Set default shell to bash
CMD ["/bin/bash"]
