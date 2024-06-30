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

int int_to_string(char **buffer, void *data, GLLError *error);
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

int int_to_string(char **buffer, void *data, GLLError *error) {
  if (NULL != error) {
    *error = NO_ERROR;
  }
  int *int_data = (int *) data;
  int size = snprintf(NULL, 0, "%d", *int_data);
  *buffer = calloc(size + 1, sizeof(char));

  if (*buffer == NULL) {
    if (NULL != error) {
      *error = CALLOC_ERROR;
    }

    return -1;
  }

  return snprintf(*buffer, size + 1, "%d", *int_data);
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
  _GLLNode *node = _gll_create_node(NULL, 0, &error);
  munit_assert_int(error, ==, DATA_NULL);
  munit_assert_ptr_null(node);

  /* Reset error */
  error = NO_ERROR;

  /* Test invoking with valid data */
  node = _gll_create_node(&data, sizeof(int), &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(node);
  munit_assert_ptr_not_null(node->data);
  munit_assert_ptr_null(node->next);
  munit_assert_int(*(int *)node->data, ==, data);

  /* Reset error */
  error = NO_ERROR;

  /* Test if the function to convert data to string works */
  char *buffer = NULL;
  int len = 0;
  len = int_to_string(&buffer, node->data, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_string_equal(buffer, "42");
  munit_assert_size(strlen(buffer), ==, len);

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
  GLLList *list = gll_create(0, NULL, NULL, &error);
  munit_assert_int(error, ==, DATA_SIZE_ZERO);
  munit_assert_ptr_null(list);

  /* Test passing NULL data_to_string */
  list = gll_create(sizeof(int), NULL, NULL, &error);
  munit_assert_int(error, ==, DATA_TO_STRING_NULL);
  munit_assert_ptr_null(list);

  /* Reset error */
  error = NO_ERROR;

  /* Test passing NULL data_compare */
  list = gll_create(sizeof(int), int_to_string, NULL, &error);
  munit_assert_int(error, ==, DATA_COMPARE_NULL);
  munit_assert_ptr_null(list);

  /* Reset error */
  error = NO_ERROR;

  /* Test invoking with valid pointers */
  list = gll_create(sizeof(int), int_to_string, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_ptr_not_null(list);
  munit_assert_ptr_null(list->head);
  munit_assert_ptr_null(list->tail);
  munit_assert_size(list->size, ==, 0);
  munit_assert_size(list->data_size, ==, sizeof(int));
  munit_assert_ptr_not_null(list->data_to_string);
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
  gll_free(NULL);

  /* Test passing an empty list */
  GLLError error = NO_ERROR;
  GLLList *list = gll_create(sizeof(int), int_to_string, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  gll_free(list);

  /* Test passing a list with one element */
  error = NO_ERROR;
  list = gll_create(sizeof(int), int_to_string, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  _GLLNode *node = _gll_create_node(&(int){42}, sizeof(int), &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_int(*((int *) node->data), ==, 42);
  list->head = node;
  list->tail = node;
  list->size = 1;
  gll_free(list);

  /* Test passing a list with multiple elements */
  error = NO_ERROR;
  list = gll_create(sizeof(int), int_to_string, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  for (int i = 0; i < 10; i++) {
    node = _gll_create_node(&(int){i}, sizeof(int), &error);
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
  gll_free(list);

  /* Test passing a list with huge number of elements */
  error = NO_ERROR;
  list = gll_create(sizeof(int), int_to_string, data_compare, &error);
  munit_assert_int(error, ==, NO_ERROR);
  for (int i = 0; i < 1000000; i++) {
    node = _gll_create_node(&(int){i}, sizeof(int), &error);
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
  gll_free(list);

  return MUNIT_OK;
}


/* End of file generic_linked_list_test.c */