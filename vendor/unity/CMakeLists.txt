include(FetchContent)

FetchContent_Declare(unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG master
    GIT_SHALLOW true
)

# Temporarily disable global warning flags
set(TEMP_C_FLAGS ${CMAKE_C_FLAGS})
set(CMAKE_C_FLAGS "")

FetchContent_MakeAvailable(unity)

add_library(unity_static STATIC
    ${unity_SOURCE_DIR}/src/unity.c
)

target_include_directories(unity_static SYSTEM PUBLIC
    ${unity_SOURCE_DIR}/src
)

# Restore global flags
set(CMAKE_C_FLAGS ${TEMP_C_FLAGS})

target_compile_options(unity_static PRIVATE
    $<$<C_COMPILER_ID:MSVC>:/W0>
    $<$<NOT:$<C_COMPILER_ID:MSVC>>:-w>
)