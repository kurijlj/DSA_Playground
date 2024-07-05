/* ==========================================================================
 *  Copyright (C) 2024 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * This file is part of "Data Structures and Algorithms Playground".
 *
 * "Data Structures and Algorithms Playground" is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * "Data Structures and Algorithms Playground" is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Focus Precision Analyze. If not, see <https://www.gnu.org/licenses/>.
 * ========================================================================== */


/* ==========================================================================
 *
 * 2024-06-21 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * generic_linked_list_test.c: created.
 *
 * ========================================================================== */


/* ==========================================================================
 * Headers Include Section
 * ========================================================================== */

/* Related header */
#include "generic_linked_list.h"

/* System headers */

/* Standard Library headers */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* External libraries headers */
#include <munit.h>


/* ==========================================================================
 * Preprocessor Definitions Section
 * ========================================================================== */
#define MAX_TEST_NAME_SIZE 64


/* ==========================================================================
 * Global Variables Section
 * ========================================================================== */


/* ==========================================================================
 * Utility Function Declarations Section
 * ========================================================================== */

const char *expected_str_range(int *data, size_t start, size_t end);
const char *expected_str_list(int *data, size_t start, size_t end);


/* ==========================================================================
 * User Defined Function Declarations Section
 * ========================================================================== */

const char *int_str_repr(void *data, GLLError *error);
char data_compare(void *data1, void *data2);


/* ==========================================================================
 * Test Cases Section
 * ========================================================================== */

/* Tests cases -------------------------------------------------------------- */
void *create_node_fixture(const MunitParameter params[], void *user_data);
void free_node_fixture(void *fixture);
void *create_list_fixture(const MunitParameter params[], void *user_data);
void free_list_fixture(void *fixture);
void *create_dummy_fixture(const MunitParameter params[], void *user_data);
void free_dummy_fixture(void *fixture);

static MunitResult dummy_test(const MunitParameter params[], void* fixture);
static MunitResult create_node_test(const MunitParameter params[],
  void* fixture);
static MunitResult create_list_test(const MunitParameter params[],
  void* fixture);
static MunitResult free_list_test(const MunitParameter params[],
  void* fixture);
static MunitResult list_range_to_string_test(const MunitParameter params[],
  void* fixture);
static MunitResult list_to_string_test(const MunitParameter params[],
  void* fixture);

/* Tets array --------------------------------------------------------------- */
MunitTest tests[] = {
  {
    "/dummy-test", /* name */
    dummy_test, /* test */
    create_dummy_fixture, /* setup */
    free_dummy_fixture, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/create-node", /* name */
    create_node_test, /* test */
    create_node_fixture, /* setup */
    free_node_fixture, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/create-list", /* name */
    create_list_test, /* test */
    create_list_fixture, /* setup */
    free_list_fixture, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/free-list", /* name */
    free_list_test, /* test */
    create_list_fixture, /* setup */
    free_list_fixture, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/list-rts", /* name */
    list_range_to_string_test, /* test */
    create_list_fixture, /* setup */
    free_list_fixture, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/list-to-string", /* name */
    list_to_string_test, /* test */
    create_list_fixture, /* setup */
    free_list_fixture, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }  /* end of array */
};

/* Test suite --------------------------------------------------------------- */
static const MunitSuite test_suite = {
  "/generic_linked_list", /* name */
  tests, /* tests */
  NULL, /* suites */
  1, /* iterations */
  MUNIT_SUITE_OPTION_NONE /* options */
};


/* ==========================================================================
 * Main Function Section
 * ========================================================================== */

int main(int argc, char *argv[]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}


/* ==========================================================================
 * Utility Function Declarations Section
 * ========================================================================== */

const char *expected_str_range(int *data, size_t start, size_t end) {
  GLLError error = NO_ERROR;
  char *expected = NULL;
  int dl = 0;

  for (size_t i = start; i <= end; i++) {
    dl = snprintf(NULL, 0, "%d", *(data + i));
    if (i == start) {
      expected = gll_calloc(dl + 1, sizeof(char), &error);
      munit_assert_int(error, ==, NO_ERROR);
      munit_assert_ptr_not_null(expected);
      snprintf(expected, dl + 1, "%d", *(data + i));
    } else {
      size_t expected_len = strlen(expected);
      expected = gll_realloc(expected, expected_len + dl + 3, &error);
      munit_assert_int(error, ==, NO_ERROR);
      munit_assert_ptr_not_null(expected);
      snprintf(expected + expected_len, dl + 3, ", %d", *(data + i));
    }
    
    /* Reset data length */
    dl = 0;
  }

  return (const char *) expected;
}

