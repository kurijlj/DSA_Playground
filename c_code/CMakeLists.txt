# ============================================================================
# A CMake build script for the C CLI application
# ============================================================================

# ----------------------------------------------------------------------------
# For more information about using CMake read the documentation on:
#   * https://cmake.org/cmake/help/latest/guide/tutorial/index.html
#   * https://cliutils.gitlab.io/modern-cmake/chapters/basics.html
#   * https://cmake.org/examples/
# ----------------------------------------------------------------------------

# Define the minimum required version of CMake
cmake_minimum_required (VERSION 3.12...3.40)

# Define the project name and version
project (
    DSA_Playground
    VERSION 0.1
    DESCRIPTION "Common Data Structures and Algorithms in C"
    LANGUAGES C
    )

# Set the C standard to C99 and make it required
set (CMAKE_C_STANDARD 99)  # This is so that we can use 'munit' framework
set (CMAKE_C_STANDARD_REQUIRED ON)

# Set the build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif ()

# Set to build with shared libraries by default
option (BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Set the output directory for the executable
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the argparse library
if (NOT DEFINED ARGPARSE_SHARED)
    option(ARGPARSE_SHARED "Build shared library" OFF)  # Default to OFF
endif ()
option(ARGPARSE_STATIC "Build static library" OFF)
add_subdirectory ("${PROJECT_SOURCE_DIR}/extern/argparse")
# Set the include directory for argparse (library CMake variable is not set)
set (ARGPARSE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/extern/argparse")

# Add the munit unit testing library
add_library (munit STATIC)
target_sources (munit PRIVATE "${PROJECT_SOURCE_DIR}/extern/munit/munit.c")
target_include_directories (
    munit
    PUBLIC
    "${PROJECT_SOURCE_DIR}/extern/munit"
    )

# Add the source code
add_subdirectory (./src)
