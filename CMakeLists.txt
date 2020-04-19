cmake_minimum_required(VERSION 3.5.0)
project(ros_com_framework)
set (ROS_COM_FRAMEWORK_VERSION_MAJOR 1)
set (ROS_COM_FRAMEWORK_VERSION_MINOR 0)
set (ROS_COM_FRAMEWORK_VERSION_PATCH 0)

## Compile as C++11, supported in ROS Kinetic and newer
set(CMAKE_CXX_STANDARD 11) 

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

SET(ADD_COMPILE_OPT_FLAGS "-g -ldl -rdynamic -fpermissive -std=c++11 -Wwrite-strings") 

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fext-numeric-literals")
add_definitions(${ADD_COMPILE_OPT_FLAGS})

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
 CATKIN_DEPENDS 
 roscpp 
 std_msgs 
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ${catkin_INCLUDE_DIRS}
)

include_directories(
"src/"
"harness/"
)

file(GLOB ros_com_framework_SOURCES "src/*.cpp" "harness/*.cpp")

add_executable(ros_com_interface_harness ${ros_com_framework_SOURCES})
target_link_libraries(ros_com_interface_harness ${catkin_LIBRARIES})
target_compile_definitions(ros_com_interface_harness PRIVATE LINUX)
target_link_libraries(ros_com_interface_harness
  ${CMAKE_DL_LIBS}
)
add_dependencies(ros_com_interface_harness ${catkin_EXPORTED_TARGETS}) 
