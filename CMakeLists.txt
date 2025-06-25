cmake_minimum_required(VERSION 3.10)
project(ChatApp)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加子目录
# add_subdirectory(base)
add_subdirectory(server)
add_subdirectory(client)