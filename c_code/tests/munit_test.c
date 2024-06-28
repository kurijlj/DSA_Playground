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
 * 2024-06-28 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * munit_test.c: created.
 *
 * ========================================================================== */


/* ==========================================================================
 * Headers Include Section
 * ========================================================================== */

/* Related header */

/* System headers */

/* Standard Library headers */

/* External libraries headers */
#include <munit.h>


/* ==========================================================================
 * Preprocessor Definitions Section
 * ========================================================================== */


/* ==========================================================================
 * Global Variables Section
 * ========================================================================== */


/* ==========================================================================
 * Utility Function Declarations Section
 * ========================================================================== */


/* ==========================================================================
 * User Defined Function Declarations Section
 * ========================================================================== */


/* ==========================================================================
 * Test Cases Section
 * ========================================================================== */

static void *test_setup(const MunitParameter params[], void* user_data);
static void test_teardown(void* fixture);
static MunitResult test_example(const MunitParameter params[], void* fixture);

/* Tets array --------------------------------------------------------------- */
MunitTest tests[] = {
  {
    "/example", /* name */
    test_example, /* test */
    test_setup, /* setup */
    test_teardown, /* tear_down */
    MUNIT_TEST_OPTION_NONE, /* options */
    NULL /* parameters */
  },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

/* Test suite --------------------------------------------------------------- */
static const MunitSuite test_suite = {
  "/munit_test", /* name */
  tests, /* tests */
  NULL, /* suites */
  1, /* iterations */
  MUNIT_SUITE_OPTION_NONE /* options */
};


/* ==========================================================================
 * Main Function Section
 * ========================================================================== */

int main(int argc, char* argv[]) {
  return munit_suite_main(&test_suite, NULL, argc, argv);
}


/* ==========================================================================
 * Test Cases Definitions Section
 * ========================================================================== */

static void *test_setup(const MunitParameter params[], void* user_data) {
  (void) params;    /* unused */
  (void) user_data; /* unused */

  int *value = (int*)malloc(sizeof(int));
  if (value == NULL) {
    return NULL;
  }
  *value = 42;

  return value;
}

static void test_teardown(void* fixture) {
  if (fixture != NULL) {
    free(fixture);
  }
}

static MunitResult test_example(const MunitParameter params[], void* fixture) {
  (void) params; /* unused */

  if (fixture == NULL) {
    return MUNIT_ERROR;
  }

  munit_assert_int(*(int*)fixture, ==, 42);

  return MUNIT_OK;
}