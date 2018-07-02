#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate r(1);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    // Set the marker shape to a cube
    uint32_t shape = visualization_msgs::Marker::CUBE;

    // create the marker
    visualization_msgs::Marker marker;

    // Set the frame ID and timestamp
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Publish the marker at the pickup zone
    marker.pose.position.x = 6.5;
    marker.pose.position.y = 3.5;
    marker.pose.position.z = 2.0;
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

    marker.lifetime = ros::Duration();

    // Publish the marker at pick up zone
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    ROS_INFO("Publish marker at pick up zone.");
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);

    // Pause 5 seconds
    ROS_INFO("Waiting 5 seconds ...");
    sleep(5);

    // Publish hiding marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    ROS_INFO("Publish hiding marker.");
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);

    // Pause 5 seconds
    ROS_INFO("Waiting 5 seconds ...");
    sleep(5);

    // Set marker data for drop off zone
    marker.pose.position.x  = 4.0;
    marker.pose.position.y = -5.0;
    marker.pose.position.z = 4.0;

    // Publish the marker at drop off zone
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    ROS_INFO("Publish marker at drop off zone.");
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);

    // Pause 5 seconds
    ROS_INFO("Waiting 5 seconds ...");
    sleep(5);
}
