cmake_minimum_required(VERSION 3.22.1)

project(aoc C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
enable_testing()

set(common_defines "")

if (WIN32)
    list(APPEND common_defines
        WIN32
        _CRT_SECURE_NO_WARNINGS
        NOMINMAX
    )
elseif (UNIX)
    list(APPEND common_defines UNIX)
endif ()

add_subdirectory(vendor/unity)
add_subdirectory(vendor/md5)
add_subdirectory(aoc_lib)
add_subdirectory(src)
add_subdirectory(test)