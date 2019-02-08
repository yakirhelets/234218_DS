cmake_minimum_required(VERSION 3.7)
project(Wet2Spring17)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES randtest7.in.debug.cc library2.h student.cpp team.cpp library2.cpp
        RankTree.h GenericUnionFind.h GenericHashTable.h school.cpp school.h)

add_executable(Wet2Spring17 ${SOURCE_FILES})