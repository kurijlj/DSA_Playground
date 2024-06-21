# =============================================================================
# Build test targets
# =============================================================================

# Print message to console that we are building the test targets
message(STATUS "Going through ./tests")

# Enable testing (this allows us to use the add_test() function)
enable_testing ()


# -----------------------------------------------------------------------------
# Target: generic_linked_list_test
# -----------------------------------------------------------------------------
#
# Description: A test suite for the generic linked list implementation.
#
# -----------------------------------------------------------------------------

# Show message that we are building the `generic_linked_list_test` target
message(STATUS "Configuring the `generic_linked_list_test` target")

# Set the source files for the 'generic_linked_list_test' target
add_executable(generic_linked_list_test
  generic_linked_list_test.c
  ${CMAKE_SOURCE_DIR}/src/datastructures/generic_linked_list/generic_linked_list.c
)

# Link the 'generic_linked_list_test' target with the 'munit' test framework
target_link_libraries(generic_linked_list_test PRIVATE
  munit
)

# Include the required directories for the `invalid_frees` target
target_include_directories(generic_linked_list_test PRIVATE
    ${MUNIT_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src/datastructures/generic_linked_list
)

# Add the 'generic_linked_list_test' target as a test
add_test(
  NAME generic_linked_list_test
  COMMAND generic_linked_list_test
)