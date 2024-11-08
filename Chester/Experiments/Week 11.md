
### November 5th, 2024

**Objective:** Reduce noise

**Experiment:** I create new code that including the filter (Target code: 15205443, Target pulse length: 177, 178, 179, 180, and Target protocol: 1).
```
#!/usr/bin/env python3

import argparse
import signal
import sys
import time
import logging
from rpi_rf import RFDevice

rfdevice = None

# Desired signal parameters
TARGET_CODE = 15205443
TARGET_PULSELENGTH = [177, 178, 179, 180]
TARGET_PROTOCOL = 1

# Exit handler to clean up GPIO
def exithandler(signal, frame):
    rfdevice.cleanup()
    sys.exit(0)

# Set up logging
logging.basicConfig(level=logging.INFO, datefmt='%Y-%m-%d %H:%M:%S',
                    format='%(asctime)-15s - [%(levelname)s] %(module)s: %(message)s', )

# Parse GPIO argument
parser = argparse.ArgumentParser(description='Receives a decimal code via a 433/315MHz GPIO device')
parser.add_argument('-g', dest='gpio', type=int, default=27,
                    help="GPIO pin (Default: 27)")
args = parser.parse_args()

# Set up RF device
signal.signal(signal.SIGINT, exithandler)
rfdevice = RFDevice(args.gpio)
rfdevice.enable_rx()
timestamp = None
logging.info("Listening for codes on GPIO " + str(args.gpio))

# Main loop to filter and respond to target signal
while True:
    if rfdevice.rx_code_timestamp != timestamp:
        timesta
        # Check if the received code matches the target signal parameters
        if (rfdevice.rx_code == TARGET_CODE and 
            rfdevice.rx_pulselength in TARGET_PULSELENGTH and 
            rfdevice.rx_proto == TARGET_PROTOCOL):
            logging.info(f"Target signal received: {rfdevice.rx_code} "
                         f"[pulselength {rfdevice.rx_pulselength}, protocol {rfdevice.rx_proto}]")
            # Add your desired action here for when the target signal is received
        else:
            logging.debug(f"Ignoring unwanted signal: {rfdevice.rx_code} "
                          f"[pulselength {rfdevice.rx_pulselength}, protocol {rfdevice.rx_proto}]")
    time.sleep(0.01)

rfdevice.cleanup()
```

**Result:** It worked!


### November 7th, 2024

**Objective:**

**Experiment:** 