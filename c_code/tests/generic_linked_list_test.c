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

/* User defined utility data structures ------------------------------------- */
typedef struct {
  const char *test_name;
  void *data;
  size_t data_size;
} Testload;

/* Test data ---------------------------------------------------------------- */
int pl1[] = {42};

static Testload testloads[] = {
  {
    "node-creation",              /* test_name */
    pl1,                          /* data */
    sizeof(pl1) / sizeof(pl1[0])  /* data_size */
  },
  {NULL, NULL, 0}  /* End of the array */
};

/* Tests cases -------------------------------------------------------------- */
MunitResult node_creation(const MunitParameter params[], void* fixture);
MunitResult list_creation(const MunitParameter params[], void* fixture);

/* Tets array --------------------------------------------------------------- */
MunitTest tests[] = {
  {
    "/node-creation", /* name */
    node_creation, /* test */
    NULL, /* setup */
    NULL, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  {
    "/list-creation", /* name */
    list_creation, /* test */
    NULL, /* setup */
    NULL, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },

  /* Mark the end of the array with an entry where the test
   * function is NULL */
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
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
  return munit_suite_main(&test_suite, testloads, argc, argv);
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

MunitResult node_creation(const MunitParameter params[], void* input_data) {
  (MunitParameter *) params; /* unused */
  Testload *testload = (Testload *) input_data;

  /* Check if the input data is NULL */
  munit_assert_not_null(testloads);

  /* Search for the our test data in the payloads array */
  while (NULL != testload->test_name) {
    if (0 == strncmp(
      testload->test_name,
      "node-creation",
      MAX_TEST_NAME_SIZE
    )) {
      break;
    }

    testload++;
  }

  /* Check if we found our test data */
  munit_assert_not_null(testload->test_name);

  /* We found our test data. Now we can run the test */
  GenericLLError error = NO_ERROR;

  GenericLLNode *node = generic_ll_create_node(testload->data, &error);
  munit_assert_not_null(node);
  munit_assert_int(error, ==, NO_ERROR);
  free(node);

  return MUNIT_OK;
}

MunitResult list_creation(const MunitParameter params[], void* input_data) {
  (MunitParameter *) params; /* unused */
  (void *) input_data;       /* unused */

  return MUNIT_OK;
}


/* End of file generic_linked_list_test.c */