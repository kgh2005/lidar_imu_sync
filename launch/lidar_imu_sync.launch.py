from launch import LaunchDescription
from launch_ros.actions import Node
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.actions import IncludeLaunchDescription
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    lidar_imu_sync = Node(
        package='lidar_imu_sync',
        executable='lidar_imu_sync_node',
        name='lidar_imu_sync',
        output='screen'
    )
    
    velodyne_launch = os.path.join(
        get_package_share_directory('velodyne'),
        'launch',
        'velodyne-all-nodes-VLP16-launch.py'
    )

    imu_launch = os.path.join(
        get_package_share_directory('ebimu_pkg'),
        'launch',
        'ebimu_pkg.launch.py'
    )
    return LaunchDescription([
        lidar_imu_sync,
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(velodyne_launch)
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(imu_launch)
        )
    ])
