set(LIB_HEADERS
    constants.h
    strutils.h
    geometry.h
    hash.h
    math.h

    collections/hashset.h
    collections/hashmap.h
)

set(LIB_SOURCE
    strutils.c
    geometry.c
    hash.c

    collections/hashmap.c
)

foreach(HEADER ${LIB_HEADERS})
    configure_file(${HEADER}
        ${CMAKE_CURRENT_BINARY_DIR}/include/aoc_lib/${HEADER}
        COPYONLY
    )
endforeach()

add_library(aoc_lib STATIC
    ${LIB_HEADERS}
    ${LIB_SOURCE}
)

target_include_directories(aoc_lib PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}/include
)