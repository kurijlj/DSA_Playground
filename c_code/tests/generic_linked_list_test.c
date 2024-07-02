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


/* ==========================================================================
 * User Defined Function Declarations Section
 * ========================================================================== */

const char *int_str_repr(void *data, GLLError *error);
char data_compare(void *data1, void *data2);


/* ==========================================================================
 * Test Cases Section
 * ========================================================================== */

/* Tests cases -------------------------------------------------------------- */
static MunitResult create_node_test(const MunitParameter params[],
  void* fixture);
static MunitResult create_list_test(const MunitParameter params[],
  void* fixture);
static MunitResult free_list_test(const MunitParameter params[],
  void* fixture);
static MunitResult list_range_to_string_test(const MunitParameter params[],
  void* fixture);

/* Tets array --------------------------------------------------------------- */
MunitTest tests[] = {
  {
    "/create-node", /* name */
    create_node_test, /* test */
    NULL, /* setup */
    NULL, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/create-list", /* name */
    create_list_test, /* test */
    NULL, /* setup */
    NULL, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/free-list", /* name */
    free_list_test, /* test */
    NULL, /* setup */
    NULL, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/list-range-to-string", /* name */
    list_range_to_string_test, /* test */
    NULL, /* setup */
    NULL, /* tear_down */
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

/* _gll_create_node test ---------------------------------------------------- */
static MunitResult create_node_test(
    const MunitParameter params[],
    void* fixture
  ) {
  (MunitParameter *) params; /* unused */
  (void *) fixture; /* unused */

  int data = 42;
  GLLError error = NO_ERROR;

  /* Test passing NULL data */
  _GLLNode *node = _gll_new_node(NULL, 0, &error);
  munit_assert_int(error, ==, DATA_NULL);
  munit_assert_ptr_null(node);

  /* Reset error */
  error = NO_ERROR;

  /* Test invoking with valid data */
  node = _gll_new_node(&data, sizeof(int), &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(node);
  munit_assert_ptr_not_null(node->data);
  munit_assert_ptr_null(node->next);
  munit_assert_int(*(int *)node->data, ==, data);

  /* Reset error */
  error = NO_ERROR;

  /* Test if the function to convert data to string works */
  const char *buffer = int_str_repr(node->data, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_size(strlen(buffer), ==, strlen("42"));
  munit_assert_string_equal(buffer, "42");

  /* Clean up */
  free(node->data);
  free(node);

  return MUNIT_OK;
}

/* gll_create_list test ----------------------------------------------------- */
static MunitResult create_list_test(
    const MunitParameter params[],
    void* fixture
  ) {
  (MunitParameter *) params; /* unused */
  (void *) fixture; /* unused */

  GLLError error = NO_ERROR;

  /* Test passing zero data size */
  GLLList *list = gll_new_list(0, NULL, NULL, &error);
  munit_assert_int(error, ==, DATA_SIZE_ZERO);
  munit_assert_ptr_null(list);

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

  /* Reset error */
  error = NO_ERROR;

  /* Test invoking with valid pointers */
  list = gll_new_list(sizeof(int), int_str_repr, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(list);
  munit_assert_ptr_null(list->head);
  munit_assert_ptr_null(list->tail);
  munit_assert_size(list->size, ==, 0);
  munit_assert_size(list->data_size, ==, sizeof(int));
  munit_assert_ptr_not_null(list->data_str);
  munit_assert_ptr_not_null(list->data_compare);

  /* Clean up */
  free(list);

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

  /* Test passing an empty list */
  GLLError error = NO_ERROR;
  GLLList *list = gll_new_list(sizeof(int), int_str_repr, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  gll_free_list(list);

  /* Test passing a list with one element */
  error = NO_ERROR;
  list = gll_new_list(sizeof(int), int_str_repr, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  _GLLNode *node = _gll_new_node(&(int){42}, sizeof(int), &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_int(*((int *) node->data), ==, 42);
  list->head = node;
  list->tail = node;
  list->size = 1;
  gll_free_list(list);

  /* Test passing a list with multiple elements */
  error = NO_ERROR;
  list = gll_new_list(sizeof(int), int_str_repr, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  for (int i = 0; i < 10; i++) {
    node = _gll_new_node(&(int){i}, sizeof(int), &error);
    munit_assert_int(error, ==, NO_ERROR);
    munit_assert_int(*((int *) node->data), ==, i);
    if (i == 0) {
      list->head = node;
    } else {
      list->tail->next = node;
    }
    list->tail = node;
    list->size++;
  }
  gll_free_list(list);

  /* Test passing a list with huge number of elements */
  error = NO_ERROR;
  list = gll_new_list(sizeof(int), int_str_repr, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  for (int i = 0; i < 1000000; i++) {
    node = _gll_new_node(&(int){i}, sizeof(int), &error);
    munit_assert_int(error, ==, NO_ERROR);
    munit_assert_int(*((int *) node->data), ==, i);
    if (i == 0) {
      list->head = node;
    } else {
      list->tail->next = node;
    }
    list->tail = node;
    list->size++;
  }
  gll_free_list(list);

  return MUNIT_OK;
}

/* gll_to_string test ------------------------------------------------------- */
static MunitResult list_range_to_string_test(
    const MunitParameter params[],
    void* fixture
  ) {
  (MunitParameter *) params; /* unused */
  (void *) fixture; /* unused */

  GLLError error = NO_ERROR;

  /* Test passing NULL list */
  _gll_list_str_range(NULL, 0, 0, &error);
  munit_assert_int(error, ==, LIST_NULL);


  /* Test passing an empty list */
  error = NO_ERROR;
  GLLList *list = gll_new_list(sizeof(int), int_str_repr, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  _gll_list_str_range(list, 0, 0, &error);
  munit_assert_int(error, ==, LIST_EMPTY);

  /* Test one element list -------------------------------------------------- */
  gll_free_list(list);
  error = NO_ERROR;

  int data = munit_rand_int_range(-10000, 10000);
  _GLLNode *node = _gll_new_node(&data, sizeof(int), &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_int(*((int *) node->data), ==, data);
  list->head = node;
  list->tail = node;
  list->size = 1;

  /* Test passing a lower index out of range */
  _gll_list_str_range(list, 1, 0, &error);
  munit_assert_int(error, ==, LOWER_BOUND_OUT_OF_RANGE);

  /* Test passing an upper index out of range */
  error = NO_ERROR;
  _gll_list_str_range(list, 0, 1, &error);
  munit_assert_int(error, ==, UPPER_BOUND_OUT_OF_RANGE);

  /* Test with valid indexes */
  error = NO_ERROR;
  const char *buffer = _gll_list_str_range(list, 0, 0, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(buffer);

  int dl = snprintf(NULL, 0, "%d", data);
  char *expected = gll_calloc(dl + 1, sizeof(char), &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(expected);
  snprintf(expected, dl + 1, "%d", data);
  munit_assert_size(strlen(expected), ==, strlen(buffer));
  munit_assert_string_equal(expected, buffer);

  /* Test passing a list with 6 elements */

  /* Clean up */
  free(expected);
  free((void *) buffer);
  gll_free_list(list);

  return MUNIT_OK;
}


/* End of file generic_linked_list_test.c */