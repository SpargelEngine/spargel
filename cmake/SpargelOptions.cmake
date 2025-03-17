#### Spargel Options ####

#
# Recommended Option Naming Pattern: SPARGEL_${SCOPE}_[ENABLE/IS/USE]_${NAME}
#


#### Platform Specific Options ####

if (SPARGEL_IS_ANDROID)
    set(SPARGEL_ANDROID_TARGET simple_entry_demo CACHE STRING "the target to be built" )
    message(STATUS "Android build target: ${SPARGEL_ANDROID_TARGET}")
endif ()

if (SPARGEL_IS_LINUX)
    spargel_add_option(SPARGEL_LINUX_IS_DESKTOP "build for Linux desktop (X11/Wayland + OpenGL etc.)" ON)
endif ()

if (SPARGEL_IS_MACOS)
    spargel_add_option(SPARGEL_ENABLE_METAL "enable metal backend" ON)
endif ()

if (SPARGEL_IS_WINDOWS)

    spargel_add_option(SPARGEL_GPU_ENABLE_DIRECTX "enable directx backend" ON)

    set(SPARGEL_VS_BUILD_TYPE Debug CACHE STRING "Visual Studio build type")
    message(STATUS "Visual Studio build type: ${SPARGEL_VS_BUILD_TYPE}")

endif ()


#### Default Values for Options ####

# File Memory Mapping (mmap)
if (SPARGEL_IS_EMSCRIPTEN)
    set(SPARGEL_USE_FILE_MMAP_DEFAULT OFF)
else ()
    set(SPARGEL_USE_FILE_MMAP_DEFAULT ON)
endif ()

# OpenGL
if (SPARGEL_IS_EMSCRIPTEN OR SPARGEL_IS_MACOS)
    set(SPARGEL_ENABLE_OPENGL_DEFAULT OFF)
elseif (SPARGEL_IS_LINUX AND NOT SPARGEL_LINUX_IS_DESKTOP)
    set(SPARGEL_ENABLE_OPENGL_DEFAULT OFF)
else ()
    set(SPARGEL_ENABLE_OPENGL_DEFAULT ON)
endif ()

# Vulkan
if (SPARGEL_IS_EMSCRIPTEN)
    set(SPARGEL_GPU_ENABLE_VULKAN_DEFAULT OFF)
else ()
    set(SPARGEL_GPU_ENABLE_VULKAN_DEFAULT ON)
endif ()


#### General Options ####

spargel_add_option(SPARGEL_ENABLE_ADDRESS_SANITIZER "enable address sanitizer" OFF)
spargel_add_option(SPARGEL_ENABLE_ASSERT "enable assert()" ON)
spargel_add_option(SPARGEL_ENABLE_CLANG_TIDY "enable clang-tidy" OFF)
spargel_add_option(SPARGEL_ENABLE_LOG_ANSI_COLOR "enable ANSI color for logging" OFF)
spargel_add_option(SPARGEL_ENABLE_OPENGL "enable OpenGL backend" ${SPARGEL_ENABLE_OPENGL_DEFAULT})
spargel_add_option(SPARGEL_GIT_USE_SSH "use ssh for git remote operations" OFF)
spargel_add_option(SPARGEL_GPU_ENABLE_VULKAN "enable vulkan backend" ${SPARGEL_GPU_ENABLE_VULKAN_DEFAULT})
spargel_add_option(SPARGEL_USE_FILE_MMAP "use file memory mapping (mmap)" ${SPARGEL_USE_FILE_MMAP_DEFAULT})

# unused: spargel_add_option(SPARGEL_ENABLE_COVERAGE "enable coverge" OFF)
# unused: spargel_add_option(SPARGEL_TRACE_ALLOCATION "trace allocation" OFF)
