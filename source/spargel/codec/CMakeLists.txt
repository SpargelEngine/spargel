spargel_add_library(
    NAME codec
    PRIVATE
        codec.cpp
        cursor.cpp
    DEPS
        base
)

spargel_add_library(
    NAME codec_json
    PRIVATE
        json_codec.cpp
        json_parser.cpp
    DEPS
        codec
)

# TEST

spargel_add_executable(
    NAME test_codec
    PRIVATE test_codec.cpp
    DEPS
        codec
        test_main
)
add_test(
    NAME test_codec
    COMMAND test_codec
)

spargel_add_executable(
    NAME test_codec2
    PRIVATE test_codec2.cpp
    DEPS
        codec
        test_main
)
add_test(
    NAME test_codec2
    COMMAND test_codec2
)

spargel_add_executable(
    NAME test_json
    PRIVATE test_json.cpp
    DEPS
        codec_json
        test_main
)
add_test(
    NAME test_json
    COMMAND test_json
)

spargel_add_executable(
    NAME test_json_codec
    PRIVATE test_json_codec.cpp
    DEPS
        codec_json
        test_main
)
add_test(
    NAME test_json_codec
    COMMAND test_json_codec
)

# OTHER

spargel_add_executable(
    NAME dump_json
    PRIVATE dump_json.cpp
    DEPS
        codec_json
        resource
)

add_subdirectory(model/)
