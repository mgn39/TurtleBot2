## <u>10/31/24</u>

### Moving Object Detection (Day 2)
Goal: Avoid collisions by detecting moving objects, testing [kostaskonkk/datmo on GitHub](https://github.com/kostaskonkk/datmo) on Pi 6

- Configure LiDAR sensor
	- ``
- Following the README on the repo
	- Navigated to `~/kobuki_ws/src`
	- `git clone https://github.com/kostaskonkk/datmo`
	- `cd .. && catkin_make`
	- `cd ~ && source .bashrc` (which also runs `source devel/setup.bash`)
	- Running `roslaunch datmo example.launch bag:=overtakes` gives an error that `player-2` has died, haven't actually configured the LiDAR sensor yet so I'm kinda working backwards
### Door Opening Side Quest (Day 2)
Tech needed:
- [ESP32 x4](https://www.amazon.com/ESP32-32D-WROOM-Module-ESP32-DevKitC-32-Development/dp/B0D6YXWSG8?th=1) (microcontroller)
- [FEETECH Servo FS5106B](https://www.pololu.com/product/3425) 
	- Specs:
		- **Idle Current**: Around 10–15 mA when not under load
		- **Operating Current**: Between **500 mA to 1 A** during normal operation at 6V
		- **Stall Current**: Up to **1.6 A** if it encounters a significant load or is stalledshe
	- Aiming for 60-80 oz/in = 0.8 kg/in
	- The MG996R requires too much power, up to **2.5A**–stall torque at [4.8V is 9.4kg/cm](https://www.jsumo.com/mg996r-servo-motor-digital)
	- FS5103B is too weak (42 oz-in at 6V), SG90 is too weak (40-50 oz/in)
- **\[Problem\]** [5000 mAh LiPo Battery x2](https://www.amazon.com/MakerHawk-5000mAh-Rechargeable-Protection-Insulated/dp/B0D3LP9P96?crid=16XYGOS6LIM95&dib=eyJ2IjoiMSJ9.Lm_MdnWDyMsX0a6elXOCQQi3fKHgxzXCULUQ-5jSASHxneZ33gnLFYyNhKV6XIgRw7G6ot_ehNeC4jS_8w8Vy9XW0uFZzCiaLieNMsfgV0KnYq727GCrzhDruX5Hwr0b3f8a8iDjQMC9PFyNkshDfRg-hcQHolQa5xPo0jZxjusP9rqsGM2Povcbf5u0WpJSpRAdpiXTjiLKOou0b8qCAiSNQzwgvP5_i19R9cG8tfdzaXKLPN4TBOmzfxVtXwzkUPnPYRL_MqAZinH1I5Ujter8FgfWjM2vlANtkltSSmk.Sl8baGx8Go7y17C_9VydZ4bEWghp4vvOq9I0eghXaRg)
	- [Link](https://techexplorations.com/guides/esp32/begin/power/) to powering the ESP32, keeping other circuitry in mind
- Will use a 3D printed lever with some styrofoam, likely will tape a popsicle stick or something