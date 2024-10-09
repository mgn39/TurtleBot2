
### October 8th, 2024

**Research:** Doorbell and LiDAR Sensor.
- LiDAR Sensor
	- Confirm to order **RPLIDAR A1M8** from Amazon
	- Price ~100$

- Doorbell
	- Ring video doorbell
		- Set up (follow the manual) + Connect to Wifi
	- IFTTT (If This Then That)
		- Trigger: Set the trigger to be "When Ring doorbell is pressed"
		- Action: Set the action to send the data to Raspberry Pi
	- Set up on the Raspberry Pi
		- Set up the listener on Raspberry Pi to receive the signal
		- Set up the ROS topic to trigger the TurtleBot movement


### October 9th, 2024

**Objective:** Map the larger area (to Dr. Block room)

**Experiment:** I try new setting while do the larger map as well. At first I use `/rtabmap/grib_prob_map` but in this time I use `/rtabmap/gib_map`.

![[Larger map with new setting.png]]
For my feeling I like `/rtabmap/grid_prob_map` more because the map is more reliable and more stable but map harder than `/rtabmap/grid_map`.

Have some limit due to have many people walk by so my map collapse. I need to wait until night because less people.

**Result:** 
