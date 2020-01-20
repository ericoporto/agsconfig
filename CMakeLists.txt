# https://gitlab.kitware.com/cmake/community/wikis/doc/cmake/Life-Cycle-Considerations
cmake_minimum_required(VERSION 3.13..3.14)

set(CMAKE_USER_MAKE_RULES_OVERRIDE ${CMAKE_CURRENT_SOURCE_DIR}/CMake/c_flag_overrides.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX ${CMAKE_CURRENT_SOURCE_DIR}/CMake/cxx_flag_overrides.cmake)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")

project(AGSCONFIG
        VERSION 0.1.0
        LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # WIN32 is set by CMake for any Windows platform
	add_definitions(-DWIN32=1)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX TRUE)
	add_definitions(-DLINUX=1)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOS TRUE)
	add_definitions(-DMACOS=1)
	set(Doptional_CONFIG_SELECT_OPTIONAL optional_OPTIONAL_NONSTD)
else ()
    message(FATAL_ERROR "Unsupported system: ${CMAKE_SYSTEM_NAME}")
endif ()

if(MSVC)
    add_compile_options(/MP)    # Build with Multiple Processes
    add_compile_definitions(_CRT_SECURE_NO_DEPRECATE)
    add_compile_definitions(_CRT_NONSTDC_NO_DEPRECATE)
endif()

if (WIN32)
	add_executable (AGSCONFIG WIN32
			DroidSans.h
			agsconfig.cpp
			AgsConfigUtilStr.h
			AgsConfigUtilStr.cpp
			AgsTold.cpp
			AgsTold.h
			AgsData.cpp
			AgsData.h
			libs/inipp/inipp/inipp.h
			libs/imgui/imgui.h
			libs/imgui/imgui.cpp
			libs/imgui/imgui_demo.cpp
			libs/imgui/imgui_draw.cpp
			libs/imgui/imgui_widgets.cpp
			libs/imgui/examples/imgui_impl_sdl.cpp
			libs/imgui/examples/imgui_impl_sdl.h
			libs/imgui/examples/imgui_impl_opengl2.h
			libs/imgui/examples/imgui_impl_opengl2.cpp )
else ()
	add_executable (AGSCONFIG
			DroidSans.h
			agsconfig.cpp
			AgsConfigUtilStr.h
			AgsConfigUtilStr.cpp
			AgsTold.cpp
			AgsTold.h
			AgsData.cpp
			AgsData.h
			libs/inipp/inipp/inipp.h
			libs/imgui/imgui.h
			libs/imgui/imgui.cpp
			libs/imgui/imgui_demo.cpp
			libs/imgui/imgui_draw.cpp
			libs/imgui/imgui_widgets.cpp
			libs/imgui/examples/imgui_impl_sdl.cpp
			libs/imgui/examples/imgui_impl_sdl.h
			libs/imgui/examples/imgui_impl_opengl2.h
			libs/imgui/examples/imgui_impl_opengl2.cpp AgsConfigIniSettings.cpp AgsConfigIniSettings.h)
endif ()

if(WIN32)
    target_include_directories(AGSCONFIG PRIVATE libs/dirent/include)
endif()


find_package(PkgConfig)
find_package(Threads)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)
set(FORCE_STATIC_VCRT ON)
add_subdirectory(libs/SDL2-2.0.10 EXCLUDE_FROM_ALL)
add_library(SDL2::SDL2 ALIAS SDL2-static)
add_library(SDL2::SDL2main ALIAS SDL2main)

find_package(OpenGL)
add_subdirectory(libs/tiny-process-library EXCLUDE_FROM_ALL)

if(LINUX)
    target_link_libraries(AGSCONFIG PRIVATE dl GL)
elseif(MACOS)
    target_link_libraries(AGSCONFIG PRIVATE "-framework Cocoa")
    target_link_libraries(AGSCONFIG PRIVATE "-framework OpenGL")
    target_link_libraries(AGSCONFIG PRIVATE "-framework Foundation")
    target_link_libraries(AGSCONFIG PRIVATE "-framework CoreVideo")
    target_include_directories(AGSCONFIG PRIVATE /usr/local/include)
    target_include_directories(AGSCONFIG PRIVATE /opt/local/include)
elseif(WIN32)
	target_link_libraries(AGSCONFIG PUBLIC opengl32)
	option (HAVE_LIBC  "Prevent error LNK2005: __ftol2_sse already defined in SDL2d.lib" TRUE)
endif()

target_include_directories(AGSCONFIG PRIVATE libs/SDL2-2.0.10/include)

target_include_directories(AGSCONFIG PRIVATE libs/inipp/inipp)
target_include_directories(AGSCONFIG PRIVATE libs/optional-lite/include)
target_include_directories(AGSCONFIG PRIVATE libs/imgui)
target_include_directories(AGSCONFIG PRIVATE libs/imgui/examples)
target_include_directories(AGSCONFIG PRIVATE libs/tiny-process-library)

target_link_libraries(AGSCONFIG PRIVATE SDL2-static)
target_link_libraries(AGSCONFIG PRIVATE SDL2main)
target_link_libraries(AGSCONFIG PRIVATE tiny-process-library)

set_target_properties(AGSCONFIG PROPERTIES OUTPUT_NAME "agsconfig")