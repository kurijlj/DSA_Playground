# =============================================================================
# Build source targets
# =============================================================================

# Print message to console that we are building the source targets
message(STATUS "Going through ./generic_linked_list")


# -----------------------------------------------------------------------------
# Target: generic_heap_ll
# -----------------------------------------------------------------------------
#
# Description: Implementation of a generic linked list that uses a heap
#              allocation strategy.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `generic_heap_ll` target
message(STATUS "Configuring the `generic_heap_ll` target")

# Set the source files for the `generic_heap_ll` target
add_executable(generic_heap_ll_test generic_heap_ll_test.c generic_heap_ll.c)

# Link the `invalid_frees` target with the required libraries
target_link_libraries(generic_heap_ll_test PRIVATE
    argparse
)

# Include the required directories for the `invalid_frees` target
target_include_directories(generic_heap_ll_test PRIVATE
    ${ARGPARSE_INCLUDE_DIR}
)
