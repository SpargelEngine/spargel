spargel_add_library(
    NAME ui
    PRIVATE
        event.cpp
        platform.cpp
        ui_dummy.cpp
        view.cpp
        view_host.cpp
    PRIVATE_ANDROID
        ui_android.cpp
    PRIVATE_LINUX
    PRIVATE_MACOS
        platform_mac.mm
        window_mac.mm
    PRIVATE_WINDOWS
        ui_win32.cpp
    DEPS
        base
        render
)


if (SPARGEL_IS_ANDROID)
    get_target_property(ANDROID_GAME_ACTIVITY_INCLUDE game-activity::game-activity INTERFACE_INCLUDE_DIRECTORIES)
    target_include_directories(ui PRIVATE ${ANDROID_GAME_ACTIVITY_INCLUDE})
endif ()

if (SPARGEL_IS_LINUX)
    if (SPARGEL_LINUX_IS_DESKTOP)

        target_sources(ui PRIVATE ui_xcb.cpp xkb_util.cpp)

        target_link_libraries(ui PRIVATE
            X11 xcb X11-xcb
            ${XKBCOMMON_LIBRARIES} ${XKBCOMMON_X11_LIBRARIES})

        if (SPARGEL_ENABLE_OPENGL)
            target_link_libraries(ui PRIVATE OpenGL::GLX)
        endif ()

    endif ()
endif ()

if (APPLE)
  #find_library(FRAMEWORK_APP_KIT AppKit)
  #find_library(FRAMEWORK_METAL Metal)
  #find_library(FRAMEWORK_QUARTZ_CORE QuartzCore)
  target_link_libraries(ui PRIVATE ${FRAMEWORK_APP_KIT} ${FRAMEWORK_METAL} ${FRAMEWORK_QUARTZ_CORE} ${FRAMEWORK_GAME_CONTROLLER})

  # compiler metal shaders
  # super hacky
  #add_custom_command(
  #  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shader.metallib
  #  COMMAND
  #    xcrun -sdk macosx metal -o ${CMAKE_CURRENT_BINARY_DIR}/shader.ir -c ${CMAKE_CURRENT_SOURCE_DI#R}/metal/shader.metal -I ${PROJECT_SOURCE_DIR}/source
  #  COMMAND
  #    xcrun -sdk macosx metallib -o ${CMAKE_CURRENT_BINARY_DIR}/shader.metallib ${CMAKE_CURRENT_BINARY_DI#R}/shader.ir
  #  DEPENDS
  #    metal/shader.metal
  #)
  #add_custom_target(ui_metal_shader
  #  DEPENDS
  #    ${CMAKE_CURRENT_BINARY_DIR}/shader.metallib)
endif ()

spargel_add_executable(
    NAME window_demo
    PRIVATE window_demo.cpp
    DEPS ui
)

spargel_add_application(
    NAME window_demo2
    PRIVATE window_demo2.cpp
    DEPS entry
)
