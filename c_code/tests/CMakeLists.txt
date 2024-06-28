# =============================================================================
# Build test targets
# =============================================================================

# Print message to console that we are building the test targets
message(STATUS "Going through ./tests")

# Enable testing (this allows us to use the add_test() function)
enable_testing ()


# -----------------------------------------------------------------------------
# Target: munit_test
# -----------------------------------------------------------------------------
#
# Description: A dummy test target to perform memory checks for the 'munit'
#              library.
#
# -----------------------------------------------------------------------------

# Show message at what configuration stage we are
message(STATUS "Configuring the `munit_test` target")

# Source files
add_executable(munit_test
  munit_test.c
)

# Link required libraries
target_link_libraries(munit_test PRIVATE
  munit
)

# Set include directories
target_include_directories(munit_test PRIVATE
    ${MUNIT_INCLUDE_DIR}
)

# Add the test to the test suite
add_test(
  NAME munit_test
  COMMAND munit_test
)


# -----------------------------------------------------------------------------
# Target: generic_linked_list_test
# -----------------------------------------------------------------------------
#
# Description: A test suite for the generic linked list implementation.
#
# -----------------------------------------------------------------------------

# Show message at what configuration stage we are
message(STATUS "Configuring the `generic_linked_list_test` target")

# Source files
add_executable(generic_linked_list_test
  generic_linked_list_test.c
  ${CMAKE_SOURCE_DIR}/src/datastructures/generic_linked_list/generic_linked_list.c
)

# Link required libraries
target_link_libraries(generic_linked_list_test PRIVATE
  munit
)

# Set include directories
target_include_directories(generic_linked_list_test PRIVATE
    ${MUNIT_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src/datastructures/generic_linked_list
)

# Add the test to the test suite
add_test(
  NAME generic_linked_list_test
  COMMAND generic_linked_list_test
)
