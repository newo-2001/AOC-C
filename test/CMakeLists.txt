function(new_test_binary name)
    set(target_name test_${name})

    add_executable(${target_name} ${ARGN})

    target_link_libraries(${target_name} PRIVATE
        aoc_lib
        unity
    )

    target_compile_options(${target_name} PRIVATE
        $<$<C_COMPILER_ID:MSVC>:/W4 /WX /Zi /Od>
        $<$<NOT:$<C_COMPILER_ID:MSVC>>:-w -g -O0>
    )

    target_link_options(${target_name} PRIVATE
        $<$<C_COMPILER_ID:MSVC>:/DEBUG>
        $<$<NOT:$<C_COMPILER_ID:MSVC>>:-g>
    )

    target_compile_definitions(${target_name} PRIVATE common_defines)

    # Set output directory for test executables
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/test/Debug
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/test/Release
    )

    add_test(NAME ${name} COMMAND ${target_name})
endfunction()

new_test_binary(slice slice_tests.c)
new_test_binary(hashmap collections/hashmap_tests.c collections/hashmap_fixture.c)
new_test_binary(list collections/list_tests.c)
new_test_binary(geometry geometry_tests.c)
new_test_binary(str str_tests.c)
new_test_binary(math math_tests.c)