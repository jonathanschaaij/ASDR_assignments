# ASDfR Assignment 3.2.1

This folder contains the code for subassignment 3.2.1 which is to do the closed loop control on the RaspberryPi.
It is supposed to be a recreation of assignment 1.2.3 but then on the Pi.
Since we are a CBL group we never did assignment 1.2.3 therefor we have to implement it now. 

## Steps:

```bash
# Step 1: Source the ROS executables
source install/local_setup.bash

# Step 2: Compile the binaries
colcon build

# Step 3: Launch the ROS nodes using the launchfile
ros2 launch src/multisimlaunch.py
```

After this there should appear windows showing the various image streams.