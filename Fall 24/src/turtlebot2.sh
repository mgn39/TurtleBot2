# This is a modified version of https://gist.github.com/jeremyfix/0c5973aba508ee8b6e8d3c3077c6db1e
# Trying to migrate to only Dockerfile
apt update -y
apt install git vim -y
cd ~
mkdir -p ~/catkin_ws/src
cd catkin_ws
catkin_make
cd src

# Clone the required repositories
git clone https://github.com/yujinrobot/kobuki.git
# git clone https://github.com/yujinrobot/kobuki_msgs.git
# git clone https://github.com/yujinrobot/kobuki_core.git
git clone https://github.com/turtlebot/turtlebot
git clone https://github.com/turtlebot/turtlebot_msgs
git clone https://github.com/turtlebot/turtlebot_apps
git clone https://github.com/turtlebot/turtlebot_simulator
git clone https://github.com/yujinrobot/yujin_ocs

# Keep 'yocs_cmd_vel_mux', 'yocs_controllers', and 'yocs_velocity_smoother'
mv yujin_ocs/yocs_cmd_vel_mux yujin_ocs/yocs_controllers yujin_ocs/yocs_velocity_smoother .
rm -rf yujin_ocs

# Add the battery monitor package
git clone https://github.com/ros-drivers/linux_peripheral_interfaces
mv linux_peripheral_interfaces/laptop_battery_monitor ./
rm -rf linux_peripheral_interfaces

# Following https://github.com/yujinrobot/kobuki/issues/427
sudo apt install liborocos-kdl-dev -y
sudo apt install ros-noetic-joy -y

# Build
cd ..
catkin_make

# yeah I hate this command
rosdep install --from-paths . --ignore-src -r -y
