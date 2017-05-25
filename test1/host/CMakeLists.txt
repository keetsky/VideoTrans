cmake_minimum_required(VERSION 2.8)
project(host)  
#opencv
find_package(OpenCV 3.0 QUIET)
if(NOT OpenCV_FOUND)
   find_package(OpenCV 2.4.3 QUIET)
   if(NOT OpenCV_FOUND)
      message(FATAL_ERROR "OpenCV > 2.4.3 not found.")
   endif()
endif()

add_definitions(-DGPU -DOPENCV)
include_directories(${OpenCV_INCLUDE_DIRS})
link_libraries( ${OpenCV_LIBS})


add_executable(host SocketServerMat.cpp SocketMatTransmissionServer.cpp)  


