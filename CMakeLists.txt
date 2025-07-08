cmake_minimum_required(VERSION 3.22.1)

project(aoc C)

set(CMAKE_C_STANDARD 11)

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

add_executable(aoc
    src/main.c
    src/constants.h
    src/timer.h
    src/timer.c

    src/lib/strutils.h
    src/lib/strutils.c
    src/lib/geometry.h
    src/lib/geometry.c
    src/lib/hash.h
    src/lib/hash.c
    src/lib/math.h

    src/lib/collections/hashmap.h
    src/lib/collections/hashmap.c
    src/lib/collections/hashset.h

    src/vendor/md5.c
    src/vendor/md5.h

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
