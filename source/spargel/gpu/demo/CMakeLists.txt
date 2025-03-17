# spargel_add_executable(
#     NAME demo_gpu
#     PRIVATE demo_gpu.cpp
#     DEPS gpu ui
# )

# spargel_add_application(
#     NAME demo_gpu_port
#     PRIVATE demo_gpu_port.cpp
#     DEPS gpu ui entry
# )

spargel_add_executable(
    NAME demo_gpu
    PRIVATE demo_gpu.cpp
    DEPS gpu resource ui
)

spargel_add_executable(
    NAME demo_sum
    PRIVATE demo_sum.cpp
    DEPS gpu resource ui
)

spargel_add_executable(
    NAME demo_sort
    PRIVATE demo_sort.cpp
    DEPS gpu resource ui
)

spargel_add_executable(
    NAME demo_tiles
    PRIVATE demo_tiles.cpp
    DEPS gpu resource ui
)

spargel_add_executable(
    NAME demo_graph
    PRIVATE demo_graph.cpp
    DEPS gpu ui
)


add_custom_target(demo_gpu_make_resources_dir
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/resources
)

if (SPARGEL_GPU_ENABLE_VULKAN)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources/vertex_shader.spirv
        COMMAND
            Vulkan::glslangValidator
                -S vert # stage
                --target-env vulkan1.2
                -o ${CMAKE_CURRENT_BINARY_DIR}/resources/vertex_shader.spirv
                ${CMAKE_CURRENT_SOURCE_DIR}/vertex_shader.glsl
        DEPENDS vertex_shader.glsl
    )
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources/fragment_shader.spirv
        COMMAND
            Vulkan::glslangValidator
                -S frag # stage
                --target-env vulkan1.2
                -o ${CMAKE_CURRENT_BINARY_DIR}/resources/fragment_shader.spirv
                ${CMAKE_CURRENT_SOURCE_DIR}/fragment_shader.glsl
        DEPENDS fragment_shader.glsl
    )
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources/demo_sum.spirv
        COMMAND
            Vulkan::glslangValidator
                -S comp # stage
                --target-env vulkan1.2
                --entry-point add_arrays
                --source-entrypoint main
                -o ${CMAKE_CURRENT_BINARY_DIR}/resources/demo_sum.spirv
                ${CMAKE_CURRENT_SOURCE_DIR}/demo_sum.glsl
        DEPENDS demo_sum.glsl
    )
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources/demo_sort.spirv
        COMMAND
            Vulkan::glslangValidator
                -S comp # stage
                --target-env vulkan1.2
                --entry-point bitonic_sort
                --source-entrypoint main
                -o ${CMAKE_CURRENT_BINARY_DIR}/resources/demo_sort.spirv
                ${CMAKE_CURRENT_SOURCE_DIR}/demo_sort.glsl
        DEPENDS demo_sort.glsl
    )
    add_custom_target(demo_gpu_vulkan_shaders
        DEPENDS
            ${CMAKE_CURRENT_BINARY_DIR}/resources/vertex_shader.spirv
            ${CMAKE_CURRENT_BINARY_DIR}/resources/fragment_shader.spirv
    )
    add_custom_target(demo_sum_vulkan_shaders
        DEPENDS
            ${CMAKE_CURRENT_BINARY_DIR}/resources/demo_sum.spirv
    )
    add_custom_target(demo_sort_vulkan_shaders
        DEPENDS
            ${CMAKE_CURRENT_BINARY_DIR}/resources/demo_sort.spirv
    )
    add_dependencies(demo_gpu demo_gpu_make_resources_dir demo_gpu_vulkan_shaders)
    add_dependencies(demo_sum demo_gpu_make_resources_dir demo_sum_vulkan_shaders)
    add_dependencies(demo_sort demo_gpu_make_resources_dir demo_sort_vulkan_shaders)
endif ()

if (SPARGEL_IS_MACOS)
    spargel_add_executable(
        NAME demo_gpu_mac
        PRIVATE demo_gpu_mac.mm
        DEPS gpu resource ui
    )

    if (SPARGEL_ENABLE_METAL)
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shader.ir
            COMMAND
                xcrun metal -frecord-sources -o ${CMAKE_CURRENT_BINARY_DIR}/shader.ir -c ${CMAKE_CURRENT_SOURCE_DIR}/shader.metal
            DEPENDS shader.metal
        )
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shader.metallib
            COMMAND
                xcrun metallib -o ${CMAKE_CURRENT_BINARY_DIR}/shader.metallib ${CMAKE_CURRENT_BINARY_DIR}/shader.ir
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/shader.ir
        )
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources/shader.metallib
            COMMAND
                cp ${CMAKE_CURRENT_BINARY_DIR}/shader.metallib ${CMAKE_CURRENT_BINARY_DIR}/resources/shader.metallib
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/shader.metallib
        )
        add_custom_target(demo_gpu_metal_shaders
            DEPENDS
                ${CMAKE_CURRENT_BINARY_DIR}/resources/shader.metallib
        )
        add_dependencies(demo_gpu demo_gpu_make_resources_dir demo_gpu_metal_shaders)
        add_dependencies(demo_gpu_mac demo_gpu_make_resources_dir demo_gpu_metal_shaders)
        add_dependencies(demo_tiles demo_gpu_make_resources_dir demo_gpu_metal_shaders)
        add_dependencies(demo_sort demo_gpu_make_resources_dir demo_gpu_metal_shaders)
    endif ()
endif ()

if (SPARGEL_GPU_ENABLE_DIRECTX)
    spargel_add_executable(
        NAME demo_directx
        PRIVATE demo_directx.cpp
        DEPS base resource ui
    )
    target_link_libraries(demo_directx PRIVATE d3d12.lib dxgi.lib)

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders.vs.dxil
        COMMAND
            dxc ${CMAKE_CURRENT_SOURCE_DIR}/shaders.hlsl -T vs_6_0 -E VSMain -Fo ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders.vs.dxil
        DEPENDS shaders.hlsl
    )
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders.ps.dxil
        COMMAND
            dxc ${CMAKE_CURRENT_SOURCE_DIR}/shaders.hlsl -T ps_6_0 -E PSMain -Fo ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders.ps.dxil
        DEPENDS shaders.hlsl
    )
    add_custom_target(demo_directx_shaders
        DEPENDS
            ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders.vs.dxil
            ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders.ps.dxil
    )
    add_dependencies(demo_directx demo_gpu_make_resources_dir demo_directx_shaders)
endif()
