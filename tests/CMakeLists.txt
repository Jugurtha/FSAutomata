
cmake_minimum_required(VERSION 3.10)

project(tests)

#Tests
add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE FSAutomataLib catch)


