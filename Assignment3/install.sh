#!/bin/bash
source install/local_setup.bash
rosdep update
rosdep install --from-paths src --ignore-src -r -y
pip3 install netifaces
