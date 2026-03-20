cmake_minimum_required(VERSION 3.21)
project(SoggyJumpscare VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Gather all source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Check GEODE_SDK
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable.")
else()
    message(STATUS "Found Geode SDK: $ENV{GEODE_SDK}")
endif()

# Add the loader/include path so compiler can find Geode 5.3.0 headers
target_include_directories(${PROJECT_NAME} PRIVATE
    "$ENV{GEODE_SDK}/loader/include"
)

# Add Geode SDK subdirectory for build
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Setup the mod
setup_geode_mod(${PROJECT_NAME})