# For more information about using CMake read the documentation on:
#   * https://cmake.org/cmake/help/latest/guide/tutorial/index.html
#   * https://cliutils.gitlab.io/modern-cmake/chapters/basics.html
#   * https://cmake.org/examples/

cmake_minimum_required (VERSION 3.15...3.40)

project (
    DSA_Playground
    VERSION 0.1
    DESCRIPTION "Common Data Structures and Algorithms in C"
    LANGUAGES C
    )

# Only do these if this is the main project, and not if it is included through
# add_subdirectory
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Append custom flags
    if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
        add_compile_options (-v -Wall -Wextra -pedantic -fcolor-diagnostics
            -fdiagnostics-format=vi)
    endif ()

endif ()

# Add the source code
add_subdirectory (./src)
