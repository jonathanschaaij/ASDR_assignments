# ASDfR Assignment 3.2.4: Final Integration

This folder contains the code for the final integration of the Closed Loop Jiwy controller. 

## Steps:

```bash
# Step 1: Source the ROS executables
source install/local_setup.bash

# Step 2: Compile the binaries
colcon build

# Step 3: Launch the ROS nodes using the launchfile
ros2 launch src/multisimlaunch.py
```

After this there should appear windows showing the various image streams. and the jiwy should move to the the brightest point in the image