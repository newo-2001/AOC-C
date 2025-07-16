function(new_test_binary name source_file)
    set(target_name test_${name})

    add_executable(${target_name} ${source_file})

    target_link_libraries(${target_name} PRIVATE
        aoc_lib
        unity
    )

    target_compile_options(${target_name} PRIVATE
        $<$<C_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<C_COMPILER_ID:MSVC>>:-w>
    )

    target_compile_definitions(${target_name} PRIVATE common_defines)

    add_test(NAME ${name} COMMAND ${target_name})
endfunction()

new_test_binary(hashmap collections/hashmaptests.c)
new_test_binary(geometry geometrytests.c)