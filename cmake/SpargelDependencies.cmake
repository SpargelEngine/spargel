include(FetchContent)

find_package(Python COMPONENTS Interpreter)

if (SPARGEL_ENABLE_OPENGL)
    if (SPARGEL_GIT_USE_SSH)
        set(GLAD_GIT_URL git@github.com:Dav1dde/glad.git)
    else ()
        set(GLAD_GIT_URL https://github.com/Dav1dde/glad.git)
    endif ()

    FetchContent_Declare(
        glad
        GIT_REPOSITORY ${GLAD_GIT_URL}
        GIT_TAG        v2.0.8
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
    )

    FetchContent_GetProperties(glad)
    if (NOT glad_POPULATED)
        message("Fetching glad")
        FetchContent_MakeAvailable(glad)

        add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
        glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=3.3 EXTENSIONS)
    endif ()
endif ()

if (SPARGEL_GPU_ENABLE_VULKAN)
    if (SPARGEL_IS_ANDROID)
        find_package(Vulkan REQUIRED)
    else ()
        find_package(Vulkan REQUIRED glslangValidator)
    endif ()
endif ()

if (SPARGEL_IS_ANDROID)
    find_package(game-activity REQUIRED CONFIG)
endif ()

if (SPARGEL_IS_LINUX)
    if (SPARGEL_LINUX_IS_DESKTOP)

        find_package(X11 REQUIRED)

        if (SPARGEL_ENABLE_OPENGL)
            find_package(OpenGL REQUIRED GLX)
        endif ()

        # TODO: find_package(Freetype REQUIRED)

    endif ()
endif ()

if (SPARGEL_IS_MACOS)
    find_library(FRAMEWORK_APP_KIT AppKit REQUIRED)
    find_library(FRAMEWORK_METAL Metal REQUIRED)
    find_library(FRAMEWORK_QUARTZ_CORE QuartzCore REQUIRED)
endif ()
