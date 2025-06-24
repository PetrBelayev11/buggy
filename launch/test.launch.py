from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    pup = Node(
        name='pup',
        namespace='',
        package='buggy',
        executable='pub',
        output='screen',
    )
    
    cub = Node(
        name='cub',
        namespace='',
        package='buggy',
        executable='sub',
        output='screen',
    )
    
    ld = LaunchDescription()
    ld.add_action(pup)
    ld.add_action(cub)
    return ld