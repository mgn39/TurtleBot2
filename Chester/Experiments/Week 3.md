
### September 9th, 2024

**Objective:** Try to do path planning.

**Problem:** I cannot map the lab area as usual. Also connect the Kobuki TurtleBot -> cannot connect to the master.

**Experiment:** Before connecting to the Kobuki TurtleBot you need to set master again if you don't want to run roscore on the master.

Example: You set the Raspberry Pi 1 as the master if you want to connect the Kobuki TurtleBot with another Raspberry Pi; you need to set the one that you want to connect as the master otherwise you need to run roscore on the Raspberry Pi 1.

I discovered that if I change the name in nano ~/.bashrc they cannot communicate due to the name change. Before mapping the lab area, I need to delete `export ROS_NAMESPACE="name"` first.

**Result:** Its work again!!


### September 11th, 2024

**Objective:** Checking all Raspberry Pi setting in nano ~/.bashrc.

**Result:** Set all `export ROS_NAMESPACE="name"` in each Raspberry Pi except Raspberry Pi 6th because I use Raspberry Pi 6th as the one to do path planning. 
 