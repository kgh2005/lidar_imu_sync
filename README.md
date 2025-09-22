# lidar_imu_sync
**lidar_imu_sync** package
It was created to synchronize the IMU and LiDAR.
Make sure the IMU and point-cloud publisher packages are fully built and configured before using this package.

## Development Environment

| Component   | Version          |
|-------------|------------------|
| **OS**      | Ubuntu 22.04     |
| **ROS**     | Humble Hawksbill    |
| **IMU**     | EBIMU    |
| **Lidar**     | Velodyne    |

## Build

```bash
colcon build --packages-select lidar_imu_sync --symlink-install
```

## Run

```bash
ros2 launch lidar_imu_sync lidar_imu_sync.launch.py 
```
