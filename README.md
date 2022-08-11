# ros_tools
###txt_to_rostopic

~~~mkdir -p catkin_ws/src
cd catkin_ws/src
git clone https://github.com/gkychd/ros_tools.git
cd ..
catkin_make
source devel/setup.bash
rosrun txt_to_rostopic txt_to_rostopic
