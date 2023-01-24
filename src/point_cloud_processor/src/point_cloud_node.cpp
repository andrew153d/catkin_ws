#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/passthrough.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/filter.h>
#include <cmath>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

ros::Publisher pub;

void cloud_callback(const sensor_msgs::PointCloud2::ConstPtr &msg)
{
// Convert the ROS message to PCL point cloud
    pcl::PointCloud<pcl::PointXYZRGBA> cloud;
    pcl::fromROSMsg(*msg, cloud);

    // Remove NaN points
    std::vector<int> indices;
    pcl::removeNaNFromPointCloud(cloud, cloud, indices);

    // Filter points based on height
    pcl::PassThrough<pcl::PointXYZRGBA> pass;
    pass.setInputCloud (cloud.makeShared());
    pass.setFilterFieldName ("z");
    pass.setFilterLimits (-0.3, 0.3);
    pass.filter (cloud);

    // Convert the filtered point cloud to ROS message
    sensor_msgs::PointCloud2 filtered_msg;
    pcl::toROSMsg(cloud, filtered_msg);
    filtered_msg.header = msg->header;
  pub.publish(filtered_msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "point_cloud_node");
  ros::NodeHandle nh;

  pub = nh.advertise<sensor_msgs::PointCloud2>("output", 1);
  ros::Subscriber cloud_sub = nh.subscribe("/zed2/zed_node/point_cloud/cloud_registered", 1, cloud_callback);

  ros::spin();
  return 0;
}