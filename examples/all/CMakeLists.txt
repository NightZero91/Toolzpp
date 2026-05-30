cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(toolzpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(run main.cpp)