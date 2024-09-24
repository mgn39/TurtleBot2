
### September 23th, 2024

**Objective:** Path Planing

**Experiment:** Try to do path planning.

**Problem:** I cannot bringup after ran `sudo apt autoremove`

**Fix:** Install some packages
- Install kdl_conversions package
	- `sudo apt-get install ros-noetic-kdl-conversions -y`
- Install camera_info_manager package
	- `sudo apt-get install ros-noetic-camera-info-manager -y`
- Install cmake_modules package
	- `sudo apt-get install ros-noetic-cmake-modules -y`
- Install visualization_msgs package
	- `sudo apt-get install ros-noetic-visualization-msgs -y`
- Install angles package
	- `sudo apt-get install ros-noetic-angles -y`


**Result:** Can work again.


### September 24th, 2024

**Objective:** Path Planing (Configuration)

**Experiment:**

**Result:** 