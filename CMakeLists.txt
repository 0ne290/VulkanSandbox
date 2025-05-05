cmake_minimum_required(VERSION 3.31)
project(vulkan_sandbox)

set(CMAKE_CXX_STANDARD 26)

find_package(Vulkan REQUIRED)

add_executable(vulkan_sandbox sources/main.cpp
        sources/logging.cpp
        headers/logging.h
        headers/json.h
        sources/json.cpp
)

target_include_directories(vulkan_sandbox PUBLIC D:/Development/Projects/C++/libraries)
target_include_directories(vulkan_sandbox PUBLIC headers)
target_link_libraries(vulkan_sandbox PUBLIC Vulkan::Vulkan)