cmake_minimum_required(VERSION 3.31)
project(VulkanSandbox)

set(CMAKE_CXX_STANDARD 26)

add_executable(VulkanSandbox VulkanSandbox/main.cpp)

target_include_directories(VulkanSandbox PUBLIC D:/Development/Projects/C++/Libraries)