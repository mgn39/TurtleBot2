
### 00 | August 27th, 2024

Make a project plan for Fall Semester.


### 1st | September 3rd, 2024

[Fall | 1st | Path Planning & ROS 2](https://docs.google.com/presentation/d/1tCsQanxvls6BLPP_sbjQ3Q1yQnOed9yRa5Zvo4SLzBg/edit?usp=sharing)

- Expand the limitation of the Raspberry Pi
- Research
	- Distance Sensor
	- Tour Guide Robot
	- Office Robot
- Read 2 documents (In SaPHaRI drive)
	- How to read paper
	- Primer for Conducting Experiments in HRI


### 2nd | September 10th, 2024

[Fall | 2nd | Path Planning & Communication & Object detection](https://docs.google.com/presentation/d/1vddYcBRm07Pz5tnCfKBQbD0pOc2AUjzkZXdTrmfxIQo/edit?usp=sharing)

- Path Planning
	- Use other computer to improve processing power
- Communication
	- Build new teleop file instead of edit it directly
- Consider
	- FOV for person
	- Hallway depth
	- Robot
		- Distance to person
- Our Project
	- Focusing on
		- How does the spatial configuration of tour guide robots affect...?
		- Following distance
		- Number of robots
		- Spatial distribution (180 POV vs full 360)
	- How does robot behavior affect...?
		- Different styles of music
- Research
	- General sound of movement
	- Robotics & Sound


### 3rd | September 17th, 2024

[Fall | 3rd | Path Planning & Communication & Object detection](https://docs.google.com/presentation/d/1A3duBmiX7N_WEsW9-zB4yRWIrXyZTolwiHceXCRLpRA/edit?usp=sharing)

**A bit behind the plan** 
- Path Planning
	- Try to do ROS publish and subscribe instead
	- Neuro Reality
		- To stream data
	- Checking the speed of sending data (use ROS command)
- Other update
	- If we can do path planning before next meeting; the meeting can be skip!


### 4th | September 24th, 2024

[Fall | 4th | Path Planning & Communication & Object detection](https://docs.google.com/presentation/d/1gl0PDvwv_8z4YSAAstxr5Q-XXCOAMZjoCHSpwODfhQE/edit?usp=share_link)

- Path Planning
	- [The robot's start position is off. Planing will always fail](https://robotics.stackexchange.com/questions/102710/noetic-rtabmap-move-basei-cannot-resolve-the-error-the-robots-start-positi)
	- [Unable to get starting pose of robot, unable to create global plan]([https://answers.ros.org/question/58796/move_base-warning-unable-to-get-starting-pose-of-robot-unable-to-create-global-plan/](https://answers.ros.org/question/58796/move_base-warning-unable-to-get-starting-pose-of-robot-unable-to-create-global-plan/ "https://answers.ros.org/question/58796/move_base-warning-unable-to-get-starting-pose-of-robot-unable-to-create-global-plan/"))
- Communication
	- [RGB and Depth images out of sync](https://answers.ros.org/question/46280/reg-subscribing-to-depth-and-rgb-image-at-the-same-time/)
- Research
	- LiDAR sensor and buy it (1 piece)
	- Charging Station (Additional)
	- Kaleb's
		- Designing door opening mechanism
	- Chester's
		- Doorbell (to sending the signal)
		- Office beacons
- Other update
	- Dr. Block connect us to last author


### 5th | October 1st, 2024

[Fall | 5th | Path Planning & Research](https://docs.google.com/presentation/d/1R9HKMAPdzUN7GNVBjQcfk2W7qSU73n1ck9ft6LzE6Oc/edit?usp=sharing)

- Path Planning
	- Should done configuration before next meeting
- Research: Doorbell and Beacons should be in the same platform? Wi-Fi or Bluetooth
	- Doorbell
		- Looking for Smart Doorbell (including speaker and screen)
	- Beacons
		- To set goal locations
		- Might needs physical
	- Mechanism door opening
		- Method 1
	- LiDAR Sensor
		- Looking for RPLIDAR A1M8
	- Charging Station
		- We should by it
	- Additional Security
		- Set the hours?
- Other updates
	- Meeting
		- Donor Meeting on October 2nd, 2024
	- Demos
		- 3 Demos in this month - October 8, 28, 30th, 2024


### 6th | October 8th, 2024

[Fall | 6th | Path Planning & Research](https://docs.google.com/presentation/d/1KN8HEZ7Km-To96Fq2wMu-KL5QfT2asIITFljo7vklZU/edit?usp=sharing)

- Path Planning
	- Done!
	- Map larger area
- Research
	- Doorbell
		- 2 Doorbell
			- TurtleBot
			- Human
		- Record data
			- When the visitor arrives at HFI, how many times the visitor rings the doorbell? For humans or robots also record the date and time
			- Example: record 1 as robot, 2 as human
	- Mechanism door opening
		- Order Flipper Zero
	- LiDAR Sensor
		- Confirm RPLIDAR A1M8
	- Security
		- Set hours
			- 10am-4pm
- Other updates
	- IRB Google form
		- Kaleb should do too!
	- Return the controller and order the new one


### 7th | October 15th, 2024

[7th | Path Planning & Collision Detection & System Testing](https://docs.google.com/presentation/d/1ynyPxwtDAZy80TCe4hGs6_5UdjVs8oTyw3MkEsDYJY4/edit?usp=sharing)

- Path Planning
	- Integrate with LiDAR Sensor
- Test new Devices
	- Doorbell
		- Web Server
- Miscellaneous
	- Photo make as GIF
	- Moleskine Pro


### 8th | October 22nd, 2024

[8th | Path Planning & Collision Detection & System Testing](https://docs.google.com/presentation/d/15OYwBmGoGKp4OD8sxtKIClH94fj6F-UkvGovnvLdOgM/edit?usp=sharing)

- Path Planning 
- Test new Devices
	- Doorbell
		- Talk to Austin about the server that can store and send the data
	- RPLIDAR A1
		- Try to run `rosrun` command individually
- Miscellaneous
	- Demo
		- Will be same demo and oral presentation on everyday
		- October 29th, 2024
			- Only me
		- Test the demo on **October 25th, 2024 at 2pm**
			- 6 TurtleBots use wireless keyboard to control at once
			- 1 TurtleBot use controller to control


### 9th | October 29th, 2024

[9th | Path Planning & Collision Detection & System Testing](https://docs.google.com/presentation/d/1YTZn-J0urZD0LpOfPe0I4AiR5rIFaNdfggdNiYcV6wc/edit?usp=sharing)

- Collision Detection (Non-stationary object detection avoidance)
	- For avoid TurtleBot when do swarm
		- Each TurtleBot known their own initial pose, sent the initial pose to other TurtleBots
	- Same as mobile robot in Thailand in restaurant
		- White dot on the ceiling


### 10th | November 6th, 2024 (Email)

[10th | Path Planning & Collision Detection & System Testing](https://docs.google.com/presentation/d/1Hwn-ka7Q229t4awgWL5dn2Gz32J45gFCfVTrl0x1f_g/edit?usp=sharing)


### 11th | November 12th, 2024

[11th | Path Planning & Collision Detection & System Testing](https://docs.google.com/presentation/d/1zg3EuHGPExAy_Ijq7kKM2YrEVFIW9Jy8G9YqAMG5sl8/edit?usp=sharing)

- Doorbell
	- I might limit too much due to I cannot enable TurtleBot to move autonomously
- LiDAR Sensor
	- Check on this error
- Physical Door Actuation
	- Flip 180 degree
		- Disable person have to easy and comfort to access the door button
	- LiPo Charger