spargel_add_library(
    NAME lang
    PRIVATE
        syntax.cpp
    DEPS
        base
)

spargel_add_executable(
    NAME driver
    PRIVATE
        driver.cpp
    DEPS
        base
        resource
)

spargel_add_executable(
    NAME syntax_test
    PRIVATE
        syntax_test.cpp
    DEPS
        base
        lang
        test_main
)
add_test(
    NAME syntax_test
    COMMAND syntax_test
)
