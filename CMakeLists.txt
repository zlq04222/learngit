cmake_minimum_required(VERSION 3.10)  
project(snake)               

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Disable GNU extensions
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)

# Set default build type to Release With Debug Info
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)  
 
add_executable(main main.cpp)  

target_link_libraries(main sfml-graphics sfml-window sfml-system)

# Disable the cache of build type and rely on either the default or the provided one
unset(CMAKE_BUILD_TYPE CACHE)  
# cmake_minimum_required(VERSION 3.10)
 
# # 项目名称和版本
# project(OpenCVProject VERSION 1.0)

# # 设置C++标准
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED True)

# # 查找 OpenCV 包
# find_package(OpenCV REQUIRED)

# # 包含 OpenCV 头文件路径
# include_directories(${OpenCV_INCLUDE_DIRS})

# # 添加可执行文件
# add_executable(main2 src/main1.cpp)

# # 链接 OpenCV 库
# target_link_libraries(main2 ${OpenCV_LIBS})
