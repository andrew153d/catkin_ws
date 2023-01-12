#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include "cloud.h"
void cloud_callback(const sensor_msgs::PointCloud2::ConstPtr& cloud_msg)
{
    using namespace std;
    std::cout << "got message" << std::endl;
    std::cout << cloud_msg->height << ' ' << cloud_msg->width << std::endl;
    cout << "hello" << endl;
    cloud Point_Cloud;
    Point_Cloud.width = cloud_msg->width;
    Point_Cloud.height = cloud_msg->height;
  // Process the point cloud data here
  // cloud_msg is a sensor_msgs/PointCloud2 message
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "point_cloud_node");
  ros::NodeHandle nh;

  ros::Subscriber cloud_sub = nh.subscribe("/zed2/zed_node/point_cloud/cloud_registered", 1, cloud_callback);

  ros::spin();
  return 0;
}