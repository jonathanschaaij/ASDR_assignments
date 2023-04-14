# ASDfR Assignment 3.2.2:  Code Generation and Xenomai

This folder contains the generated code from Simulink and a method to test it running on xenomai

## Steps:

```bash
# Step 1: Source the ROS executables
source install/local_setup.bash

# Also source the ros2-xenomai nodes
. /home/pi/ros2-xenomai/install/local_setup.sh

# Step 2: Compile the binaries
colcon build
# Maybe build the xenomai files seperately


# Step 3: Launch the ROS nodes using the launchfile
ros2 launch src/multisimlaunch.py

# launch the xenomai executable in a new terminal.
```