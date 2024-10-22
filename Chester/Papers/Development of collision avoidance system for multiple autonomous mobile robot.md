Hou, Atikah, Homod, International Journal of Advanced Robotic Systems | August 17th, 2020

**Links:** [Development of collision avoidance](https://journals.sagepub.com/doi/full/10.1177/1729881420923967)

**Conclusion:** 

Main concept is to test on the 2 ways communication (vehicle-to-vehicle or V2V) due to possibility of collision between autonomous vehicles with the lack of V2V.

With a 2 ways communication system, potential accidents can be mitigated since the vehicles will be able to estimate the other around them based on the current position, especially when the sensors and camera fail to detect the obstacles.

The fundamental sensors normally used by autonomous vehicles are radar, light detection and ranging (LiDAR), radar is capable to work in every condition and can even use reflection to see behind obstacles. LiDAR is favorably used for 3D mapping. LiDAR is a technology can scan more than 100 m in all directions (360 degree imaging), generating a precise 3D map of the car's surrounding that are very vital for autonomous cars to make intelligent detections.

The algorithm was loaded into the Raspberry Pi/Laptop to program the TurtleBot for the autonomous navigation system. The Wi-Fi router allows TurtleBot to communicate with another TurtleBot using Google LCM, which is similar to the DSRC system. The initial position and distance of the TurtleBot are calculated using rear end collision scenario (RECS) setup and junction crossing intersection collision scenario (JCICS) setup.