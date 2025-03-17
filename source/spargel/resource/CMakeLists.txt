
spargel_add_library(
    NAME resource
    PRIVATE
        resource.cpp
        directory.cpp
        overlay.cpp
    PRIVATE_ANDROID
        android_asset.cpp
    DEPS
        base
        util
)

spargel_add_executable(
    NAME demo_resource
    PRIVATE demo_resource.cpp
    DEPS resource
)
spargel_application_add_resources(
    TARGET demo_resource
    SRC ${CMAKE_CURRENT_SOURCE_DIR}/demo_assets
    DST
    DEPS demo_resource_make_resources_dir
)

spargel_add_executable(
    NAME demo_resource_overlay
    PRIVATE demo_resource_overlay.cpp
    DEPS resource
)
add_custom_target(demo_resource_make_resources_dir
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/resources
)
add_custom_target(demo_resource_overlay_resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${CMAKE_CURRENT_SOURCE_DIR}/demo_assets ${CMAKE_CURRENT_BINARY_DIR}/resources
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${CMAKE_CURRENT_SOURCE_DIR}/demo_assets2 ${CMAKE_CURRENT_BINARY_DIR}/resources2
    DEPENDS demo_resource_make_resources_dir
)
add_dependencies(demo_resource_overlay demo_resource_overlay_resources)
