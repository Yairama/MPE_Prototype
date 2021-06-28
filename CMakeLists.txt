cmake_minimum_required(VERSION 3.17)
project(core)

set(CMAKE_CXX_STANDARD 20)

#VULKAN
include_directories("$ENV{VULKAN_SDK}/include")
link_directories("$ENV{VULKAN_SDK}/lib")
link_directories("$ENV{VULKAN_SDK}/etc/explicit_layer.d")
set(VULKAN_LIB_LIST "vulkan-1")

#OPENGL

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS})

#GLAD
include_directories(lib/glad/include)

#GFLW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)


#GLM
add_subdirectory(lib/glm)

#IMGUI
##Take care when remove, add or update files from this src because its necessary a manual CMAKE recompilation
file(GLOB IMGUI_SRC
        lib/imgui/*.h
        lib/imgui/*.cpp
        )


add_executable(core main.cpp
        vk_core/first_app.cpp
        vk_core/first_app.hpp
        vk_core/cvk_device.cpp
        vk_core/cvk_device.hpp
        vk_core/cvk_model.cpp
        vk_core/cvk_model.hpp
        vk_core/cvk_pipeline.cpp
        vk_core/cvk_pipeline.hpp
        vk_core/cvk_swap_chain.cpp
        vk_core/cvk_swap_chain.hpp
        vk_core/cvk_window.cpp
        vk_core/cvk_window.hpp
        vk_core/cvk_game_object.hpp
        vk_core/cvk_renderer.hpp
        vk_core/cvk_renderer.cpp
        vk_core/simple_render_system.hpp
        vk_core/simple_render_system.cpp

        vk_core/tests/rainbow_system.hpp
        vk_core/cvk_camera.hpp
        vk_core/cvk_camera.cpp

        ${IMGUI_SRC}

        vk_core/cvk_imgui.cpp
        vk_core/cvk_imgui.hpp)


target_link_libraries(core glfw)
target_link_libraries(core glm)
target_link_libraries(core ${VULKAN_LIB_LIST} )
target_link_libraries(core ${OPENGL_LIBRARIES})
