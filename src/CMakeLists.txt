file(COPY ../inputs DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ../solutions DESTINATION ${CMAKE_BINARY_DIR})

add_executable(aoc
    main.c
    timer.c
    solvers/2015/day_01.c
    solvers/2015/day_02.c
    solvers/2015/day_03.c
    solvers/2015/day_04.c
    solvers/2015/day_05.c
    solvers/2015/day_06.c
    solvers/2015/day_07.c
    solvers/2015/day_08.c
)

target_link_libraries(aoc
    aoc_lib
    md5
)

target_compile_options(aoc PRIVATE
    $<$<C_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror>
)

target_compile_definitions(aoc PRIVATE ${common_defines})