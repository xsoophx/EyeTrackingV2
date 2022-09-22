cmake_minimum_required(VERSION 3.21)
project(EyeTrackingV2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(EyeTrackingV2 src/main.cpp)
target_link_libraries(EyeTrackingV2 PRIVATE Qt5::Core)