cmake_minimum_required(VERSION 3.7)
project(Wet1Spring17)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES AVL.h school.cpp team.cpp student.cpp library1.cpp randtest2.debug.c)
add_executable(Wet1Spring17 ${SOURCE_FILES})