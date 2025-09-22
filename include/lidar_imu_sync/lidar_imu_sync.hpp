#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

class LidarImuSyncNode : public rclcpp::Node
{
public:
  LidarImuSyncNode();

  // ===== Pub =====
  void publishSync();

private:

  bool have_imu_ = false, have_lidar_ = false;

  sensor_msgs::msg::Imu imu;
  sensor_msgs::msg::PointCloud2 lidar;

  // ===== ROS 통신 =====
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr synced_lidar_pub_;
  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr synced_imu_pub_;
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr lidar_sub_;

  // ===== Callback =====
  void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg);
  void lidarCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
};
