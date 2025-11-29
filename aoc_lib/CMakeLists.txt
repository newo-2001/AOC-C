set(LIB_SOURCE
    strutils.c
    geometry.c
    hash.c
    str.c
    math.c

    collections/hashmap.c
    collections/list.c
)

# Create the main library with source files
add_library(aoc_lib STATIC
   ${LIB_SOURCE}
)

if (UNIX)
    target_link_libraries(aoc_lib PRIVATE m)
endif ()

# Set up include directories to use source directories directly
target_include_directories(aoc_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

target_compile_options(aoc_lib PRIVATE
    $<$<C_COMPILER_ID:MSVC>:/W4 /WX /Zi /Od>
    $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror -g -O0>
)

target_compile_definitions(aoc_lib PRIVATE common_defines)