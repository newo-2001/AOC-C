set(LIB_HEADERS
    strutils.h
    geometry.h
    hash.h
    math.h
    slice.h

    collections/hashset.h
    collections/hashmap.h
)

set(LIB_SOURCE
    strutils.c
    geometry.c
    hash.c
    slice.c

    collections/hashmap.c
)

foreach(HEADER ${LIB_HEADERS})
    configure_file(${HEADER}
        ${CMAKE_CURRENT_BINARY_DIR}/include/aoc_lib/${HEADER}
        COPYONLY
    )
endforeach()

add_library(aoc_lib STATIC
   ${LIB_SOURCE}
)

target_include_directories(aoc_lib PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/include
)

target_compile_options(aoc_lib PRIVATE
    $<$<C_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror>
)

target_compile_definitions(aoc_lib PRIVATE common_defines)