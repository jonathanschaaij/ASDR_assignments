from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="image_tools",
            executable="cam2image",
            name='camera',
            parameters=[{"depth": 1}, {"history": "keep_last"}],
        ),
        Node(
            package='jiwy_simulator',
            executable='jiwy_simulator',
            name='jiwySimulator'
        ),
        Node(
            package='brightness_pkg',
            executable='lightposition_node',
            name='lightpositionnode',
            arguments=[{"inputimage": "moving_camera_output"}]
        ),
        Node(
            package='closed_loop',
            executable='controller',
            name='losed_loop_controller',
        ),


        # Visualise the outputs
        Node(
            package='image_tools',
            executable='showimage',
            name='originalImage'
        ),
        Node(
            package='image_tools',
            executable='showimage',
            name='simulatorImage',
            arguments=["image:=/moving_camera_output"]
        ),
        Node(
            package='image_tools',
            executable='showimage',
            name='grayImage',
            arguments=["image:=/grayImage"]
        ),
        Node(
            package='image_tools',
            executable='showimage',
            name='binaryImage',
            arguments=["image:=/binaryImage"]
        ),
    ])