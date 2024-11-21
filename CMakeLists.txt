cmake_minimum_required(VERSION 3.29)
project(heystl)

set(CMAKE_CXX_STANDARD 20)

add_executable(heystl
        unique_ptr.hpp
        define.hpp
        unique_ptr.cpp)
