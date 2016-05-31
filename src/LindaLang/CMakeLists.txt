cmake_minimum_required(VERSION 2.8)
project(lindalang)
set(CMAKE_BUILD_TYPE Debug)

find_package (Boost COMPONENTS system filesystem serialization REQUIRED)
include_directories(.
        ${Boost_INCLUDE_DIRS})

add_library(lindalang STATIC
        Linda.cpp Tuple.cpp Tuple.h TuplePattern.cpp TuplePattern.h TupleValue.cpp TupleValue.h Pipe.cpp Pipe.h TuplePatternValue.cpp TuplePatternValue.h Conditions.h TupleValVisitors.cpp TupleValVisitors.h ConditionVis.h Message.cpp Message.h)


set(SOURCES
        src/Linda.cpp
        )


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -pthread")

target_link_libraries(lindalang ${PROJECT_LINK_LIBS} ${Boost_SERIALIZATION_LIBRARY})



