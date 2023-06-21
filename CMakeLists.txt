cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_GENERATOR_TOOLSET "v140")
    set(CMAKE_VS_PLATFORM_TOOLSET "v140")

    set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
    )
    set(CMAKE_C_FLAGS_DEBUG "/fsanitize=address")

    foreach(CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

# Use this to locate Qt5.15.2 on your development machine
# list(APPEND CMAKE_PREFIX_PATH "H:/Qt/5.15.2/msvc2019_64")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Don't touch this, it will be set by the build script
project("<plugin_name>")

message("Looking for Qt...")

find_package(Qt5 REQUIRED Widgets)

if(${Qt5_FOUND})
    message("Found Qt " ${Qt5_VERSION})
else()
    message("Couldn't find Qt")
endif()

include_directories("ts3client-pluginsdk/include")

set(sources
    src/config.ui
    src/config.cpp
    src/definitions.hpp
    src/plugin.cpp
)

add_library(${CMAKE_PROJECT_NAME} SHARED ${sources})

if(MSVC)
    target_compile_options(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        /MT
    )
else()
    target_compile_options(
        ${CMAKE_PROJECT_NAME}
        PRIVATE
        -fPIC
        -static-libgcc
        -static-libstdc++
    )
endif()

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    Qt5::Widgets
)