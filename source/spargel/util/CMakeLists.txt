spargel_add_library(
    NAME util
    PRIVATE
        path.cpp
    DEPS base
)

spargel_add_executable(
    NAME test_path
    PRIVATE
        test_path.cpp
    DEPS
        base
        util
)
