# 添加可执行文件
add_executable(server server.cpp)

# 链接 base 库和 POCO 库
target_link_libraries(server PRIVATE PocoNet PocoFoundation)

# 包含头文件目录
target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/base)
