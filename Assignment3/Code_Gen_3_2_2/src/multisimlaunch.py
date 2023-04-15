from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="jiwy_simulator",
            executable="jiwy_tester",
            name='Manual_Setpoint',
        ),
        Node(
            package="ros2-xenomai",
            executable="talker",
            name='Setpoint_to_XDDP',
            parameters=[{"topicName": "sendData"}, {"xddpPort": 10}],
        ),
    ])