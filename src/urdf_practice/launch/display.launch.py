import launch
from launch.substitutions import Command, LaunchConfiguration
import launch_ros
from launch_ros.actions import Node
import os
def generate_launch_description():
    # Get the path to the package
    pkg_path = launch_ros.substitutions.FindPackageShare(package='urdf_practice').find('urdf_practice')
    # Get the path to the urdf file
    urdf_file = os.path.join(pkg_path, 'urdf/model.urdf')
    # Get the path to the rviz config file
    rviz_config_file = os.path.join(pkg_path, 'config/config.rviz')
    print("URDF path: ", urdf_file)
    # Read the URDF file
    with open(urdf_file, 'r') as infp:
        robot_description = infp.read()
    params = { 'robot_description': robot_description }
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[params],
        arguments=[urdf_file]
    )
    joint_state_publisher_node = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        name='joint_state_publisher',
        parameters=[params],    
        arguments=[urdf_file]
    )
    joint_state_publisher_gui_node = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        name='joint_state_publisher_gui',
        arguments=[urdf_file],  
        condition = launch.conditions.IfCondition(
            LaunchConfiguration('gui')) # This condition is used to check if the GUI should be launched
    )
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', rviz_config_file]
    )
    return launch.LaunchDescription([
        # Declare the launch argument for the GUI
        launch.actions.DeclareLaunchArgument(name='gui', default_value='True', description='Launch the GUI'),
        robot_state_publisher_node,
        joint_state_publisher_node,
        joint_state_publisher_gui_node,
        rviz_node
    ])

