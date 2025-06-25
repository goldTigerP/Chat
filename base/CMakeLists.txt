
file(GLOB_RECURSE BASE_SOURCES "*.cpp")
file(GLOB_RECURSE BASE_HEADERS "*.h")

# 添加动态库
add_library(base SHARED ${BASE_SOURCES} ${BASE_HEADERS})

# 包含头文件目录
target_include_directories(base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})