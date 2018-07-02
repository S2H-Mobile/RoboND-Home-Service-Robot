#!/bin/sh
xterm  -e "source /opt/ros/kinetic/setup.bash; source /home/nvidia/catkin_ws/devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; roscore" & 
sleep 3
xterm  -e "source /opt/ros/kinetic/setup.bash; source /home/nvidia/catkin_ws/devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/nvidia/catkin_ws/src/RoboND-Home-Service-Robot/World/u_shaped_room.world" & 
sleep 14
xterm  -e "source /opt/ros/kinetic/setup.bash; source /home/nvidia/catkin_ws/devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/nvidia/catkin_ws/src/RoboND-Home-Service-Robot/World/kinect-map.yaml" & 
sleep 5
xterm  -e "source /opt/ros/kinetic/setup.bash; source /home/nvidia/catkin_ws/devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; roslaunch add_markers add_markers_rviz.launch" & 
sleep 5
xterm  -e "source /opt/ros/kinetic/setup.bash; source /home/nvidia/catkin_ws/devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; rosrun add_markers add_markers" & 
sleep 5
xterm  -e "source /opt/ros/kinetic/setup.bash; source /home/nvidia/catkin_ws/devel/setup.bash; export TURTLEBOT_3D_SENSOR=kinect; rosrun pick_objects pick_objects"
