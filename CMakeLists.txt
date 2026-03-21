cmake_minimum_required(VERSION 4.1)
project(LABA2)

set(CMAKE_CXX_STANDARD 20)

add_executable(LABA2 main.cpp
        dynamicArray.h
        linkedList.h
        sequence.h
        arraySequence.h
        listSequence.h
        mutableArraySequence.h
        immutableArraySequence.h
        mutableListSequence.h
        immutableListSequence.h)
