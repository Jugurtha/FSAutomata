
cmake_minimum_required(VERSION 3.10)

project(FSAutomata)

set(CMAKE_CXX_STANDARD 14)

add_executable(FSAutomata main.cpp)
target_link_libraries(FSAutomata PRIVATE FSAutomataLib PRIVATE Boost::program_options)#"C:/Development/Libraries/Boost/boost_1_67_0/bin.v2/libs/program_options/build/gcc-5.1.0/release/threading-multi/libboost_program_options-mgw51-mt-x64-1_67.dll")


