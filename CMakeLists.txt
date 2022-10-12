cmake_minimum_required(VERSION 3.21)
project(EyeTrackingV2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
        DocTest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG b7c21ec5ceeadb4951b00396fc1e4642dd347e5f # v2.4.9
)
FetchContent_MakeAvailable(DocTest)

set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Gui REQUIRED)

add_library(EyeTrackingV2_impl STATIC
        src/config/General.cpp src/config/General.hpp
        src/config/Helpers.hpp
        src/config/Exceptions.hpp
        src/Config.cpp src/Config.hpp
        src/Exceptions.cpp src/Exceptions.hpp)
target_link_libraries(EyeTrackingV2_impl PUBLIC Qt5::Core Qt5::Gui)

add_executable(EyeTrackingV2 src/main.cpp)
target_link_libraries(EyeTrackingV2 PRIVATE EyeTrackingV2_impl)

enable_testing()

add_executable(EyeTrackingV2_tests test/ConfigReaderTest.cpp test/test_main.cpp)
target_link_libraries(EyeTrackingV2_tests PRIVATE EyeTrackingV2_impl doctest::doctest)
add_test(NAME EyeTrackingV2_tests COMMAND EyeTrackingV2_tests)