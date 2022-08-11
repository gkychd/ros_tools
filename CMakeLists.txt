cmake_minimum_required(VERSION 3.0.2)
project(txt_to_rosmsg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  sensor_msgs
  nav_msgs
  std_msgs
  message_generation
)

 add_message_files(
   FILES
   cam_data.msg
 )


 generate_messages(
   DEPENDENCIES
   sensor_msgs
   std_msgs
   nav_msgs
   
 )


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES txt_to_rosmsg
  CATKIN_DEPENDS
  roscpp 
  rospy 
  sensor_msgs 
  std_msgs
  nav_msgs
  message_runtime
  message_generation
  #DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(txt_to_rosmsg src/txt_to_rosmsg.cpp)
add_executable(txt_to_rosmsg2 src/txt_to_rosmsg2.cpp)
add_executable(txt_to_rosmsg3 src/txt_to_rosmsg3.cpp)

target_link_libraries(txt_to_rosmsg
  ${catkin_LIBRARIES}
)

target_link_libraries(txt_to_rosmsg2
  ${catkin_LIBRARIES}
)

target_link_libraries(txt_to_rosmsg3
  ${catkin_LIBRARIES}
)
