cmake_minimum_required(VERSION 3.22.1)

PROJECT(miniture_STL CXX)

aux_source_directory(./ DIR_SRCS)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

ADD_SUBDIRECTORY(./test)

add_subdirectory(./src)

add_executable(miniture_STL ${DIR_SRCS})

target_link_libraries(miniture_STL Lib_test)

target_link_libraries(miniture_STL Lib_src)

message(STATUS ${PROJECT_SOURCE_DIR} "--------------- 完成编译和连接生成可执行文件 ---------------")
