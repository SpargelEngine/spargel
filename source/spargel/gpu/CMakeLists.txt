spargel_add_library(
    NAME gpu
    PRIVATE
        gpu.cpp
        gpu_context.cpp
    PRIVATE_MACOS
        gpu_metal.mm
        metal_context.mm
    DEPS
        base
        spargel_config
)

# if(${SPARGEL_GPU_ENABLE_DIRECTX})
#   target_sources(gpu
#     PRIVATE
#       gpu_dx.c
#   )
# endif()

if(${SPARGEL_ENABLE_METAL})
    #target_sources(gpu
    #    PRIVATE
    #        gpu_metal.mm
    #        metal_context.mm
    #)
    target_link_libraries(gpu PRIVATE ${FRAMEWORK_METAL})
endif()

if(${SPARGEL_GPU_ENABLE_VULKAN})
    target_sources(gpu
        PRIVATE
            gpu_vulkan.cpp
    )
    target_link_libraries(gpu PRIVATE Vulkan::Headers)
endif()

add_subdirectory(demo)
