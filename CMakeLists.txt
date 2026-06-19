cmake_minimum_required(VERSION 4.2)
project(Programming_Challenge_A)

set(CMAKE_CXX_STANDARD 17)

include_directories(gateware-main)

if (WIN32)

    ADD_DEFINITIONS(-DUNICODE)
    ADD_DEFINITIONS(-D_UNICODE)

    add_executable(Programming_Challenge_A
        gateware-main/Gateware.h 
        main.cpp)

endif(WIN32)


if(UNIX AND NOT APPLE)

    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    target_link_libraries(Programming_Challenge_A ${X11_LIBRARIES})

    add_executable(Programming_Challenge_A 
                   gateware-main/Gateware.h 
                   main.cpp)

endif()

if(APPLE)

    set(CMAKE_CXX_FLAGS 
        "${CMAKE_CXX_FLAGS} -std=c++17 -fmodules -fcxx-modules -Wno-module-import-in-extern-c")
    set(Architecture ${CMAKE_OSX_ARCHITECTURES})

    add_executable(Programming_Challenge_A main.mm)

endif(APPLE)

# Optional Hint:
# GRasterSurface has a Vulkan backend it will automatically use if GVulkanSurface is enabled
# This may provide faster and more consistent screen updates than the default software backends
# See if you can figure out how to enable it