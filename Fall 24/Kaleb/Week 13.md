## <u>11/20/24</u>

### The LiDAR Sensor
Created `gmapping_demo2.launch` in `kobuki_ws/src/turtlebot_apps/turtlebot_navigation/launch/`: same process from [[Fall 24/Chester/Experiments/Week 12|Chester]]
```roslaunch
<launch>
  <!-- RPLIDAR node should be launched separately, as you are already doing -->

  <!-- Gmapping -->
  <include file="$(find turtlebot_navigation)/launch/includes/gmapping/gmapping.launch.xml">
    <arg name="scan_topic" value="/scan" /> <!-- Use RPLIDAR scan topic -->
  </include>

  <!-- Move base -->
  <include file="$(find turtlebot_navigation)/launch/includes/move_base.launch.xml"/>

</launch>
```

Now, my `turtleboot` file (all-in-one launch) has been updated to not use the Kinect camera:
```bash
#!/bin/bash

source .bashrc

# 1: turtlebot
roslaunch turtlebot_bringup minimal.launch &
PID_TURTLE=$!

# wait for bringup to complete
sleep 5

# 6: rplidar activation (only works on Pi 5/6)
roslaunch rplidar_ros rplidar_a1.launch &
PID_LIDAR=$!

# 4: rplidar mapping (only works on Pi 5/6)
roslaunch turtlebot_navigation gmapping_demo2.launch &
PID_MAP=$!

# _: doorbell testing (only works on Pi 5 --> will be moved to ESP32)
# sudo -python3 ~/kobuki_ws/src/rpi-rf_receive+launch.py &
# DOORBELL_PID=$!

# On the main desktop, run rviz
```
- Note: Run `rosnode kill -a` to terminate all 3 nodes

We plan to map and autonomously drive the Turtlebot using the LiDAR sensor, without the help of the Kinect camera. In doing so, we reduce the computational overhead required and fix the issue in which the camera has trouble distinguishing between glass and valid space.

In rviz:
- Add `RobotModel` (Turtlebot)
- Add `Laserscan`, set the topic if necessary
- Add `Map`, set to the map topic

The LiDAR sensor builds a limited, initial map but doesn't create a map of the actual space

## <u>11/23/24</u>
### The System (Day 1)
Borrowing Austin's board (ESP32-PICO-MINI-02). The LiPo battery connects and I burned myself. Awesome!

For reference: https://learn.adafruit.com/adafruit-esp32-feather-v2/pinouts
![[Pasted image 20241207013507.png]]

**NOTE: DO NOT USE THE LIPO BATTERY JUST YET UNLESS YOU'D LIKE TO FRY YOUR BOARD**

#### ESP32: Blink
- Install the PlatformIO extension on VSCode
	- Click on the alien icon in the sidebar and create a new project
	- Use Arduino, set the board to the Adafruit ESP32 Feather V2
- In platformio.ini, set `monitor_speed = 115200` $<--$ baud rate
- In `src/main.cpp`, modify to the following code (Blink LED):
```cpp
#include <Arduino.h>

// our board uses GPIO 13
#define LED 13

void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	pinMode(LED, OUTPUT);
}

void loop() {
	// put your main code here, to run repeatedly:
	digitalWrite(LED, HIGH);
	Serial.println("LED is on");
	delay(1000);
	digitalWrite(LED, LOW);
	Serial.println("LED is off");
	delay(1000);
}
```
After building and uploading the code, I'm using the Serial Monitor at the bottom to view the output. The LED onboard blinks, woohoo.

#### Servo Control
The newly modified code to actuate the motor is in the `src` folder of this repo. Slight muse from [here](https://dronebotworkshop.com/esp32-servo/#Servo_Motors).

Add `lib_deps = madhephaestus/ESP32Servo@^3.0.5` in `platformio.ini` to install the ESP32Servo library. It's ok if there's library errors in the IDE, cause it works on the ESP32. Wire ground (GND), 3.3V power (3V), and output signal connection (A1).

#### LiPo Battery
Every time I've connected the LiPo battery I've noticed a funny smell coming from the board. I may have cancer by the numerous times I've sniffed the board, but using some tomfoolery I realized the battery's polarity is reversed. (This means that the black wire from the battery is the power and the red wire is ground when we plug it into the ESP32.)

~~Potential solution: cut the battery wires and resolder to swap...but how then would we charge the battery?~~
- Need to consult Austin or Dr. Block or Andrew if he's alive

#### Radio Receiver
The ESP32 only operates with 3.3V logic, yet the MX-RM-5V receiver operates only on 5V (shocker). Likewise, this goes for the FS1000A transmitter, but we won't be using it since we're working with the doorbell here.

Best option without buying a new receiver is to use a voltage divider with a $1k Omega$ and a $2k Omega$ resistor.
![[Pasted image 20241123212028.png]]
More info and diagram from [here](https://randomnerdtutorials.com/how-to-level-shift-5v-to-3-3v/)

## <u>11/24/24</u>

### The System (Day 2)
#### LiPo Battery
Used a flathead to switch the polarity on the JRT connector itself with the help of Austin. Also learned that the LiPo battery is charged when the ESP32 is charged by the USB-C port...
#### Radio Receiver
Trying the voltage divider with this breadboard configuration and moved the servo wiring as well:
![[Pasted image 20241124212426.png]]
I needed a refresher on [reading resistors](https://developer.wildernesslabs.co/Hardware/Tutorials/Electronics/Part4/Reading_Resistors/)–the end color of the resistor is almost always gold or silver.

Yeah we'll need to order a 3.3V receiver, the 5V one simply doesn't work since it requires more power.
### Web Server
Web server being hosted from the ESP32–will likely change from HTTP to a different protocol/port since we won't need a GUI later). [Here](https://randomnerdtutorials.com/esp32-web-server-arduino-ide/)'s a good resource for some high-level interfacing.

It kinda works, it's buggy. Code w/ comments are in the main.cpp file.