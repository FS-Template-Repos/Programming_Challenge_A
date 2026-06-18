cmake_minimum_required(VERSION 4.2)
project(Programming_Challenge_A)

set(CMAKE_CXX_STANDARD 17)

include_directories(gateware-main)

add_executable(Programming_Challenge_A
        gateware-main/Gateware.h
        main.cpp)

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    target_link_libraries(Programming_Challenge_A ${X11_LIBRARIES})
endif()

# Optional Hint:
# GRasterSurface has a Vulkan backend it will automatically use if GVulkanSurface is enabled
# This may provide faster and more consistent screen updates than the default software backends
# See if you can figure out how to enable it