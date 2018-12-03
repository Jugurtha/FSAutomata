cmake_minimum_required(VERSION 3.10)
project(FSAutomata)

set(CMAKE_CXX_STANDARD 14)


include_directories("C:\\Development\\Libraries\\Boost\\boost_1_67_0")
add_executable(FSAutomata main.cpp Word.cpp Word.h State.cpp State.h Transition.cpp Transition.h Transitions.cpp Transitions.h)
