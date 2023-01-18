#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/filter.h>
#include <cmath>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
void cloud_callback(const sensor_msgs::PointCloud2::ConstPtr &msg)
{

  // Convert the ROS message to a PCL point cloud
  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
  pcl::fromROSMsg(*msg, *cloud);
  std::vector<int> indices;
  pcl::removeNaNFromPointCloud(*cloud, *cloud, indices);
  
  //printf("\nPoint 0: X: %f, Y: %f, Z: %F, R: %lf", cloud->points[0].x, cloud->points[0].y, cloud->points[0].z);
  for(auto point: cloud->points){
    std::cout << point << std::endl;
  }
  //std::cout << cloud->points[0] << std::endl;
   //std::cout << cloud->points[0];

  //for (int i = 0; i < msg->fields.size(); i++)
  //{
    //std::cout << msg->fields[i] << std::endl;
  //}
  //const float *cloudData = reinterpret_cast<const float *>(&msg->data[0]);
  //int counter = 0;

  //std::cout << cloudData[0];

  /*for(int i = 0; i< msg->data.size(); i++){
    uint32_t p = msg->data[i];
    if(counter>10){
      break;
    }
    if(!isnan(p)){
      std::cout << "x: " << p << std::endl;
      counter++;
    }
  }*/

  // Print the number of points in the point cloud
  // std::cout << "Point cloud has " << cloud->points.size() << " poistd:nts." << :endl;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "point_cloud_node");
  ros::NodeHandle nh;

  ros::Subscriber cloud_sub = nh.subscribe("/zed2/zed_node/point_cloud/cloud_registered", 1, cloud_callback);

  ros::spin();
  return 0;
}