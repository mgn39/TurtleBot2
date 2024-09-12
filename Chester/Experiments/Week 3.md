
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


### September 12th, 2024

**Objective:** After adding a new user to the computer next to my desk. Do path planning by streaming the data to another computer.

**Problem:** Cannot run teleop on Raspberry Pi 1

**Experiment:** 
Add a User via Recovery Mode
- Reboot the System
	- Reboot the system, and as it boots up, hold the **Shift** key to access the **GRUB** boot menu
- Select Recovery Mode
	- In the GRUB menu, select the **Advanced options for Ubuntu.** Then select the **Recovery mode** for your current kernel (the one ending in (recovery mode))
- Drop to Root Shell
	- Once in the recovery mode, select **Root - Drop to root shell prompt.** 
- Remount the Filesystem
	- `mount -o remount,rw /`
- Create a New User
	- `adduser newusername`
	- newusername = enter the desire name
	- Then follow the pormpts to set the password and other details for the new user
	- In other details
		- Full name, Room number, Phone number, etc. you can skip by press **enter** key
- Grant Sudo Privileges
	- `usermod -aG sudo newusername`
	- newusername = enter the name that you put in the create a new user part
- Reboot the System
	- `reboot`
	- Boots up in log in with the new user

\Username: SaPHaRI
Password: 7TurtleBots!