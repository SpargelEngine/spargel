spargel_add_library(
    NAME base
    PRIVATE
        allocator.cpp
        panic.cpp
        platform.cpp
        string.cpp
        logging.cpp
        test.cpp
    PRIVATE_POSIX
        platform_posix.cpp
    PRIVATE_ANDROID
        platform_linux.cpp
    PRIVATE_EMSCRIPTEN
        platform_emscripten.cpp
    PRIVATE_LINUX
        platform_linux.cpp
    PRIVATE_MACOS
        platform_mac.cpp
    PRIVATE_WINDOWS
        platform_win.cpp
    DEPS spargel_config
)

spargel_add_library(
    NAME test_main
    PRIVATE
        test_main.cpp
    DEPS base
)

if (SPARGEL_IS_ANDROID OR SPARGEL_IS_LINUX)
    target_link_libraries(base PUBLIC m)
endif ()

spargel_add_executable(
    NAME executable_path_demo
    PRIVATE executable_path_demo.cpp
    DEPS base
)

spargel_add_executable(
    NAME backtrace_demo
    PRIVATE backtrace_demo.cpp
    DEPS base
)

spargel_add_executable(
    NAME panic_demo
    PRIVATE panic_demo.cpp
    DEPS base
)

spargel_add_executable(
    NAME log_demo
    PRIVATE log_demo.cpp
    DEPS base
)

spargel_add_executable(
    NAME tag_invoke_demo
    PRIVATE tag_invoke_demo.cpp
    DEPS base
)

spargel_add_executable(
    NAME vector_test
    PRIVATE vector_test.cpp
    DEPS base
)

spargel_add_executable(
    NAME meta_test
    PRIVATE meta_test.cpp
    DEPS base
)

spargel_add_executable(
    NAME test_demo
    PRIVATE
        test_demo.cpp
    DEPS
        base
        test_main
)

spargel_add_executable(
    NAME vector_bench
    PRIVATE
        vector_bench.cpp
    DEPS
        base
)

spargel_add_executable(
    NAME hash_test
    PRIVATE
        hash_test.cpp
    DEPS
        base
)

spargel_add_executable(
    NAME tagged_union_test
    PRIVATE
        tagged_union_test.cpp
    DEPS
        base
)

spargel_add_executable(
    NAME string_test
    PRIVATE
        string_test.cpp
    DEPS
        base
)

spargel_add_executable(
    NAME sum_type_test
    PRIVATE
        sum_type_test.cpp
    DEPS
        base
)

spargel_add_executable(
    NAME inline_array_test
    PRIVATE
        inline_array_test.cpp
    DEPS
        base
)

spargel_add_executable(
    NAME optional_test
    PRIVATE
        optional_test.cpp
    DEPS
        base
)

spargel_add_executable(
    NAME array_storage_test
    PRIVATE
        array_storage_test.cpp
    DEPS
        base
)

spargel_add_executable(
    NAME hash_map_test
    PRIVATE
        hash_map_test.cpp
    DEPS
        base
)
