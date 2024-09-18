
### September 16th, 2024

**Objective:** Try to do path planning via pink computer. 

**Problem:** Cannot open Rviz.

**Experiment:** ssh from pink computer into Raspberry Pi. After I ran all command whether bring up, rtammap, etc. Found out that Rviz cannot open it up. "qt.qpa.xcb: Could not connect to display". So, need to check the X11Forwarding in `sudo nano /etc/ssh/sshd_config` that are indicated yes or no. If no, change it into yes.

On the pink computer use `ssh -Y SaPHaRI@192.168.0.213` (adding -Y).

**Result:** 


### September 17th, 2024

**Objective:** Continue from yesterday.

**Experiment:** 

**Result:** 

