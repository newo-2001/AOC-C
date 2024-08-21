cmake_minimum_required(VERSION 3.25)
project(aoc C)

set(CMAKE_C_STANDARD 99)

file(COPY inputs DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY solutions DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(aoc
    src/main.c
    src/debug.h
    src/constants.h
    src/lib/strutils.h
    src/lib/strutils.c
    src/lib/geometry.h
    src/lib/geometry.c
    src/lib/hash.h
    src/lib/hash.c
    src/lib/collections/hashmap.h
    src/lib/collections/hashmap.c
    src/vendor/md5.c
    src/vendor/md5.h
    src/solvers/solvers.h
    src/solvers/2015/day_01.c
    src/solvers/2015/day_02.c
    src/solvers/2015/day_03.c
    src/solvers/2015/day_04.c
)
