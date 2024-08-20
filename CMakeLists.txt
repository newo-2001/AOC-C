cmake_minimum_required(VERSION 3.25)
project(aoc C)

set(CMAKE_C_STANDARD 99)

file(COPY inputs DESTINATION Debug)
file(COPY solutions DESTINATION Debug)

add_executable(aoc
    src/main.c
    src/debug.h
    src/constants.h
    src/lib/strutils.h
    src/lib/strutils.c
    src/lib/geometry.h
    src/lib/geometry.c
    src/lib/collections/hashmap.h
    src/lib/collections/hashmap.c
    src/solvers/solvers.h
    src/solvers/2015/day_01.c
    src/solvers/2015/day_02.c
    src/solvers/2015/day_03.c
)
