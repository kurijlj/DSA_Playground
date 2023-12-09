# Find clang-tidy if available
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

# Set clang-tidy arguments
if(CLANG_TIDY_EXE)
    set(
        CLANG_TIDY_COMMAND
        "${CLANG_TIDY_EXE}"
        "clang-diagnostic-*,clang-analyzer-*,readability-*,performance-*"
        )
endif()

add_executable (
    find_middle_node
    find_middle_node.c
)

set_target_properties(
    find_middle_node
    PROPERTIES
    C_CLANG_TIDY
    "${CLANG_TIDY_COMMAND}"
    )
target_compile_features (find_middle_node PRIVATE c_std_11)
