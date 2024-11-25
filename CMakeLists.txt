cmake_minimum_required(VERSION 3.29)
project(heystl)

set(CMAKE_CXX_STANDARD 20)

# 包含 src 目录
include_directories(${PROJECT_SOURCE_DIR}/src)

# 查找 src 目录下的所有 .cpp 文件
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# 为每个 .cpp 文件创建一个可执行文件
foreach(SOURCE_FILE IN LISTS SOURCES)
    # 获取文件名（不含路径和扩展名）
    get_filename_component(EXECUTABLE_NAME ${SOURCE_FILE} NAME_WE)
    # 添加可执行文件
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILE})
endforeach()
