#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <iostream>
#include <chrono>
#include <thread>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 6.5;
  goal.target_pose.pose.position.y = 3.5;
  goal.target_pose.pose.orientation.w = 2.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pick up goal (6.5, 3.5, 2.0)");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Successfully reached pick up zone at (6.5, 3.5, 2.0)");
  else
   ROS_INFO("Failed to reach pick up zone at (6.5, 3.5, 2.0)");

  ROS_INFO("Waiting ...");
  std::chrono::seconds dura(5);
  std::this_thread::sleep_for(dura);
  ROS_INFO("Waited for 5 seconds.");

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 4.0;
  goal.target_pose.pose.position.y = -5.0;
  goal.target_pose.pose.orientation.w = 4.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off goal (4.0, -5.0, 4.0)");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Successfully reached drop off zone at (4.0, -5.0, 4.0)");
  else
   ROS_INFO("Failed to reach drop off zone at (4.0, -5.0, 4.0)");

  return 0;
}
