include(FetchContent)

FetchContent_Declare(unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG master
    GIT_SHALLOW true
)

FetchContent_MakeAvailable(unity)