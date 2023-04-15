# ASDfR Assignment 3.2.2:  Code Generation and Xenomai

This folder contains the generated code from 20-Sim and a method to test it running on xenomai

## Steps:

```bash
# Compile the binaries
colcon build

# Compile the xenomai files seperately
cd xenomai-ros2-framework
cmake .. && make

# Step 3: Launch the ROS nodes using the launchfile
ros2 launch src/multisimlaunch.py

# launch the xenomai executable in a new terminal.
sudo ./xenomai-ros2-framework
```