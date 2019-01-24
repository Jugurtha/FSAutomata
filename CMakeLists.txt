
cmake_minimum_required(VERSION 3.12)

project(FSA)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS program_options REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

add_subdirectory(src/FSAutomataLib)
add_subdirectory(src/FSAutomata)
add_subdirectory(externals/catch)
add_subdirectory(tests)


