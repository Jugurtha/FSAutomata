
cmake_minimum_required(VERSION 3.10)

project(FSAutomataLib)

set(CMAKE_CXX_STANDARD 14)

add_library(FSAutomataLib STATIC Word.cpp Word.h State.cpp State.h Transition.cpp Transition.h Transitions.cpp Transitions.h Alphabet.h Alphabet.cpp States.cpp States.h Automaton.cpp Automaton.h)
target_include_directories(FSAutomataLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

