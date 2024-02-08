cmake_minimum_required(VERSION 3.28)
project(tunet)

set(SOURCES
        src/Net.cpp
        src/Net.hpp)

add_library(libtunet STATIC ${SOURCES})
target_include_directories(libtunet PRIVATE src)