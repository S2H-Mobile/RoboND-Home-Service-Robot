#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <visualization_msgs/Marker.h>

ros::Publisher marker_pub;
visualization_msgs::Marker marker;

const double pick_up_pose[3] = {6.5, 3.5, 0.0};
const double drop_off_pose[3] = {4.0, -5.0, 0.0};

void publish_marker()
{
  while (marker_pub.getNumSubscribers() < 1)
  {
    if (!ros::ok())
    {
      return;
    }
    ROS_WARN_ONCE("Please create a subscriber to the marker.");
    sleep(1);
  }
  ROS_INFO_STREAM("Publishing marker at x=" << marker.pose.position.x << ", y=" << marker.pose.position.y);
  marker_pub.publish(marker);
}

void odom_callback(const nav_msgs::Odometry::ConstPtr &msg)
{
  // current pose of the robot from odometry
  const float robot_x = msg -> pose.pose.position.x;
  const float robot_y = msg -> pose.pose.position.y;

  // Define a range delta
  const double delta = 0.4;

  // Robot is in zone if inside box of size delta x delta
  const bool is_in_pickup_zone = abs(robot_x - pick_up_pose[0]) < delta && abs(robot_y - pick_up_pose[1]) < delta;
  const bool is_in_dropoff_zone = abs(robot_x - drop_off_pose[0]) < delta && abs(robot_y - drop_off_pose[1]) < delta;

  if (is_in_pickup_zone)
  {
    // Pause 5 seconds
    ROS_INFO("Waiting 5 seconds ...");
    sleep(5);

    // Publish hiding marker
    ROS_INFO("Publish hiding marker.");
    marker.action = visualization_msgs::Marker::DELETE;
    publish_marker();

  } else if (is_in_dropoff_zone)
  {
    // Set marker data for drop off
    marker.pose.position.x = drop_off_pose[0];
    marker.pose.position.y = drop_off_pose[1];
    marker.pose.position.z = drop_off_pose[2];
    marker.action = visualization_msgs::Marker::ADD;
    publish_marker();
  }
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
    
  // Create publisher for the marker 
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Create subscriber to the odom topic 
  ros::Subscriber subscriber_odom = n.subscribe("odom", 1000, &odom_callback);

  // Set marker data
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "basic_shapes";
  marker.id = 0;
  marker.type = visualization_msgs::Marker::CUBE;
  marker.lifetime = ros::Duration();

  // Set the orientation
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale
  marker.scale.x = 0.45;
  marker.scale.y = 0.45;
  marker.scale.z = 0.45;

  // Set the color
  marker.color.r = 0.0f;
  marker.color.g = 0.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;

  // Set pick up location
  marker.pose.position.x = pick_up_pose[0];
  marker.pose.position.y = pick_up_pose[1];
  marker.pose.position.z = pick_up_pose[2];

  // Publish the marker at pick up location
  marker.action = visualization_msgs::Marker::ADD;
  publish_marker();

  // Listen to odom messages
  ROS_INFO_STREAM("Start listening for odom messages.");
  ros::Duration pause_duration(0.1);
  while (ros::ok())
  {
    ros::spinOnce();
    pause_duration.sleep();
  }
  // ros::spin();
}
