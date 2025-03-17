spargel_add_library(
    NAME codec_gltf
    PRIVATE
        gltf.cpp
    DEPS
        codec_json
)

spargel_add_executable(
    NAME summary_gltf
    PRIVATE
        summary_gltf.cpp
    DEPS
        codec_gltf
        resource
)
