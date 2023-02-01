aux_source_directory(. DIR_LIB_SRCS)

include_directories(../include)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(Lib_test STATIC ${DIR_LIB_SRCS})

message(STATIC "--------------- test 生成静态库完成 ---------------")
