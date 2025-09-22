cmake_minimum_required(VERSION 3.8)
project(lidar_imu_sync)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 종속성
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

# 포함 디렉터리
include_directories(
  include
)

# 실행 파일
add_executable(lidar_imu_sync_node
  src/lidar_imu_sync.cpp
)

ament_target_dependencies(lidar_imu_sync_node
  rclcpp
  sensor_msgs
)

# 설치 규칙
install(TARGETS 
  lidar_imu_sync_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include)

install(DIRECTORY 
  launch
  DESTINATION share/${PROJECT_NAME}
)

# 패키지 익스포트
ament_package()
