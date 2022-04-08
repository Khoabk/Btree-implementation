cmake_minimum_required(VERSION 3.16)
project(Btree)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Btree
        include/Bnode.h
        include/Btree.h
        include/Elem.h
        include/Queue.h
        src/Bnode.cpp
        src/Btree.cpp
        src/Elem.cpp
        src/main.cpp
        src/Queue.cpp)
