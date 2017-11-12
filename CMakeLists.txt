cmake_minimum_required(VERSION 3.8)
project(rtmidi_hello)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(rtmidi_hello ${SOURCE_FILES})

# link rtmidi
target_link_libraries (rtmidi_hello rtmidi)

# link openal
target_link_libraries (rtmidi_hello openal)
