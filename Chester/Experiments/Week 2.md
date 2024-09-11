
### September 4th, 2024

**Objective:** Fix the 6th one that had not been connected the last time.

**Experiment:** Updating the source and exporting the IP Address in nano ~/.bashrc
`source /home/SaPHaRI/kobuki_ws/devel/setup.bash
`export ROS_MASTER_URI=http://192.168.0.91:11311
`export ROS_IP=192.168.0.213

**Result:** 6 are controlled!!!
![[Pasted image 20240911113349.png]]

### September 5th, 2024

**Objective:** Avoiding identify name every single time when bring up (connect Raspberry Pi to TurtleBot)

**Experiment:** Type this command `export ROS_NAMESPACE=<name>` into nano ~/.bashrc and save it!. But still need to relay every single time.
