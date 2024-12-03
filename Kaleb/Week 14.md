## <u>12/2/24</u>
It's not Sunday, but here we are.
#### Modularity
On the desktop (master), uploading the `kobuki_ws` to a repo at [https://github.com/SaPHaRI-Lab/Turtlebot2-kobuki_ws](https://github.com/SaPHaRI-Lab/Turtlebot2-kobuki_ws).

While doing this initially, I accidentally deleted everything and had to recreate the folder. Sorry Chester.

There exists repos in this repo, so I went into every folder and ran `rm -rf .git` to remove repo data. To work with Git, these are my steps:
- Ensure Git's installed already. If it isn't, run `sudo apt-get install git-all`
- To make a new repo
- Navigate to `kobuki_ws`, then run:
	- `git init`
	- `git remote add origin https://github.com/SaPHaRI-Lab/Turtlebot2-kobuki_ws`
	- `git add .`
	- `echo "# Turtlebot 2 blah blah blah > README.md`
	- If you need a `.gitignore`, use:
		- `vim .gitignore` (then edit)
		- `git rm --cached .` or `git reset`
	- `git commit -m "init"`
- Now the slightly annoying part: **authentication**
	- I'm using [Git Credential Manager](https://github.com/git-ecosystem/git-credential-manager) (GCM) to simplify the auth process.
	- Test if you have .NET by running `dotnet` in the terminal. If not found, I installed [.NET here](https://learn.microsoft.com/en-us/dotnet/core/install/linux-ubuntu-install?tabs=dotnet9&pivots=os-linux-ubuntu-2004) since I dislike `snap`
	- Then follow the [.NET Linux section](https://github.com/git-ecosystem/git-credential-manager/blob/release/docs/install.md#net-tool)–a restart is required!
	- `git-credential-manager configure`
	- Since we're on Linux with a GUI, we'll use secretservice. Run `export GCM_CREDENTIAL_STORE=secretservice`
- Config auth
	- `git config --global user.email <email>`
	- `git config --global user.name <name>`
	- Check with `cat ~/.gitignore`, if need to reset delete the file with `rm`
- Finally, `git push --set-upstream origin master`

### Communication (Day 2)
Switching from HTTP to [MQTT](https://randomnerdtutorials.com/what-is-mqtt-and-how-it-works/) (Message Querying Telemetry Transport).

Was originally going to use the Jetson, but for compatibility and convenience we'll be using the Desktop that's also the master for the Turtlebots.

**Goal:** We need the ESP32 to send messages to the Desktop (our broker) over WiFi via MQTT, then a response is sent both to the ESP32 and a corresponding Turtlebot.

Modified `main.cpp` for the ESP32 again, with comments explaining key parts of the code. 

For the Desktop, we need to use **Mosquitto** for a broker. Install with `sudo apt install mosquitto mosquitto-clients`. It should run automatically, but it can be manually started with `sudo systemctl start mosquitto` and `sudo systemctl enable mosquitto`.

For the Pis, I've created a fork of `minimal.launch` to `minimal_ext.launch` that incorporates the script `turtlebot_mqtt`. It'll be using the **Paho MQTT** client. It's available in [this directory of the repo](https://github.com/SaPHaRI-Lab/Turtlebot2-kobuki_ws/tree/master/src/turtlebot/turtlebot_bringup/scripts) created just earlier. This means we'll need to run `minimal_ext.launch` instead of `minimal.launch` for the Pis moving forward.

**TODO:** Haven't tested for any device. `main.cpp` should work and I'll test it using the mosquitto client on the Desktop. Then, I'll test it on a Turtlebot with a Pi to send a command to move the Turtlebot forward.
## <u>12/3/24</u>
### Communication (Day 3)
for custom, deployed movement of independant bot swarms...use `os.environ[<env var>]` and go by IP

![[Pasted image 20241203101559.png]]

Updated `main.cpp` to subscribe to topic `esp32/motor` and publish to topic `esp32/door`. 

Then, on the Desktop (broker) I subscribed using `mosquitto_sub -h localhost -t esp32/door`. There is a constant stream of beeps every 2 seconds. Success! I tested publishing with `mosquitto_pub -h localhost -t esp32/motor -m "hello"`, and monitored the ESP32's Serial output. Messages are being received. Success!

Cooked `.master.py` to be always run on the broker (Desktop), linked [here](https://github.com/SaPHaRI-Lab/Turtlebot2-kobuki_ws/blob/master/.master.py).

