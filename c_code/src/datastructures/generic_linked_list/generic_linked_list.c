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
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* External libraries headers */


/* ==========================================================================
  * Internal Declarations Section
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * Function: _gll_string_length
 * --------------------------------------------------------------------------
 * 
 * Description: Calculate the size of the string representation of the list.
 * 
 *              The string representation of the list is in the following form:
 * 
 *                GLLList(data1, data2, data3, ..., dataN-2, dataN-1, dataN)
 * 
 *              where data1, data2, data3, ..., dataN-2, dataN-1, and dataN are
 *              the string representations of the data of the elements of the
 *              list. If the list is empty, the string representation is:
 * 
 *                GLLList(None)
 * 
 *              If the list has less than eight elements, the string
 *              representation is in the following form:
 * 
 *                GLLList(data1, data2, data3, data4, data5, data6, data7)
 * 
 *              If the list is NULL, the function returns zero and sets the
 *              error code to LIST_NULL.
 * 
 *              If the error is NULL, the function does not set the error.
 * 
 *              CAUTION: This function is for internal use only and should not
 *              be called from outside of the library.
 * 
 * Parameters:
 *  - list: The list for which we calculate the size of the string.
 *  - error: A pointer to a variable of type GLLError, where we store the
 *           error code if an error occurs.
 * 
 * Return: The size of the string representation of the list, or zero if an
 *         error occurs.
 * 
 * -------------------------------------------------------------------------- */
static int _gll_string_length(
  GLLList *list,
  GLLError *error
);


/* ==========================================================================
 * Algorithms Definitions Section
 * ========================================================================== */

_GLLNode *_gll_create_node(
    const void *data,
    const size_t data_size,
    GLLError *error
    ) {
  *error = NO_ERROR;

  if (NULL == data) {
      *error = DATA_NULL;

      return NULL;
  }

  _GLLNode *node = calloc(1, sizeof(_GLLNode));
  if (NULL == node) {
      *error = CALLOC_ERROR;

      return NULL;
  }

  node->data = calloc(1, data_size);
      if (NULL == node->data) {
      *error = CALLOC_ERROR;

      free(node);
      return NULL;
  }

  memcpy(node->data, data, data_size);

  return node;
}

GLLList *gll_create(
    const size_t data_size,
    int (*data_to_string)(char **buffer, void *data, GLLError *error),
    char (*data_compare)(void *data1, void *data2),
    GLLError *error
    ) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (0 == data_size) {
    if (NULL != error) {
      *error = DATA_SIZE_ZERO;
    }

    return NULL;
  }

  if (NULL == data_to_string) {
    if (NULL != error) {
      *error = DATA_TO_STRING_NULL;
    }

    return NULL;
  }

  if (NULL == data_compare) {
    if (NULL != error) {
      *error = DATA_COMPARE_NULL;
    }

    return NULL;
  }

  GLLList *heap = calloc(1, sizeof(GLLList));
  if (heap == NULL) {
    if (NULL != error) {
      *error = CALLOC_ERROR;
    }

    return NULL;
  }

  heap->data_size = data_size;
  heap->data_to_string = data_to_string;
  heap->data_compare = data_compare;

  return heap;
}

GLLList *gll_push_front(
    GLLList *list,
    const void *data,
    GLLError *error
  ) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return list;
  }

  if (NULL == data) {
    if (NULL != error) {
      *error = DATA_NULL;
    }

    return list;
  }

  _GLLNode *node = _gll_create_node(data, list->data_size, error);
  if (NULL == node) {
    return list;
  }

  if (0 == list->size) {
    list->head = node;
    list->tail = node;
  } else {
    node->next = list->head;
    list->head = node;
  }

  list->size++;

  return list;
}

GLLList *gll_push_back(
    GLLList *list,
    const void *data,
    GLLError *error
  ) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return list;
  }

  if (NULL == data) {
    if (NULL != error) {
      *error = DATA_NULL;
    }

    return list;
  }

  _GLLNode *node = _gll_create_node(data, list->data_size, error);
  if (NULL == node) {
    return list;
  }

  if (0 == list->size) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }

  list->size++;

  return list;
}

void *gll_pop_front(GLLList *list, GLLError *error) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return NULL;
  }

  if (0 == list->size) {
    if (NULL != error) {
      *error = LIST_EMPTY;
    }

    return NULL;
  }

  _GLLNode *node = list->head;
  if (1 == list->size) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    list->head = list->head->next;
  }
  list->size--;

  void *data = calloc(1, list->data_size);
  if (NULL == data) {
    if (NULL != error) {
      *error = CALLOC_ERROR;
    }

    return NULL;
  }

  memcpy(data, node->data, list->data_size);

  free(node->data);
  free(node);

  return data;
}

GLLList *gll_delete_at_front(GLLList *list, GLLError *error) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return list;
  }

  if (0 == list->size) {
    if (NULL != error) {
      *error = LIST_EMPTY;
    }

    return list;
  }

  _GLLNode *node = list->head;
  if (1 == list->size) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    list->head = list->head->next;
  }
  list->size--;

  gll_node_free(node);

  return list;
}

