
### September 16th, 2024

**Objective:** Try to do path planning via pink computer. 

**Problem:** Cannot open Rviz.

**Experiment:** ssh from pink computer into Raspberry Pi. After I ran all command whether bring up, rtammap, etc. Found out that Rviz cannot open it up. "qt.qpa.xcb: Could not connect to display". So, need to check the X11Forwarding in `sudo nano /etc/ssh/sshd_config` that are indicated yes or no. If no, change it into yes.

On the pink computer use `ssh -Y SaPHaRI@192.168.0.213` (adding -Y).

**Result:** I can open Rviz from pink computer. And mapping the lab area is a lot **faster.**


### September 17th, 2024

**Objective:** Continue from yesterday.

**Experiment:** After I map the lab area, I can save the map but cannot find the saved file; I just reboot it. It turns out that it does not save the map, it saves just configuration so that means I cannot save the map but I can run the move_base file that I cannot run earlier on the Raspberry Pi itself.

To create **move_base** file
- Create a package for the navigation configuration
	- `cd kobuki_ws/src/`
	- `catkin_create_pkg my_navigation` (my_navigation just the name can be change)
- Create configuration files
	- Create a config directory
		- `mkdir config`
		- `nano costmap_common_params.yaml`
			- 
		- `nano local_costmap_params.yaml`
			- 
		- `nano global_costmap_params.yaml` 
			- 
	- Create a launch directory
		- `mkdir launch`
		- `cd launch`
		- `nano move_base.launch`
- Build the workspace
	- `cd ~/kobuki_ws`
	- `catkin_make`
	- `source devel/setup.bash`
- Then try launch the file
	- `roslaunch my_navigation move_base.launch`

**Problem:** If I use ssh in every single terminal; workload in Raspberry Pi is still heavy even though it is faster.

**Fix:** I run the Rviz in the pink computer (not ssh into Raspberry Pi).

**Result:** 

