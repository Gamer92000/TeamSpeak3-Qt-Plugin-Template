cmake_minimum_required(VERSION 3.10)

set(CMAKE_GENERATOR_TOOLSET "v140")
set(CMAKE_VS_PLATFORM_TOOLSET "v140")
# Use this to locate Qt5.12.3 on your development machine
# list(APPEND CMAKE_PREFIX_PATH "H:/Qt/5.12.3/msvc2017_64")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

project("QtExamplePlugin")

message("Looking for Qt...")

find_package(Qt5 REQUIRED Widgets)
if (${Qt5_FOUND})
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

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    Qt5::Widgets
)