cmake_minimum_required(VERSION 2.8)
project(UXP1A)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_subdirectory(src/LindaLang)

set(SOURCE_FILES src/main.cpp)
add_executable(UXP1A ${SOURCE_FILES})

target_link_libraries(UXP1A lindalang)