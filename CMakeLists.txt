cmake_minimum_required(VERSION 3.10)
project(task1)
find_package(OpenCV 4 REQUIRED)


add_executable(task1 main.cpp)
target_include_directories(task1 PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(task1 ${OpenCV_LIBS})

set(CMAKE_BUILD_TYPE Debug)