
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
Checking the sensor on rviz by sunning this `roslaunch rplidar_ros view_rplidar_a1.launch` on both pink computer and Raspberry Pi then get both error! (different error).

**Result:** Cannot use in the rviz yet.


### October 16th, 2024

**Objective:** Testing the doorbell

**Experiment:** After I failed to use the lidar sensor from yesterday. So, I move on into doorbell instead for today.
![[RF Receiver MX-RM-5V.png]]
- RF Receiver pins (Start from left)
	- 1st: GND - Connect to a ground in pin 6th
	- 2nd: DATA (Signal) - Connect to a GPIO pin 11th
	- 3rd: ANT (Antenna) - Skip
	- 4th: 5V power - Connect to a 5V in pin 4th

After all cables are connected. To setup the software before use the RF receiver.
- Install WiringPi, which will help control GPIO pins
	- `sudo apt install wiringpi`
- Install 433Utils
	- `cd kobuki_ws/src`
	- `git clone https://github.com/ninjablocks/433Utils.git`
	- `cd 433Utils/RPi_utils`
	- `make`

But I cannot run `make` I get some error (RCSwitch library is missing). I try to fix by
- Install the RCSwitch manually
	- `cd kobuki_ws/src/433Utils/RPi_utils`
	- `git clone https://github.com/sui77/rc-switch.git`
	- `make`

I still get the error but different one so this one is wiringPi library is missing (So confused due to I just install it). So, I fix it by
- `git clone https://github.com/WiringPi/WiringPi.git`
- `cd WiringPi`
- `./build`

I cannot build this package so I try to use another package instead.
- Install pigpio
	- `wget https://github.com/joan2937/pigpio/archive/master.zip`
	- `unzip master.zip`
	- `cd pigpio-master`
	- `make`
	- `sudo make install`
- To start the pigpio
	- sudo systemctl enable pigpiod

ERROR! pigpoid is not exist!

I try in another way. So, with new connection.
- RF Receiver pins (Start from left) | Picture on the above
	- 1st: GND - Connect to a ground in pin 6th
	- 2nd: DATA (Signal) - Connect to a GPIO pin 11th/13th
	- 3rd: ANT (Antenna) - Skip
	- 4th: 5V power - Connect to a 5V in pin 4th
- Open terminal
	- `sudo apt-get install python3-pip`
	- `sudp pip3 install rpi-rf`
	- `nano rpi-rf_receive.py`
```
#!/usr/bin/env python3

import argparse
import signal
import sys
import time
import logging

from rpi_rf import RFDevice

rfdevice = None

# pylint: disable=unused-argument
def exithandler(signal, frame):
    rfdevice.cleanup()
    sys.exit(0)

logging.basicConfig(level=logging.INFO, datefmt='%Y-%m-%d %H:%M:%S',
                    format='%(asctime)-15s - [%(levelname)s] %(module)s: %(message)s', )
  
parser = argparse.ArgumentParser(description='Receives a decimal code via a 433/315MHz GPIO device')
parser.add_argument('-g', dest='gpio', type=int, default=27,
                    help="GPIO pin (Default: 27)")
args = parser.parse_args()
 
signal.signal(signal.SIGINT, exithandler)
rfdevice = RFDevice(args.gpio)
rfdevice.enable_rx()
timestamp = None
logging.info("Listening for codes on GPIO " + str(args.gpio))
while True:
    if rfdevice.rx_code_timestamp != timestamp:
        timestamp = rfdevice.rx_code_timestamp
        logging.info(str(rfdevice.rx_code) +
                     " [pulselength " + str(rfdevice.rx_pulselength) +
                     ", protocol " + str(rfdevice.rx_proto) + "]")
    time.sleep(0.01)
rfdevice.cleanup()
```
- After finished the setup try the code
	- `sudo python3 rpi-rf_receive.py`
- Press the doorbell button
	- receive the signal
![[Received RF signal.png]]
Including the date and time to record; need to figure it out how to record this!

**Result:** Can received the signal.


### October 17th, 2024

**Objective:** 

