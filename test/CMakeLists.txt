add_executable(test_hashmap
    collections/hashmaptests.c
)

target_link_libraries(test_hashmap PRIVATE
    aoc_lib
    unity_static
)

add_test(NAME hashmap COMMAND test_hashmap)