const char *expected_str_list(int *data, size_t start, size_t end) {
  GLLError error = NO_ERROR;
  char *expected = NULL;

  if (7 >= end - start) {
    const char *data_str = NULL;
    size_t data_str_len = 0;

    data_str = expected_str_range(data, start, end);
    munit_assert_ptr_not_null(data_str);
    data_str_len = strlen(data_str);

    expected = gll_calloc(data_str_len + 10, sizeof(char), &error);
    munit_assert_int(error, ==, NO_ERROR);
    munit_assert_ptr_not_null(expected);

    snprintf(expected, data_str_len + 10, "GLLList(%s)", data_str);

    free((void *) data_str);

  } else {
    const char *data_str_a = NULL;
    const char *data_str_b = NULL;
    size_t data_str_len_a = 0;
    size_t data_str_len_b = 0;

    data_str_a = expected_str_range(data, start, start + 2);
    munit_assert_ptr_not_null(data_str_a);
    data_str_len_a = strlen(data_str_a);

    data_str_b = expected_str_range(data, end - 2, end);
    munit_assert_ptr_not_null(data_str_b);
    data_str_len_b = strlen(data_str_b);

    expected = gll_calloc(data_str_len_a + data_str_len_b + 17,
      sizeof(char), &error);
    munit_assert_int(error, ==, NO_ERROR);
    munit_assert_ptr_not_null(expected);

    snprintf(expected, data_str_len_a + data_str_len_b + 17,
      "GLLList(%s, ..., %s)", data_str_a, data_str_b);

    free((void *) data_str_a);
    free((void *) data_str_b);
  }

  return (const char *) expected;
}


/* ==========================================================================
 * User Defined Function Definitions Section
 * ========================================================================== */

const char *int_str_repr(void *data, GLLError *error) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  int *int_data = (int *) data;
  int size = snprintf(NULL, 0, "%d", *int_data);
  char *buffer = gll_calloc(size + 1, sizeof(char), error);

  if (NULL != buffer) {
    snprintf(buffer, size + 1, "%d", *int_data);
  }

  return buffer;
}

char data_compare(void *data1, void *data2) {
  int *int_data1 = (int *)data1;
  int *int_data2 = (int *)data2;

  if (*int_data1 < *int_data2) {
    return -1;
  } else if (*int_data1 > *int_data2) {
    return 1;
  }

  return 0;
}


/* ==========================================================================
 * Test Cases Definitions Section
 * ========================================================================== */

/* Fixture functions -------------------------------------------------------- */
void *create_dummy_fixture(const MunitParameter params[], void *user_data) {
  (MunitParameter *) params; /* unused */
  (void *) user_data; /* unused */

  munit_assert_int(42, ==, 42);
  return (void *) 42;
}

void free_dummy_fixture(void *fixture) {
  (void *) fixture; /* unused */
}

