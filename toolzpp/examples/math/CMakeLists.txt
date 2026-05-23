cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(mathfn-gra)

add_executable(mathfn-gra WIN32 main.cpp)

target_link_libraries(mathfn-gra PRIVATE easyx)

target_include_directories(mathfn-gra PRIVATE E:/Codes/libs/std++/include)