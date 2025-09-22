#include "lidar_imu_sync/lidar_imu_sync.hpp"

LidarImuSyncNode::LidarImuSyncNode() : Node("lidar_imu_sync_node")
{
  synced_lidar_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/synced/velodyne_points", 10);
  synced_imu_pub_ = this->create_publisher<sensor_msgs::msg::Imu>("/synced/imu/data", 10);

  imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
      "/imu/data", 10,
      std::bind(&LidarImuSyncNode::imuCallback, this, std::placeholders::_1));

  lidar_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "/velodyne_points", 10,
      std::bind(&LidarImuSyncNode::lidarCallback, this, std::placeholders::_1));
}

void LidarImuSyncNode::imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg)
{
  imu = *msg;
  have_imu_ = true;
}

void LidarImuSyncNode::lidarCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  lidar = *msg;
  have_lidar_ = true;
}

void LidarImuSyncNode::publishSync()
{
  if (!have_imu_ || !have_lidar_)
    return;
  auto time_stamp = this->get_clock()->now();
  imu.header.stamp = time_stamp;
  lidar.header.stamp = time_stamp;
  synced_imu_pub_->publish(imu);
  synced_lidar_pub_->publish(lidar);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<LidarImuSyncNode>();

  rclcpp::Rate rate(10); // 10 Hz

  while (rclcpp::ok())
  {
    rclcpp::spin_some(node);
    node->publishSync();
    rate.sleep();
  }

  rclcpp::shutdown();
  return 0;
}
