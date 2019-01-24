
cmake_minimum_required(VERSION 3.10)
project(Catch)

add_library(catch INTERFACE)

target_include_directories(catch INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

