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

int int_to_string(char **buffer, void *data, GenericLLError *error);
bool data_equals(void *data1, void *data2);


/* ==========================================================================
 * Test Cases Section
 * ========================================================================== */

/* Tests cases -------------------------------------------------------------- */
static MunitResult node_creation_test(const MunitParameter params[],
  void* fixture);
static MunitResult list_creation_test(const MunitParameter params[],
  void* fixture);
static MunitResult empty_list_test(const MunitParameter params[],
  void* fixture);
static void *empty_list_setup(const MunitParameter params[], void *user_data);
static void empty_list_tear_down(void *fixture);

/* Tets array --------------------------------------------------------------- */
MunitTest tests[] = {
  {
    "/node-creation", /* name */
    node_creation_test, /* test */
    NULL, /* setup */
    NULL, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/list-creation", /* name */
    list_creation_test, /* test */
    NULL, /* setup */
    NULL, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/empty-list", /* name */
    empty_list_test, /* test */
    empty_list_setup, /* setup */
    empty_list_tear_down, /* tear_down */
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

int int_to_string(char **buffer, void *data, GenericLLError *error) {
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

bool data_equals(void *data1, void *data2) {
  int *int_data1 = (int *)data1;
  int *int_data2 = (int *)data2;

  return *int_data1 == *int_data2;
}


/* ==========================================================================
 * Test Cases Definitions Section
 * ========================================================================== */

/* Node creation test ------------------------------------------------------- */
static MunitResult node_creation_test(
    const MunitParameter params[],
    void* fixture
  ) {
  (MunitParameter *) params; /* unused */
  (void *) fixture; /* unused */

  int data = 42;
  GenericLLError error = NO_ERROR;
  GenericLLNode *node = generic_ll_create_node(&data, sizeof(int), &error);

  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_not_null(node);
  munit_assert_ptr_not_equal(node->data, &data);
  munit_assert_int(*(int *)node->data, ==, data);

  generic_ll_node_free(node);

  return MUNIT_OK;
}

/* List creation test ------------------------------------------------------- */
static MunitResult list_creation_test(
    const MunitParameter params[],
    void* fixture
  ) {
  (MunitParameter *) params; /* unused */
  (void *) fixture; /* unused */

  GenericLLError error = NO_ERROR;
  GenericLL *list = generic_ll_create(int_to_string, data_equals, NULL,
    NULL, NULL, NULL, &error);

  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_not_null(list);
  munit_assert_null(list->head);
  munit_assert_null(list->tail);
  munit_assert_size(list->size, ==, 0);

  generic_ll_free(list);

  return MUNIT_OK;
}

/* Empty list test ---------------------------------------------------------- */
static MunitResult empty_list_test(
    const MunitParameter params[],
    void* fixture
  ) {
  (MunitParameter *) params; /* unused */

GenericLLError error = NO_ERROR;
  GenericLL *list = (GenericLL *) fixture;

  munit_assert_not_null(list);
  munit_assert_null(list->head);
  munit_assert_null(list->tail);
  munit_assert_size(list->size, ==, 0);

  /* Test pop_front on empty list */
  int *data = (int *) generic_ll_pop_front(list, &error);
  munit_assert_int(error, ==, LIST_EMPTY);
  munit_assert_null(data);
  munit_assert_null(list->head);
  munit_assert_null(list->tail);
  munit_assert_size(list->size, ==, 0);

  /* Reset error */
  error = NO_ERROR;

  /* Test pop_back on empty list */
  data = (int *) generic_ll_pop_back(list, &error);
  munit_assert_int(error, ==, LIST_EMPTY);
  munit_assert_null(data);
  munit_assert_null(list->head);
  munit_assert_null(list->tail);
  munit_assert_size(list->size, ==, 0);

  /* Reset error */
  error = NO_ERROR;

  /* Test delete_at_front on empty list */
  GenericLL *result = generic_ll_delete_at_front(list, &error);
  munit_assert_int(error, ==, LIST_EMPTY);
  munit_assert_ptr_equal(result, list);
  munit_assert_null(list->head);
  munit_assert_null(list->tail);
  munit_assert_size(list->size, ==, 0);

  /* Reset error */
  error = NO_ERROR;

  /* Test delete_at_back on empty list */
  result = generic_ll_delete_at_back(list, &error);
  munit_assert_int(error, ==, LIST_EMPTY);
  munit_assert_ptr_equal(result, list);
  munit_assert_null(list->head);
  munit_assert_null(list->tail);
  munit_assert_size(list->size, ==, 0);

  /* Reset error */
  error = NO_ERROR;

  /* Test is_empty on empty list */
  munit_assert_true(generic_ll_is_empty(list, &error));
  munit_assert_int(error, ==, NO_ERROR);

  /* Test size on empty list */
  munit_assert_size(generic_ll_size(list, &error), ==, 0);
  munit_assert_int(error, ==, NO_ERROR);

  /* Test contains on empty list */
  int value = 42;
  size_t index = generic_ll_contains(list, &value, &error);
  munit_assert_int(error, ==, LIST_EMPTY);
  munit_assert_size(index, ==, SIZE_MAX);

  /* Reset error */
  error = NO_ERROR;

  /* Test count_occurrences on empty list */
  size_t count = generic_ll_count_occurrences(list, &value, &error);
  munit_assert_int(error, ==, LIST_EMPTY);
  munit_assert_size(count, ==, 0);

  /* Reset error */
  error = NO_ERROR;

  /* Test get_data on empty list */
  data = (int *) generic_ll_get_data(list, 0, &error);
  munit_assert_int(error, ==, LIST_EMPTY);
  munit_assert_null(data);

  /* Reset error */
  error = NO_ERROR;

  /* Test get_node on empty list */
  GenericLLNode *node = generic_ll_get_node(list, 0, &error);
  munit_assert_int(error, ==, LIST_EMPTY);
  munit_assert_null(node);

  /* Reset error */
  error = NO_ERROR;

  /* Test to_string on empty list */
  char *str = NULL;
  int size = generic_ll_to_string(&str, list, &error);
  munit_assert_int(error, ==, NO_ERROR);
  munit_assert_string_equal(str, "GenericLL(None)");
  munit_assert_int(size - 1, ==, strlen("GenericLL(None)"));

  free(str);

  return MUNIT_OK;
}

static void *empty_list_setup(
    const MunitParameter params[],
    void *user_data
  ) {
  (MunitParameter *) params; /* unused */
  (void *) user_data; /* unused */

  GenericLLError error = NO_ERROR;
  GenericLL *list = generic_ll_create(int_to_string, data_equals, NULL,
    NULL, NULL, NULL, &error);

  return list;
}

static void empty_list_tear_down(void *fixture) {
  GenericLL *list = (GenericLL *) fixture;
  generic_ll_free(list);
}


/* End of file generic_linked_list_test.c */