/* ==========================================================================
 *  Copyright (C) 2024 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * This file is part of "C Common Memory Errors".
 *
 * "C Common Memory Errors" is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * "C Common Memory Errors" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Focus Precision Analyze. If not, see <https://www.gnu.org/licenses/>.
 * ========================================================================== */


/* ==========================================================================
 *
 * 2024-05-29 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* External libraries headers */
#include <argparse.h>
#include <munit.h>


/* ==========================================================================
 * Macros Definitions Section
 * ========================================================================== */

#define APP_NAME "generic_linked_list_test"
#define APP_VERSION "1.0"
#define APP_AUTHOR "Ljubomir Kurij"
#define APP_EMAIL "ljubomir_kurij@protonmail.com"
#define APP_COPYRIGHT_YEAR "2024"
#define APP_COPYRIGHT_HOLDER APP_AUTHOR
#define APP_LICENSE "GPLv3+"
#define APP_LICENSE_URL "http://gnu.org/licenses/gpl.html"
#define APP_DESCRIPTION                                                        \
  "This code is to demonstrate and test the generic linked list implementation."
#ifdef _WIN32
#define APP_USAGE_A APP_NAME ".exe [OPTION]..."
#else
#define APP_USAGE_A APP_NAME " [OPTION]..."
#endif /* End of platform specific macro definition */
#define APP_EPILOGUE "\nReport bugs to <" APP_EMAIL ">."


/* ==========================================================================
 * Global Variables Section
 * ========================================================================== */

static const char *const kUsages[] = {
    APP_USAGE_A,
    NULL,
};


/* ==========================================================================
 * Utility Function Declarations Section
 * ========================================================================== */

int short_usage(struct argparse *self, const struct argparse_option *option);
int version_info(struct argparse *self, const struct argparse_option *option);


/* ==========================================================================
 * User Defined Function Declarations Section
 * ========================================================================== */

int int_to_string(char **buffer, void *data, GenericLLError *error);
bool data_equals(void *data1, void *data2);


/* ==========================================================================
 * Main Function Section
 * ========================================================================== */

int main(int argc, char **argv) {

  int usage = 0;
  int version = 0;

  /* Define command line options */
  struct argparse_option options[] = {
      OPT_GROUP("general options"),
      OPT_HELP(),
      OPT_BOOLEAN('\0', "usage", &usage, "give a short usage message",
                  &short_usage, 0, 0),
      OPT_BOOLEAN('V', "version", &version, "print program version",
                  &version_info, 0, 0),
      OPT_END(),
  };

  /* Parse command line arguments */
  struct argparse argparse;
  argparse_init(&argparse, options, kUsages, 0);
  argparse_describe(&argparse, APP_DESCRIPTION, APP_EPILOGUE);
  argc = argparse_parse(&argparse, argc, argv);

  /* Check if usage or version options were given */
  if (usage != 0 || version != 0) {
    exit(EXIT_SUCCESS);
  }

  /* Main module code */
  if (argc == 0) {
    /* No arguments were given */
    int data = 42;  /* Data to be stored in the node */
    char *buffer = NULL;  /* Buffer to store the string representation
                             of the data */
    GenericLLError error = NO_ERROR;  /* Error code */

    /* Print start message -------------------------------------------------- */
    printf("%s> Program execution started!\n", APP_NAME);

    /* Create a node and check if it was created successfully */
    GenericLLNode *node = generic_ll_create_node(&data, &error);
    munit_assert_int(NO_ERROR, ==, error);

    /* Generate string representation of the data and print it */
    int_to_string(&buffer, node->data, &error);
    munit_assert_int(NO_ERROR, ==, error);
    printf("%s> Data=%s\n", APP_NAME, buffer);

    /* Free the buffer */
    free(buffer);
    buffer = NULL;

    /* Create a linked list and check if it was created successfully */
    GenericLL *list = generic_ll_create(int_to_string, data_equals, NULL, NULL,
      NULL, NULL, &error);
    munit_assert_int(NO_ERROR, ==, error);

    /* Generate string representation of the empty linked list and print it */
    munit_assert_int(strlen("GenericLL(None)"), ==,
      generic_ll_to_string(&buffer, list, &error) - 1);

    /* Free the buffer */
    free(buffer);
    buffer = NULL;

    /* Add the node to the linked list */
    list->head = node;
    list->tail = node;
    list->size = 1;

    /* Generate string representation of the linked list and print it */
    munit_assert_int(strlen("GenericLL(42)"), ==,
      generic_ll_to_string(&buffer, list, &error) - 1);

    /* Free the buffer */
    free(buffer);
    buffer = NULL;

    if (NULL != buffer) {
      free(buffer);
    }
    if (NULL != node) {
      free(node);
    }
    /* End of main module code. Print exit message -------------------------- */
    printf("%s> Program execution complete!\n", APP_NAME);
  }

  return EXIT_SUCCESS;
}

/* ==========================================================================
 * Utility Function Definitions Section
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * Function: short_usage
 * --------------------------------------------------------------------------
 *
 * Description: Print a short usage message
 *
 * Parameters:
 *      self: Pointer to argparse structure
 *    option: Pointer to argparse option structure
 *
 * Returns: Number of characters printed
 *
 * -------------------------------------------------------------------------- */
int short_usage(struct argparse *self, const struct argparse_option *option) {
#ifdef _WIN32
  return fprintf(stdout, "%s %s\n%s%s%s\n", "Usage:", APP_USAGE_A, "Try `",
                 APP_NAME, ".exe -h' for more information.");
#else
  return fprintf(stdout, "%s %s\n%s%s%s\n", "Usage:", APP_USAGE_A, "Try `",
                 APP_NAME, " -h' for more information.");
#endif /* End of platform specific code */
}

/* --------------------------------------------------------------------------
 * Function: version_info
 * --------------------------------------------------------------------------
 *
 * Description: Print program version information
 *
 * Parameters:
 *      self: Pointer to argparse structure
 *    option: Pointer to argparse option structure
 *
 * Returns: Number of characters printed
 *
 * -------------------------------------------------------------------------- */
int version_info(struct argparse *self, const struct argparse_option *option) {
  return fprintf(stdout, "%s %s %s %s %s\n%s %s: %s <%s>\n%s\n%s\n", APP_NAME,
                 APP_VERSION, "Copyright (c)", APP_COPYRIGHT_YEAR, APP_AUTHOR,
                 "License", APP_LICENSE, "GNU GPL version 3 or later",
                 APP_LICENSE_URL,
                 "This is free software: you are free "
                 "to change and redistribute it.",
                 "There is NO WARRANTY, to the extent permitted by law.");
}

/* ==========================================================================
 * User Defined Function Definitions Section
 * ========================================================================== */

int int_to_string(char **buffer, void *data, GenericLLError *error) {
  int *int_data = (int *) data;
  int size = snprintf(NULL, 0, "%d", *int_data);
  *buffer = calloc(size + 1, sizeof(char));
  *error = NO_ERROR;

  if (*buffer == NULL) {
    *error = CALLOC_ERROR;

    return -1;
  }

  return snprintf(*buffer, size + 1, "%d", *int_data);
}

bool data_equals(void *data1, void *data2) {
  int *int_data1 = (int *)data1;
  int *int_data2 = (int *)data2;

  return *int_data1 == *int_data2;
}


/* End of file generic_linked_list_test.c */