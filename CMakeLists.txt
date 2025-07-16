cmake_minimum_required(VERSION 3.22.1)

project(aoc C)

set(CMAKE_C_STANDARD 11)

include(CTest)
enable_testing()

if (WIN32)
    add_compile_definitions(
        WIN32
        _CRT_SECURE_NO_WARNINGS
        strtok_r=strtok_s
    )
elseif (UNIX)
    add_compile_definitions(UNIX)
endif ()

file(COPY inputs DESTINATION ${CMAKE_BINARY_DIR})
file(COPY solutions DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(lib)
add_subdirectory(vendor/md5)

add_executable(aoc
    src/main.c
    src/timer.h
    src/timer.c

    src/solvers/solvers.h
    src/solvers/2015/day_01.c
    src/solvers/2015/day_02.c
    src/solvers/2015/day_03.c
    src/solvers/2015/day_04.c
    src/solvers/2015/day_05.c
    src/solvers/2015/day_06.c
    src/solvers/2015/day_07.c
    src/solvers/2015/day_08.c
)

target_link_libraries(aoc
    aoc_lib
    md5
)

add_subdirectory(vendor/unity)
add_subdirectory(test)