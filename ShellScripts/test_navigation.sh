#!/bin/sh
xterm  -e "source /opt/ros/kinetic/setup.bash; source /home/nvidia/catkin_ws/devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; roscore" & 
sleep 3
xterm  -e "source /opt/ros/kinetic/setup.bash; source /home/nvidia/catkin_ws/devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/nvidia/catkin_ws/src/RoboND-Home-Service-Robot/World/u_shaped_room.world" & 
sleep 14
xterm  -e "source /opt/ros/kinetic/setup.bash; source /home/nvidia/catkin_ws/devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/nvidia/catkin_ws/src/RoboND-Home-Service-Robot/World/kinect-map.yaml" & 
sleep 6
xterm  -e "source /opt/ros/kinetic/setup.bash; source /home/nvidia/catkin_ws/devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; roslaunch turtlebot_rviz_launchers view_navigation.launch"
