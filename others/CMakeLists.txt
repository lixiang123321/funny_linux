cmake_minimum_required(VERSION 3.17)
project(process_10)

set(CMAKE_CXX_STANDARD 14)

add_library(PROCESS SHARED process.cpp)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC PROCESS)