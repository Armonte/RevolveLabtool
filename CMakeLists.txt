cmake_minimum_required(VERSION 3.19)
project(RevolveLabtool)

set(CMAKE_CXX_STANDARD 20)

# DirectX SDK (June 2010) paths
set(DXSDK_DIR "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")

# Windows SDK paths
set(DX_INCLUDE_DIR "C:/Program Files (x86)/Windows Kits/10/Include/10.0.22000.0/um")
set(DX_LIB_DIR "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22000.0/um/x86")

# Add ImGui
add_subdirectory(external/imgui)

# Configure Detours
add_library(detours STATIC IMPORTED)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 64-bit
    set_target_properties(detours PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/external/detours/x64/detours.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/external/detours/include"
    )
else()
    # 32-bit
    set_target_properties(detours PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/external/detours/x86/detours.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/external/detours/include"
    )
endif()

# RevolveLib.lib
add_library(
    RevolveLib STATIC
    src/revolveLib/RevolveLib.hpp 
    src/revolveLib/Address.hpp
    src/revolveLib/Address.cpp 
    src/revolveLib/Character.cpp
    src/revolveLib/Character.hpp
)
target_include_directories(RevolveLib PRIVATE src/revolveLib)

# Labtool.dll
add_library(Labtool SHARED 
    src/injector/DLLMain.cpp 
    src/labtool/EntryPoint.cpp
    src/labtool/EntryPoint.hpp
    src/labtool/hooks/Hook.cpp
    src/labtool/hooks/Hook.h
    src/labtool/hooks/pch.h
    src/labtool/hooks/StringPatch.cpp
    src/labtool/hooks/StringPatch.h
    src/overlay/Drawing.cpp
    src/overlay/Drawing.h
)

target_include_directories(Labtool PRIVATE 
    src/labtool 
    src/injector
    src/overlay
    ${DX_INCLUDE_DIR}
    "${DXSDK_DIR}/Include"    # DirectX SDK Include path
)

target_link_directories(Labtool PRIVATE 
    ${DX_LIB_DIR}
    "${DXSDK_DIR}/Lib/x86"    # DirectX SDK Lib path for 32-bit
)

target_link_libraries(Labtool PRIVATE 
    RevolveLib
    imgui
    detours
    d3d9.lib
    d3dx9.lib    # Added D3DX9 library
)

# RevolveLabtool.exe
add_executable(RevolveLabtool src/injector/DLLInjector.cpp)
target_include_directories(RevolveLabtool PRIVATE src/injector)
