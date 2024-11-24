cmake_minimum_required(VERSION 3.29)
project(heystl)

set(CMAKE_CXX_STANDARD 20)


add_executable(unique_ptr
        src/define.hpp
        src/unique_ptr.cpp
        src/unique_ptr.hpp
)
