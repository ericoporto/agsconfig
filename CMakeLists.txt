# https://gitlab.kitware.com/cmake/community/wikis/doc/cmake/Life-Cycle-Considerations
cmake_minimum_required(VERSION 3.13..3.14)

set(CMAKE_USER_MAKE_RULES_OVERRIDE ${CMAKE_CURRENT_SOURCE_DIR}/CMake/c_flag_overrides.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX ${CMAKE_CURRENT_SOURCE_DIR}/CMake/cxx_flag_overrides.cmake)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")

project(AGSCONFIG
        VERSION 0.1.0
        LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # WIN32 is set by CMake for any Windows platform
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX TRUE)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOS TRUE)
else()
    message(FATAL_ERROR "Unsupported system: ${CMAKE_SYSTEM_NAME}")
endif ()

add_executable (AGSCONFIG
        agsconfig.cpp
        AgsTold.cpp
        AgsTold.h
        agsdata.cpp
        agsdata.h
        libs/inipp/inipp/inipp.h
        libs/imgui/imgui.h
        libs/imgui/imgui.cpp
        libs/imgui/imgui_demo.cpp
        libs/imgui/imgui_draw.cpp
        libs/imgui/imgui_widgets.cpp
        libs/imgui/examples/imgui_impl_sdl.cpp
        libs/imgui/examples/imgui_impl_sdl.h
        libs/imgui/examples/imgui_impl_opengl2.h
        libs/imgui/examples/imgui_impl_opengl2.cpp util_str.h)


find_package(OpenGL)
include(FindLocalSDL2)
add_subdirectory(libs/tiny-process-library EXCLUDE_FROM_ALL)

if(LINUX)
    target_link_libraries(AGSCONFIG dl GL)
elseif(MACOS)
    target_link_libraries(AGSCONFIG PRIVATE "-framework Cocoa")
    target_link_libraries(AGSCONFIG PRIVATE "-framework OpenGL")
    target_link_libraries(AGSCONFIG PRIVATE "-framework Foundation")
    target_link_libraries(AGSCONFIG PRIVATE "-framework CoreVideo")
    target_include_directories(AGSCONFIG PRIVATE /usr/local/include)
    target_include_directories(AGSCONFIG PRIVATE /opt/local/include)
endif()

target_include_directories(AGSCONFIG PRIVATE libs/inipp/inipp)
target_include_directories(AGSCONFIG PRIVATE libs/imgui)
target_include_directories(AGSCONFIG PRIVATE libs/imgui/examples)
target_include_directories(AGSCONFIG PRIVATE libs/SDL2-2.0.10/include)
target_include_directories(AGSCONFIG PRIVATE libs/tiny-process-library)

target_link_libraries(AGSCONFIG SDL2)
target_link_libraries(AGSCONFIG tiny-process-library)

set_target_properties(AGSCONFIG PROPERTIES OUTPUT_NAME "agsconfig")