void *gll_pop_back(GLLList *list, GLLError *error) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return NULL;
  }

  if (0 == list->size) {
    if (NULL != error) {
      *error = LIST_EMPTY;
    }

    return NULL;
  }

  _GLLNode *node = list->tail;
  if (1 == list->size) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    _GLLNode *current = list->head;
    while (current->next != list->tail) {
      current = current->next;
    }

    list->tail = current;
    list->tail->next = NULL;
  }
  list->size--;

  void *data = calloc(1, list->data_size);
  if (NULL == data) {
    if (NULL != error) {
      *error = CALLOC_ERROR;
    }

    return NULL;
  }

  memcpy(data, node->data, list->data_size);

  free(node->data);
  free(node);

  return data;
}

GLLList *gll_delete_at_back(GLLList *list, GLLError *error) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return list;
  }

  if (0 == list->size) {
    if (NULL != error) {
      *error = LIST_EMPTY;
    }

    return list;
  }

  _GLLNode *node = list->tail;
  if (1 == list->size) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    _GLLNode *current = list->head;
    while (current->next != list->tail) {
      current = current->next;
    }

    list->tail = current;
    list->tail->next = NULL;
  }
  list->size--;

  gll_node_free(node);

  return list;
}

void gll_node_free(_GLLNode *node) {
  if (NULL == node) {
    return;
  }

  if (NULL != node->data) {
    free(node->data);
  }

  free(node);
}

void gll_free(GLLList *list) {
  if (NULL == list) {
    return;
  }

  if (0 == list->size) {
    free(list);

    return;
  }

  _GLLNode *current = list->head;
  while (NULL != current) {
    _GLLNode *next = current->next;
    gll_node_free(current);
    current = next;
  }

  free(list);
}

bool gll_is_empty(GLLList *list, GLLError *error) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return false;
  }

  return 0 == list->size;
}

size_t gll_size(GLLList *list, GLLError *error) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return 0;
  }

  return list->size;
}

size_t gll_contains(
    GLLList *list,
    void *data,
    GLLError *error
  ) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return SIZE_MAX;
  }

  if (NULL == data) {
    if (NULL != error) {
      *error = DATA_NULL;
    }

    return SIZE_MAX;
  }

  if (0 == list->size) {
    if (NULL != error) {
      *error = LIST_EMPTY;
    }

    return SIZE_MAX;
  }

  _GLLNode *current = list->head;
  size_t index = 0;
  while (NULL != current) {
    if (0 == list->data_compare(data, current->data)) {
      return index;
    }

    current = current->next;
    index++;
  }

  /* If we reach this point, the data is not in the list */
  if (NULL != error) {
    *error = DATA_NOT_FOUND;
  }

  return SIZE_MAX;
}

size_t gll_count_occurrences(
    GLLList *list,
    void *data,
    GLLError *error
  ) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  size_t count = 0;  /* We return zero if there is an error, or if the
                        occurrence count is zero.
                     */

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return count;
  }

  if (NULL == data) {
    if (NULL != error) {
      *error = DATA_NULL;
    }

    return count;
  }

  if (0 == list->size) {
    if (NULL != error) {
      *error = LIST_EMPTY;
    }

    return count;
  }

  _GLLNode *current = list->head;
  while (NULL != current) {
    if (0 == list->data_compare(data, current->data)) {
      count++;
    }

    current = current->next;
  }

  return count;
}

void *gll_get_data(GLLList *list, size_t index, GLLError *error) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return NULL;
  }

  if (0 == list->size) {
    if (NULL != error) {
      *error = LIST_EMPTY;
    }

    return NULL;
  }

  if (index < 0 || index >= list->size) {
    if (NULL != error) {
      *error = INDEX_OUT_OF_BOUNDS;
    }

    return NULL;
  }

  _GLLNode *current = list->head;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }

  void *data = calloc(1, list->data_size);
  if (NULL == data) {
    if (NULL != error) {
      *error = CALLOC_ERROR;
    }

    return NULL;
  }

  memcpy(data, current->data, list->data_size);

  return data;
}

_GLLNode *gll_get_node(
    GLLList *list,
    size_t index,
    GLLError *error
  ) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return NULL;
  }

  if (0 == list->size) {
    if (NULL != error) {
      *error = LIST_EMPTY;
    }

    return NULL;
  }

  if (index < 0 || index >= list->size) {
    if (NULL != error) {
      *error = INDEX_OUT_OF_BOUNDS;
    }

    return NULL;
  }

  _GLLNode *current = list->head;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }

  return current;
}

