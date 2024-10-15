
### October 15th, 2024

**Objective:** Testing on LiDAR Sensor

**Experiment:** I have no micro usb to usb. So, connect by UART (pins TX, RX).
- Pins on LiDAR Sensor
	- Orange: TX
	- Green: RX
	- Black: VCC_5V
	- White: GND
	- Red: GND_MOTO
	- Blue: CTRL_MOTO
	- Yellow: 5V
![[RPLIDAR A1M8 Cables.png]]
![[Raspberry Pi 4 Pins.jpg]]
But its turn out not working! Dr. Block suggest me try to use micro usb instead. I borrow the micro usb to usb from the HFI lab, its work!
![[Connect LiDAR into Raspberry Pi by micro usb.png]]
Checking the sensor on rviz.