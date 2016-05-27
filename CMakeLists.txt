cmake_minimum_required(VERSION 3.5)
project(2dTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#find_package(GLEW REQUIRED)
#
#find_package(GLM REQUIRED)
#
#find_package(PkgConfig REQUIRED)
#pkg_search_module(GLFW REQUIRED glfw3)
#include_directories(${GLFW_INCLUDE_DIRS})

FIND_PACKAGE(ArrayFire REQUIRED)
INCLUDE_DIRECTORIES(${ArrayFire_INCLUDE_DIRS})

FIND_PACKAGE(OpenCL REQUIRED)
SET(EXTRA_LIBS ${CMAKE_THREAD_LIBS_INIT} ${OpenCL_LIBRARIES})


set(SOURCE_FILES main.cpp)
add_executable(2dTest ${SOURCE_FILES})
target_link_libraries(2dTest ${ArrayFire_LIBRARIES} ${EXTRA_LIBS} ${GLFW_LIBRARIES} ${GLEW_LIBRARY} "-framework OpenGL")
