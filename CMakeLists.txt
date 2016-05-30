cmake_minimum_required(VERSION 2.8)
project(UXP1A)

include_directories(.
                    src/LindaLang
                    src/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_subdirectory(src/LindaLang)
add_subdirectory(test)

set(SOURCE_FILES src/main.cpp src/server/TupleSpace.cpp src/server/TupleSpace.h src/server/Server.cpp src/server/Server.h src/client/Client.cpp src/client/Client.h)
add_executable(UXP1A ${SOURCE_FILES})

target_link_libraries(UXP1A lindalang)


enable_testing ()
add_test (NAME MyTest COMMAND Test)
