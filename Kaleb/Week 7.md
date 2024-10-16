## <u>10/8/24</u>
### Controller Side Quest (Day 1)
- The [Ultimate 2C](https://www.amazon.com/-/zh_TW/dp/B0D7367TK1?th=1) is designated for Windows 10.0+ and Android 9.0+
	- Chester pulled an oopsie and when looking at the pink color; subtle switch from the Ultimate C (compatible) to the Ultimate 2C (incompatible)
	- Taking that back, the Ultimate C and 2.4GHz is likely incompatible as well
- Should get [Xbox One S controller](https://www.amazon.com/Xbox-Core-Wireless-Controller-Deep-Controllers/dp/B09VV5LJS1/ref=sr_1_3?crid=WRHIS5YGVSQJ&dib=eyJ2IjoiMSJ9.esGG7pafXCEk_c9mSITHVcBlrZYuOm3xS4oFy_YYwoGmMOfyrE4rAzS9ZDX1dwrBgxneSjdiEvMoHCTkugBokpJbbrazNr7NgUStsEDX5OJZdLL83LrRADo4327KV-TBLhTweCbSpkpB_2SFOnkOgUGIrIbLQR7ozhDolmtQAWO6LyOpOrUsCpLlW79fBA4A0u8L53py4xlT4YrD4Ycj6bOefVGDzH04NlYc6l7-dP4.QCs3oWDtY4wYO0JLsHYXcujmf8vWqxxl57cJtEEkgTs&dib_tag=se&keywords=xbox%2Bone%2Bcontroller&qid=1728407453&s=videogames&sprefix=xbox%2Bone%2Bcontroller%2Cvideogames%2C89&sr=1-3&th=1) (~$55) to simplify coding and all sorts
	- [Guide for setting up an Xbox controller in Ubuntu 20.04](https://forum.arduino.cc/t/making-an-xbox-controller-work-on-ubuntu/1134394)
	- Another Reddit thread over the same issue
	- Alternative is the [Logitech F710](https://www.amazon.com/Logitech-Wireless-Nano-Receiver-Controller-Vibration/dp/B0041RR0TW/ref=sr_1_1?crid=22WHIJYIFYEO5&dib=eyJ2IjoiMSJ9.Dpo5bvFXpJM3oQEDxlrPqptRUMCmrgQtbpJsmm5uDVxNxlm_z0_53Fifqy3qQ34SUviGIAfQ1wMQhCzKBbUuysKsvOK8JCD7Y3czEX3arpPwjS4Zh3oyjrMO56RU2i8v1qstrS6kwZP5odFxc9KOGEzKck3d_FPcxiXhoqojYpDj-y7vVgSQHdK-Uzp3yXdX0gosSBu-MYdh45bnXFhdxYGVX1dxCj17tijWTWLX_Jk.7Z4sDz_xfKLNtLwwd5Ibmci2tutyM-O6NZCOOd08qSU&dib_tag=se&keywords=f710&qid=1728408009&s=videogames&sprefix=f710%2Cvideogames%2C90&sr=1-1), a little cheaper and as of 10/8/24 there's a 40% discount
- dinput is direct input (older), xinput is a new input (newer) that requires less setup–thus preferred to use xinput

## Docker Side Quest (Day 4)
- Using same commands as Day 2/3, now updating for the following:
	- Switching from bridge to host network to use host IP (`192.168.0.x`) instead of `172.17.0.x` IP
	- Updated DockerFile since it didn't call `setup.bash` in the catkin_ws w/ all the turtlebot modules
		- Rebuild with `docker build -t ros-noetic-desktop-arm64 .`
	- Updated run command (for **Terminal 1**):
	```bash
	  docker run -t \
			--env="DISPLAY=host.docker.internal:0" \
			--env="QT_X11_NO_MITSHM=1" \
			--volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
			-p 11311:11311 \
			ros-noetic-desktop-arm64
		```
	- **Terminal 2**: `docker exec -it $(docker ps -l -q) /bin/bash`
- Ok quitting Docker, it's not worth it. My 7 hours are gone.

## <u>10/15/24</u>

### Controller Side Quest (Day 2)
- Pairing the pink [Xbox One S controller](https://www.amazon.com/Xbox-Core-Wireless-Controller-Deep-Controllers/dp/B09VV5LJS1/ref=sr_1_3?crid=WRHIS5YGVSQJ&dib=eyJ2IjoiMSJ9.esGG7pafXCEk_c9mSITHVcBlrZYuOm3xS4oFy_YYwoGmMOfyrE4rAzS9ZDX1dwrBgxneSjdiEvMoHCTkugBokpJbbrazNr7NgUStsEDX5OJZdLL83LrRADo4327KV-TBLhTweCbSpkpB_2SFOnkOgUGIrIbLQR7ozhDolmtQAWO6LyOpOrUsCpLlW79fBA4A0u8L53py4xlT4YrD4Ycj6bOefVGDzH04NlYc6l7-dP4.QCs3oWDtY4wYO0JLsHYXcujmf8vWqxxl57cJtEEkgTs&dib_tag=se&keywords=xbox%2Bone%2Bcontroller&qid=1728407453&s=videogames&sprefix=xbox%2Bone%2Bcontroller%2Cvideogames%2C89&sr=1-3&th=1)
- On a separate device (Mac)
	- Connected via Bluetooth and ran `system_profiler SPBluetoothDataType` to get the MAC address of the controller
	- Unpair and forget the controller so we can connect it to the desktop
- On the desktop (our Ubuntu 20.04 ROS master)
	- Since the Xbox One S is a newer controller, run `sudo apt remove xboxdrv` (legacy driver)
	- On the desktop, after running `bluetoothctl`, use:
		- `scan on` – ensure the same MAC address pops up
		- `pair <MAC address>` – might not work, which is fine
		- `connect <MAC address` – should work
		- `trust <MAC address>` – should work
	- To verify the controller input config, `sudo apt-get install jstest-gtk` and run the program
		- Run `sudo apt-get install evtest && sudo evtest`, then select the controller from the list to test inputs
- Turtlebot2 testing
	- After running `minimal.launch`, 
### Web Server Setup
- Setup with Apache and launch 