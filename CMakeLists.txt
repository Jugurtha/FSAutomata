cmake_minimum_required(VERSION 3.10)
project(FSAutomata)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

add_executable(FSAutomata main.cpp Word.cpp Word.h State.cpp State.h Transition.cpp Transition.h Transitions.cpp Transitions.h Alphabet.h Alphabet.cpp States.cpp States.h Automaton.cpp Automaton.h)
