from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
         Node(
            package="image_tools",
            executable="cam2image",
            name='camera',
            parameters=[{"depth": 1}, {"history": "keep_last"}]
        ),
        Node(
            package='brightness_pkg',
            executable='lightposition_node',
            name='lightpositionnode'
        ),
        # Node(
        #     package='image_tools',
        #     executable='showimage',
        #     name='originalImage'
        # ),
        # Node(
        #     package='image_tools',
        #     executable='showimage',
        #     name='grayImage',
        #    arguments=["image:=/grayImage"]
        # ),
        Node(
            package='image_tools',
            executable='showimage',
            name='binaryImage',
            arguments=["image:=/binaryImage"]
        ),
        Node(
            package='jiwy_simulator',
            executable='jiwy_simulator',
            name='jiwySimulator'
        ),
        Node(
            package='jiwy_simulator',
            executable='jiwy_tester',
            name='jiwyTester'
        ),
    ])