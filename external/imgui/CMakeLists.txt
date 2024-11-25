cmake_minimum_required(VERSION 3.19)
project(imgui)

add_library(imgui STATIC
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    backends/imgui_impl_dx9.cpp
    backends/imgui_impl_win32.cpp
)

target_include_directories(imgui PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
)