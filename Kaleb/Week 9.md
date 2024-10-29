## <u>10/28/24</u>
### Flipper Zero Side Quest (Day 1)
- Setup
	- Requires Micro SD card for firmware and storage
	- Install Flipper Zero software for a firmware update; connect to Flipper Zero
	- Using the tool is trivial, navigate to "Sub-GHz" and there are two main tools to detect frequencies: "Frequency Detector" (shocker) and "Read RAW"
- Attempts
	- Using Google Lens, the button should be in the 433 MHz range, wireless
	- **Issue:** Detecting with "Read RAW" does not display any signals...research guesses:
		- The door operates on a frequency band outside of the Flipper Zero's legal and freely licensed range (see comments [here](https://www.reddit.com/r/flipperzero/comments/1437s5x/flipper_zero_doesnt_detect_my_transmitter/) and [here](https://www.youtube.com/watch?app=desktop&v=4kwqLR2U1h8))
		- RF interference in which the radio waves are sent through the wall (highly unlikely)
		- The button is somehow not wireless (highly unlikely)
- Solutions
	- [\[ILLEGAL\]](https://www.reddit.com/r/flipperzero/comments/11i06zp/why_you_shouldnt_unlock_restricted_frequencies/) Bypass Flipper Zero regional restrictions using custom firmware
		- Illegal since it may interfere with licensed, military, medical, aircraft, or governmental territory
		- The range on the Flipper Zero goes up to 50 meters
		- If we did break into the illegal band, what would the consequences be?
	- Brute force over 433.92 MHz to decrypt rolling codes and test wireless connectivity, requires a Python script
		- Testing 1024 codes (20+ year-old system), 5x each takes about 4 minutes with the FlipperZero -> 1280 attempts / min
		- Keys can go up to 12 hex digits, aka 256^6 digits...brute forcing each key once would only take 219902325781 minutes (only 418383 years :DDD)!
	- Alternative is to use the physical approach: ESP32 + single motor–not scalable however
- Other
	- RFID duping works haha

## <u>10/29/24</u>

### Flipper Zero Side Quest (Day 2)
- [Unleashed firmware](https://github.com/DarkFlippers/unleashed-firmware) by DarkFlippers bypasses region restriction
- Tested on various university doors, none transmit a signal the Flipper Zero cannot detect
	- **Turns out, the doors on campus are hard-wired to prevent faculty from messing with them.**
	- :(
### Moving Object Detection
- Static object detection is fine after loading a map in, thanks Chester!
	- LiDAR sensor is broken though
- **GOAL:** Use Kinect Camera + LiDAR + Python scripts to implement DATMO.
	- Object identification is easy with YOLOv8, check [src/obj-identification]
	- Would like to use [kostaskonkk/datmo on GitHub](https://github.com/kostaskonkk/datmo)