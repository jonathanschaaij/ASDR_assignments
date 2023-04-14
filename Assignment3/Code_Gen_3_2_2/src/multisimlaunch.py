from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="jiwy-simulator",
            executable="jiwy-tester",
            name='Manual_Setpoint',
        ),
        Node(
            package="ros2-xenomai",
            executable="talker",
            name='Setpoint_to_XDDP',
            parameters=[{"topicName": "sendData"}, {"xddpPort": 10}],
        ),
        # Node(
        #     package="image_tools",
        #     executable="cam2image",
        #     name='camera',
        #     parameters=[{"depth": 1}, {"history": "keep_last"}],
        # ),
        # Node(
        #     package='brightness_pkg',
        #     executable='lightposition_node',
        #     name='lightpositionnode',
        #     arguments=[{"inputimage": "image"}] 
        # ),
        # Node(
        #     package='closed_loop',
        #     executable='controller',
        #     name='losed_loop_controller',
        # ),

        # # Visualise the outputs
        # Node(
        #     package='image_tools',
        #     executable='showimage',
        #     name='originalImage'
        # ),
        # Node(
        #     package='image_tools',
        #     executable='showimage',
        #     name='grayImage',
        #     arguments=["image:=/grayImage"]
        # ),
        # Node(
        #     package='image_tools',
        #     executable='showimage',
        #     name='binaryImage',
        #     arguments=["image:=/binaryImage"]
        # ),
    ])