static int _gll_string_length(GLLList *list, GLLError *error) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }
  int size = 0;  /* We return zero if there is an error */

  /* We can't do anything if the list is NULL */
  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return size;
  }

  char *data_str = NULL;  /* Buffer for the string representation of the data */

  size += 10; /* "GLLList(" */

  if (0 == list->size) {
    size += 4;  /* "None" */
  } else {
    /* Calculate the size of the data of the first three or less elements */
    for(size_t i = 0; 3 > i && list->size > i; i++) {
      int data_str_size = list->data_to_string(
        &data_str,
        gll_get_data(list, i, NULL),
        error
      );

      if (data_str_size <= 0) {
        size = 0;
        return size;
      }

      size += data_str_size;
      free(data_str);
      data_str = NULL;

      if (list->size - 1 != i) {
        size += 2; /* ", " */
      }
    }

    /* Calculate the size of the data of rest of the elements, if there are 
       more than three
    */
    if (3 < list->size) {
      if (8 > list->size) {
        /* Calculate the size of the data of the rest of the elements, if list 
           has up to seven elements
        */
        for(size_t i = 3; list->size > i; i++) {
          int data_str_size = list->data_to_string(
            &data_str,
            gll_get_data(list, i, NULL),
            error
          );

          if (data_str_size <= 0) {
            size = 0;
            return size;
          }

          size += data_str_size;
          free(data_str);
          data_str = NULL;

          if(list->size - 1 > i) {
            size += 2; /* ", " */
          }
        }
      } else {
        /* Calculate the size of the data of the last three elements, if list 
           has more than seven elements. We use three dots to indicate that
           there are more elements
        */
        size += 5; /* "..., " */
        for(size_t i = list->size - 3; list->size > i; i++) {
          int data_str_size = list->data_to_string(
            &data_str,
            gll_get_data(list, i, NULL),
            error
          );

          if (data_str_size <= 0) {
            size = 0;
            return size;
          }

          size += data_str_size;
          free(data_str);
          data_str = NULL;

          if(list->size - 1 > i) {
            size += 2; /* ", " */
          }
        }
      }
    }
  }

  size += 2; /* ")" */

  return size;
}

int gll_to_string(
    char **buffer,
    GLLList *list,
    GLLError *error
  ) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }
  int size = 0;  /* We return zero if there is an error */

  /* We can't do anything if the list is NULL ... */
  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return size;
  }

  /* ... or if the buffer is NULL */
  if (NULL == buffer) {
    if (NULL != error) {
      *error = DESTINATION_BUFFER_NULL;
    }

    return size;
  }

  /* First we need to calculate the size of the buffer */
  size = _gll_string_length(list, error);

  if (size <= 0) {
    return size;
  }

  /* Allocate memory for the buffer */
  *buffer = calloc(size, sizeof(char));
  if (NULL == *buffer) {
    if (NULL != error) {
      *error = CALLOC_ERROR;
    }

    return 0;
  }

  /* Copy the string representation of the list to the buffer */
  int offset = 0;
  offset += snprintf(*buffer + offset, 11, "GLLList(");

  if (0 == list->size) {
    offset += snprintf(*buffer + offset, 5, "None");
  } else {
    char *data_str = NULL;  /* Buffer for the string representation of the data */

    /* Copy the string representation of the data of the first three or less 
       elements
    */
    for(size_t i = 0; 3 > i && list->size > i; i++) {
      int data_str_size = list->data_to_string(
        &data_str,
        gll_get_data(list, i, NULL),
        error
      );

      if (data_str_size <= 0) {
        free(*buffer);
        *buffer = NULL;
        return 0;
      }

      offset += snprintf(*buffer + offset, data_str_size + 1, "%s", data_str);
      free(data_str);
      data_str = NULL;

      if (list->size - 1 != i) {
        offset += snprintf(*buffer + offset, 3, ", ");
      }
    }

    /* Copy the string representation of the data of rest of the elements, if 
       there are more than three
    */
    if (3 < list->size) {
      if (8 > list->size) {
        /* Copy the string representation of the data of the rest of the 
           elements, if list has up to seven elements
        */
        for(size_t i = 3; list->size > i; i++) {
          int data_str_size = list->data_to_string(
            &data_str,
            gll_get_data(list, i, NULL),
            error
          );

          if (data_str_size <= 0) {
            free(*buffer);
            *buffer = NULL;
            return 0;
          }

          offset += snprintf(
            *buffer + offset,
            data_str_size + 1, 
            "%s", 
            data_str
            );
          free(data_str);
          data_str = NULL;

          if(list->size - 1 > i) {
            offset += snprintf(*buffer + offset, 3, ", ");
          }
        }
      } else {
        /* Copy the string representation of the data of the last three 
           elements, if list has more than seven elements. We use three dots to 
           indicate that there are more elements
        */
        offset += snprintf(*buffer + offset, 6, "..., ");
        for(size_t i = list->size - 3; list->size > i; i++) {
          int data_str_size = list->data_to_string(
            &data_str,
            gll_get_data(list, i, NULL),
            error
          );

          if (data_str_size <= 0) {
            free(*buffer);
            *buffer = NULL;
            return 0;
          }

          offset += snprintf(
            *buffer + offset,
            data_str_size + 1,
            "%s", 
            data_str
            );
          free(data_str);
          data_str = NULL;

          if(list->size - 1 > i) {
            offset += snprintf(*buffer + offset, 3, ", ");
          }
        }
      }
    }
  }

  offset += snprintf(*buffer + offset, 2, ")");

  return size;
}

/* End of generic_Linked_list.c */