void *create_node_fixture(const MunitParameter params[], void *user_data) {
  (MunitParameter *) params; /* unused */
  (void *) user_data; /* unused */

  int data = 42;
  GLLError error = NO_ERROR;
  _GLLNode *node = _gll_new_node(&data, sizeof(int), &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(node);
  munit_assert_ptr_not_null(node->data);
  munit_assert_ptr_null(node->next);
  munit_assert_int(*(int *)node->data, ==, data);

  return (void *) node;
}

void free_node_fixture(void *fixture) {
  _GLLNode *node = (void *) fixture;
  _gll_free_node(node);
}

void *create_list_fixture(const MunitParameter params[], void *user_data) {
  (MunitParameter *) params; /* unused */
  (void *) user_data; /* unused */

  GLLError error = NO_ERROR;
  void *fixture = NULL;
  int *ref_data = NULL;

  /* Initialize the fixture */
  fixture = gll_calloc(5, sizeof(void *), &error);
  munit_assert_int(error, ==, NO_ERROR);

  /* Create an array with 1,000,000 elements */
  ref_data = gll_calloc(1000000, sizeof(int), &error);
  munit_assert_int(error, ==, NO_ERROR);
  for (size_t i = 0; i < 1000000; i++) {
    *(ref_data + i) = munit_rand_int_range(INT_MIN, INT_MAX);
  }

  /* Assign the reference data to the fixture */
  *((void **) fixture) = (void *) ref_data;
  
  /* Create an empty list */
  GLLList *list = gll_new_list(sizeof(int), int_str_repr, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);

  /* Assign the list to the fixture */
  *((void **) fixture + 1) = (void *) list;

  /* Create a one-element list */
  list = gll_new_list(sizeof(int), int_str_repr, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  _GLLNode *node = _gll_new_node(ref_data, sizeof(int), &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_int(*(int *)node->data, ==, *ref_data);
  list->head = node;
  list->tail = node;
  list->size = 1;

  /* Assign the list to the fixture */
  *((void **) fixture + 2) = (void *) list;

  /* Create a list with 10 elements */
  list = gll_new_list(sizeof(int), int_str_repr, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  for (size_t i = 0; i < 10; i++) {
    node = _gll_new_node(ref_data + i, sizeof(int), &error);
    munit_assert_int(error, ==, NO_ERROR);
    munit_assert_int(*(int *)node->data, ==, *(ref_data + i));
    if (i == 0) {
      list->head = node;
    } else {
      list->tail->next = node;
    }
    list->tail = node;
    list->size++;
  }

  /* Assign the list to the fixture */
  *((void **) fixture + 3) = (void *) list;

  /* Create a list with 1,000,000 elements */
  list = gll_new_list(sizeof(int), int_str_repr, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  for (size_t i = 0; i < 1000000; i++) {
    node = _gll_new_node(ref_data + i, sizeof(int), &error);
    munit_assert_int(error, ==, NO_ERROR);
    munit_assert_int(*(int *)node->data, ==, *(ref_data + i));
    if (i == 0) {
      list->head = node;
    } else {
      list->tail->next = node;
    }
    list->tail = node;
    list->size++;
  }

  /* Assign the list to the fixture */
  *((void **) fixture + 4) = (void *) list;

  return fixture;
}

void free_list_fixture(void *fixture) {
  if (NULL != fixture) {
    int *ref_data = (int *) *((void **) fixture);
    free(ref_data);
    for (size_t i = 1; i < 5; i++) {
      GLLList *list = (GLLList *) *((GLLList **) fixture + i);
      gll_free_list(list);
    }
    free(fixture);
  }
}

/* Dummy test -------------------------------------------------------------- */
static MunitResult dummy_test(
    const MunitParameter params[],
    void* fixture
  ) {
  (MunitParameter *) params; /* unused */
  (void *) fixture; /* unused */

  munit_assert_int(42, ==, 42);

  return MUNIT_OK;
}

/* _gll_create_node test ---------------------------------------------------- */
static MunitResult create_node_test(
    const MunitParameter params[],
    void* fixture
  ) {
  (MunitParameter *) params; /* unused */

  int data = 42;
  GLLError error = NO_ERROR;

  /* Test passing NULL data */
  _GLLNode *node = _gll_new_node(NULL, 0, &error);
  munit_assert_int(error, ==, DATA_NULL);
  munit_assert_ptr_null(node);

  /* Reset error */
  error = NO_ERROR;

  /* Test if the function to convert data to string works */
  node = (_GLLNode *) fixture;
  munit_assert_ptr_not_null(node);
  munit_assert_int(*(int *)node->data, ==, data);
  const char *buffer = int_str_repr(node->data, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_size(strlen(buffer), ==, strlen("42"));
  munit_assert_string_equal(buffer, "42");

  /* Clean up */
  free((void *) buffer);

  return MUNIT_OK;
}

/* gll_create_list test ----------------------------------------------------- */
static MunitResult create_list_test(
    const MunitParameter params[],
    void* fixture
  ) {
  (MunitParameter *) params; /* unused */

  GLLError error = NO_ERROR;

  /* Test passing zero data size */
  GLLList *list = gll_new_list(0, NULL, NULL, &error);
  munit_assert_int(error, ==, DATA_SIZE_ZERO);
  munit_assert_ptr_null(list);

  /* Reset error */
  error = NO_ERROR;

  /* Test passing NULL data_str */
  list = gll_new_list(sizeof(int), NULL, NULL, &error);
  munit_assert_int(error, ==, DATA_STR_NULL);
  munit_assert_ptr_null(list);

  /* Reset error */
  error = NO_ERROR;

  /* Test passing NULL data_compare */
  list = gll_new_list(sizeof(int), int_str_repr, NULL, &error);
  munit_assert_int(error, ==, DATA_COMPARE_NULL);
  munit_assert_ptr_null(list);

  /* Test creating a empty list */
  list = (GLLList *) *((GLLList **) fixture + 1);
  munit_assert_ptr_not_null(list);
  munit_assert_ptr_null(list->head);
  munit_assert_ptr_null(list->tail);
  munit_assert_size(list->size, ==, 0);

  /* Get the reference data */
  int *ref_data = (int *) *((void **) fixture);

  /* Test creating a list with one element */
  list = (GLLList *) *((GLLList **) fixture + 2);
  munit_assert_ptr_not_null(list);
  munit_assert_ptr_not_null(list->head);
  munit_assert_ptr_not_null(list->tail);
  munit_assert_size(list->size, ==, 1);
  munit_assert_int(*(int *)list->head->data, ==, *ref_data);

  /* Test creating a list with 10 elements */
  list = (GLLList *) *((GLLList **) fixture + 3);
  munit_assert_ptr_not_null(list);
  munit_assert_ptr_not_null(list->head);
  munit_assert_ptr_not_null(list->tail);
  munit_assert_size(list->size, ==, 10);
  _GLLNode *current = list->head;
  for (size_t i = 0; i < list->size; i++) {
    munit_assert_int(*(int *)current->data, ==, *(ref_data + i));
    current = current->next;
  }

  /* Test creating a list with 1,000,000 elements */
  list = (GLLList *) *((GLLList **) fixture + 4);
  munit_assert_ptr_not_null(list);
  munit_assert_ptr_not_null(list->head);
  munit_assert_ptr_not_null(list->tail);
  munit_assert_size(list->size, ==, 1000000);
  current = list->head;
  for (size_t i = 0; i < list->size; i++) {
    munit_assert_int(*(int *)current->data, ==, *(ref_data + i));
    current = current->next;
  }

  return MUNIT_OK;
}

/* gll_free test ------------------------------------------------------- */
static MunitResult free_list_test(
    const MunitParameter params[],
    void* fixture
  ) {
  (MunitParameter *) params; /* unused */
  (void *) fixture; /* unused */

  /* Test passing NULL list */
  gll_free_list(NULL);

  return MUNIT_OK;
}

/* _gll_list_str_range test ------------------------------------------------- */
static MunitResult list_range_to_string_test(
    const MunitParameter params[],
    void* fixture
  ) {
  (MunitParameter *) params; /* unused */

  GLLError error = NO_ERROR;
  GLLList *list = NULL;
  const char *buffer = NULL;
  const char *expected = NULL;

  /* Test passing NULL list ------------------------------------------------- */
  _gll_list_str_range(NULL, 0, 0, &error);
  munit_assert_int(error, ==, LIST_NULL);

  /* Reset error */
  error = NO_ERROR;

  /* Test passing an empty list --------------------------------------------- */
  list = (GLLList *) *((GLLList **) fixture + 1);
  _gll_list_str_range(list, 0, 0, &error);
  munit_assert_int(error, ==, LIST_EMPTY);

  /* Reset error */
  error = NO_ERROR;

  /* Get the reference data ------------------------------------------------- */
  int *ref_data = (int *) *((void **) fixture);

  /* Test one element list -------------------------------------------------- */
  list = (GLLList *) *((GLLList **) fixture + 2);

  /* Test passing a lower index out of range */
  _gll_list_str_range(list, 1, 0, &error);
  munit_assert_int(error, ==, LOWER_BOUND_OUT_OF_RANGE);

  /* Reset error */
  error = NO_ERROR;

  /* Test passing an upper index out of range */
  _gll_list_str_range(list, 0, 1, &error);
  munit_assert_int(error, ==, UPPER_BOUND_OUT_OF_RANGE);

  /* Reset error */
  error = NO_ERROR;

  /* Test with valid indexes */
  buffer = _gll_list_str_range(list, 0, 0, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(buffer);

  /* Format the expected string */
  expected = expected_str_range(ref_data, 0, 0);

  /* Clean up */
  gll_multi_free(2, buffer, expected);
  error = NO_ERROR;

  /* Test 10 elements list -------------------------------------------------- */
  list = (GLLList *) *((GLLList **) fixture + 3);

  /* Test passing a lower index greater than upper index */
  _gll_list_str_range(list, 7, 3, &error);
  munit_assert_int(error, ==, BOUNDS_INVERTED);

  /* Test for each element in the list */
  for (int i = 0; i < 10; i++) {
    buffer = _gll_list_str_range(list, i, i, &error);
    munit_assert_int(error, ==, NO_ERROR);
    munit_assert_ptr_not_null(buffer);

    /* Format the expected string */
    expected = expected_str_range(ref_data, i, i);

    /* Clean up */
    gll_multi_free(2, buffer, expected);
    error = NO_ERROR;
  }

  /* Test for first three elements */
  buffer = _gll_list_str_range(list, 0, 2, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(buffer);

  /* Format the expected string */
  expected = expected_str_range(ref_data, 0, 2);

  /* Compare buffer against expected */
  munit_assert_size(strlen(expected), ==, strlen(buffer));
  munit_assert_string_equal(expected, buffer);

  /* Clean up */
  gll_multi_free(2, buffer, expected);
  error = NO_ERROR;

  /* Test for last three elements */
  buffer = _gll_list_str_range(list, 7, 9, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(buffer);

  /* Format the expected string */
  expected = expected_str_range(ref_data, 7, 9);

  /* Compare buffer against expected */
  munit_assert_size(strlen(expected), ==, strlen(buffer));
  munit_assert_string_equal(expected, buffer);

  /* Clean up */
  gll_multi_free(2, buffer, expected);
  error = NO_ERROR;

  /* Test for first seven elements */
  buffer = _gll_list_str_range(list, 0, 6, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(buffer);

  /* Format the expected string */
  expected = expected_str_range(ref_data, 0, 6);

  /* Compare buffer against expected */
  munit_assert_size(strlen(expected), ==, strlen(buffer));
  munit_assert_string_equal(expected, buffer);

  /* Clean up */
  gll_multi_free(2, buffer, expected);
  error = NO_ERROR;

  return MUNIT_OK;
}

/* gll_list_str test -------------------------------------------------------- */
static MunitResult list_to_string_test(
    const MunitParameter params[],
    void* fixture
  ) {
  (MunitParameter *) params; /* unused */

  GLLError error = NO_ERROR;
  GLLList *list = NULL;
  const char *buffer = NULL;
  const char *expected = NULL;

  /* Test passing NULL list ------------------------------------------------- */
  gll_list_str(NULL, &error);
  munit_assert_int(error, ==, LIST_NULL);

  /* Reset error */
  error = NO_ERROR;

  /* Test passing an empty list --------------------------------------------- */
  expected = "GLLList(None)";
  list = (GLLList *) *((GLLList **) fixture + 1);
  buffer = gll_list_str(list, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(buffer);
  munit_assert_size(strlen(buffer), ==, strlen(expected));
  munit_assert_string_equal(buffer, expected);

  /* Clean up */
  gll_multi_free(1, buffer);
  error = NO_ERROR;

  /* Get the reference data ------------------------------------------------- */
  int *ref_data = (int *) *((void **) fixture);

  /* Test one element list -------------------------------------------------- */
  expected = expected_str_list(ref_data, 0, 0);
  list = (GLLList *) *((GLLList **) fixture + 2);
  buffer = gll_list_str(list, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(buffer);
  munit_assert_size(strlen(buffer), ==, strlen(expected));
  munit_assert_string_equal(buffer, expected);

  /* Clean up */
  gll_multi_free(2, buffer, expected);
  error = NO_ERROR;

  /* Test 10 elements list -------------------------------------------------- */
  expected = expected_str_list(ref_data, 0, 9);
  list = (GLLList *) *((GLLList **) fixture + 3);
  buffer = gll_list_str(list, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(buffer);
  munit_assert_size(strlen(buffer), ==, strlen(expected));
  munit_assert_string_equal(buffer, expected);

  /* Clean up */
  gll_multi_free(2, buffer, expected);
  error = NO_ERROR;

  /* Test one million elements list ----------------------------------------- */
  expected = expected_str_list(ref_data, 0, 999999);
  list = (GLLList *) *((GLLList **) fixture + 4);
  buffer = gll_list_str(list, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(buffer);
  munit_assert_size(strlen(buffer), ==, strlen(expected));
  munit_assert_string_equal(buffer, expected);

  /* Clean up */
  gll_multi_free(2, buffer, expected);
  error = NO_ERROR;

  return MUNIT_OK;
}


/* End of file generic_linked_list_test.c */