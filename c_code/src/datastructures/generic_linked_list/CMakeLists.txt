# =============================================================================
# Build source targets
# =============================================================================

# Print message to console that we are building the source targets
message(STATUS "Going through ./generic_linked_list")


# -----------------------------------------------------------------------------
# Target: generic_linked_list_test
# -----------------------------------------------------------------------------
#
# Description: Implementation of a generic linked list that uses a heap
#              allocation strategy.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `generic_linked_list_test` target
message(STATUS "Configuring the `generic_linked_list_test` target")

# Set the source files for the `generic_linked_list_test` target
add_executable(generic_linked_list_test
    generic_linked_list_test.c
    generic_linked_list.c
)

# Link the `invalid_frees` target with the required libraries
target_link_libraries(generic_linked_list_test PRIVATE
    argparse
    munit
)

# Include the required directories for the `invalid_frees` target
target_include_directories(generic_linked_list_test PRIVATE
    ${ARGPARSE_INCLUDE_DIR}
    ${MUNIT_INCLUDE_DIR}
)
