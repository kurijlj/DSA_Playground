/* ==========================================================================
 *  Copyright (C) 2024 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * This file is part of "DSA Playground".
 *
 * "DSA Playground" is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free 
 * Software Foundation, either version 3 of the License, or (at your option) 
 * any later version.
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
 * 2024-05-28 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * generic_Linked_list.c: created.
 *
 * ========================================================================== */


/* ==========================================================================
 * Headers Include Section
 * ========================================================================== */

/* Related header */
#include "generic_Linked_list.h"

/* System headers */

/* Standard Library headers */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* External libraries headers */


/* ==========================================================================
 * Algorithms Definitions Section
 * ========================================================================== */

heap_ll_node_t *heap_ll_node_create(
    void *data, 
    generic_ll_error_t *error
    ) {
  *error = NO_ERROR; /* Set error to default value */

  heap_ll_node_t *node = calloc(1, sizeof(heap_ll_node_t));
  if (node == NULL) {
    *error = CALLOC_ERROR;

    return NULL;
  }

  node->data = data;

  return node;

}

heap_ll_t *heap_ll_create(
    int (*data_to_string)(char **buffer, void *data, char const **error),
    bool (*data_equals)(void *data1, void *data2),
    bool (*data_less)(void *data1, void *data2),
    bool (*data_greater)(void *data1, void *data2),
    bool (*data_less_or_equal)(void *data1, void *data2),
    bool (*data_greater_or_equal)(void *data1, void *data2),
    generic_ll_error_t *error
    ) {
  *error = NO_ERROR; /* Set error to default value */

  if (NULL == data_to_string) {
    *error = DATA_TO_STRING_NULL;

    return NULL;
  }

  if (NULL == data_equals) {
    *error = DATA_EQUALS_NULL;

    return NULL;
  }

  heap_ll_t *heap = calloc(1, sizeof(heap_ll_t));
  if (heap == NULL) {
    *error = CALLOC_ERROR;

    return NULL;
  }

  heap->data_to_string = data_to_string;
  heap->data_equals = data_equals;
  heap->data_less = data_less;
  heap->data_greater = data_greater;
  heap->data_less_or_equal = data_less_or_equal;
  heap->data_greater_or_equal = data_greater_or_equal;

  return heap;
}


/* End of generic_Linked_list.c */