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
    linkedlist
    linkedlist.c
)

set_target_properties(
    linkedlist
    PROPERTIES
    C_CLANG_TIDY
    "${CLANG_TIDY_COMMAND}"
    )
target_compile_features (linkedlist PRIVATE c_std_11)
