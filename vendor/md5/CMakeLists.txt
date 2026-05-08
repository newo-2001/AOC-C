cmake_minimum_required(VERSION 3.22.1)

project(md5 C)

add_library(md5 STATIC md5.c)

configure_file(md5.h
    ${CMAKE_CURRENT_BINARY_DIR}/include/md5/md5.h
    COPYONLY
)

target_include_directories(md5 PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)