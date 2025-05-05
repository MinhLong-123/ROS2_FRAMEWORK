from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cpp_pubsub_turtlesim',
            executable='publisher',
            name='turtlesim_publisher_node',
        ),
        Node(
            package='cpp_pubsub_turtlesim',
            executable='subscriber',
            name='turtlesim_subscriber_node',
        )
    ])