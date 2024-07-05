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
#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* External libraries headers */


/* ==========================================================================
 * Algorithms Definitions Section
 * ========================================================================== */

_GLLNode *_gll_new_node(
    const void *data,
    const size_t data_size,
    GLLError *error
    ) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  if (NULL == data) {  /* Data is NULL */
    gll_set_err_code(error, DATA_NULL);
    return NULL;  /* ... nothing to do */
  }

  _GLLNode *node = gll_calloc(1, sizeof(_GLLNode), error);
  if (NULL == node) {
    return NULL;
  }

  node->data = gll_calloc(1, data_size, error);
  if (NULL == node) {
    free(node);  /* Release the node */
    return NULL;
  }

  /* Copy the data to the node */
  memcpy(node->data, data, data_size);

  return node;
}

GLLList *gll_new_list(
    const size_t data_size,
    const char *(*data_str)(void *data, GLLError *error),
    char (*data_compare)(void *data1, void *data2),
    GLLError *error
    ) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  if (0 == data_size) {  /* Don't know how many bytes to allocate */
    gll_set_err_code(error, DATA_SIZE_ZERO);
    return NULL;  /* ... bail out */
  }

  if (NULL == data_str) {  /* This is a must-have function */
    gll_set_err_code(error, DATA_STR_NULL);
    return NULL;  /* ... bail out */
  }

  if (NULL == data_compare) {  /* ... so is this one */
    gll_set_err_code(error, DATA_COMPARE_NULL);
    return NULL;  /* ... bail out */
  }

  GLLList *heap = gll_calloc(1, sizeof(GLLList), error);
  /* Check if memory allocation failed */
  if (NULL == heap) {  /* ... memory allocation failed */
    return NULL;  /* ... bail out */
  }

  /* Initialize the list */
  heap->data_size = data_size;
  heap->data_str = data_str;
  heap->data_compare = data_compare;

  return heap;
}

GLLList *gll_push_front(
    GLLList *list,
    const void *data,
    GLLError *error
  ) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* A guard clause to check if the list is NULL */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return list;
  }

  /* A guard clause to check if the data is NULL */
  if (NULL == data) {
    gll_set_err_code(error, DATA_NULL);
    return list;
  }

  _GLLNode *node = _gll_new_node(data, list->data_size, error);
  /* Check if memory allocation failed */
  if (NULL == node) {  /* ... memory allocation failed */
    return list;  /* ... bail out */
  }

  /* Put the new node at the front of the list */
  if (0 == list->size) {
    list->head = node;
    list->tail = node;
  } else {
    node->next = list->head;
    list->head = node;
  }

  list->size++;  /* Update the size of the list */

  return list;
}

GLLList *gll_push_back(
    GLLList *list,
    const void *data,
    GLLError *error
  ) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* A guard clause to check if the list is NULL */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return list;
  }

  /* A guard clause to check if the data is NULL */
  if (NULL == data) {
    gll_set_err_code(error, DATA_NULL);
    return list;
  }

  _GLLNode *node = _gll_new_node(data, list->data_size, error);
  /* Check if memory allocation failed */
  if (NULL == node) {  /* ... memory allocation failed */
    return list;  /* ... bail out */
  }

  /* Put the new node at the back of the list */
  if (0 == list->size) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }

  list->size++;  /* Update the size of the list */

  return list;
}

void *gll_pop_front(GLLList *list, GLLError *error) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* A guard clause to check if the list is NULL */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return list;
  }

  /* A guard clause to check if the list is empty */
  if (0 == list->size) { /* ... the list is empty */
    gll_set_err_code(error, LIST_EMPTY);
    return NULL;  /* ... nothing to do */
  }

  /* Detach the first node from the list */
  _GLLNode *node = list->head;
  if (1 == list->size) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    list->head = list->head->next;
  }

  list->size--;  /* ... update the size of the list */

  void *data = node->data;  /* ... get the data from the node */

  free(node);  /* ... release the node, but not the data */

  return data;  /* ... return the data */
}

GLLList *gll_delete_front(GLLList *list, GLLError *error) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* A guard clause to check if the list is NULL */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return list;
  }

  /* A guard clause to check if the list is empty */
  if (0 == list->size) { /* ... the list is empty */
    gll_set_err_code(error, LIST_EMPTY);
    return NULL;  /* ... nothing to do */
  }

  /* Detach the first node from the list */
  _GLLNode *node = list->head;
  if (1 == list->size) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    list->head = list->head->next;
  }

  list->size--;  /* ... update the size of the list */

  _gll_free_node(node);  /* ... release the node and the data */

  return list;
}

void *gll_pop_back(GLLList *list, GLLError *error) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* A guard clause to check if the list is NULL */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return list;
  }

  /* A guard clause to check if the list is empty */
  if (0 == list->size) { /* ... the list is empty */
    gll_set_err_code(error, LIST_EMPTY);
    return NULL;  /* ... nothing to do */
  }

  /* Detach the last node from the list */
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

  list->size--;  /* ... update the size of the list */

  void *data = node->data;  /* ... get the data from the node */

  free(node);  /* ... release the node, but not the data */

  return data;  /* ... return the data */
}

GLLList *gll_delete_at_back(GLLList *list, GLLError *error) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* A guard clause to check if the list is NULL */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return list;
  }

  /* A guard clause to check if the list is empty */
  if (0 == list->size) { /* ... the list is empty */
    gll_set_err_code(error, LIST_EMPTY);
    return NULL;  /* ... nothing to do */
  }

  /* Detach the last node from the list */
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

  list->size--;  /* ... update the size of the list */

  _gll_free_node(node);  /* ... release the node and the data */

  return list;  /* ... return the list */
}

void _gll_free_node(_GLLNode *node) {
  if (NULL == node) {  /* Nothing to do */
    return;
  }

  if (NULL != node->data) {  /* Release the data */
    free(node->data);
  }

  free(node);  /* ... release the node */
}

void gll_free_list(GLLList *list) {
  if (NULL == list) {  /* Nothing to do */
    return;
  }

  list->data_str = NULL;  /* Clear the data string function pointer */
  list->data_compare = NULL;  /* Clear the data compare function pointer */

  if (0 == list->size) {  /* ... so as here */
    free(list);

    return;
  }

  /* Release all the nodes in the list */
  _GLLNode *current = list->head;
  while (NULL != current) {
    _GLLNode *next = current->next;
    _gll_free_node(current);
    current = next;
  }

  free(list);  /* ... release the list */
}

bool gll_is_empty(GLLList *list, GLLError *error) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* A guard clause to check if the list is NULL */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return list;
  }

  return 0 == list->size;
}

size_t gll_size(GLLList *list, GLLError *error) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* A guard clause to check if the list is NULL */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return SIZE_MAX;
  }

  return list->size;
}

size_t gll_contains(
    GLLList *list,
    void *data,
    GLLError *error
  ) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* A guard clause to check if the list is NULL */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return SIZE_MAX;
  }

  /* A guard clause to check if the data is NULL */
  if (NULL == data) {
    gll_set_err_code(error, DATA_NULL);
    return SIZE_MAX;
  }

  /* A guard clause to check if the list is empty */
  if (0 == list->size) {
    gll_set_err_code(error, LIST_EMPTY);
    return SIZE_MAX;
  }

  /* Search for the data in the list */
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
  gll_set_err_code(error, DATA_NOT_FOUND);

  return SIZE_MAX;
}

size_t gll_occurrences(
    GLLList *list,
    void *data,
    GLLError *error
  ) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* Return zero if there is an error, or if the count is zero. */
  size_t count = 0;

  /* A guard clause to check if the list is NULL */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return count;
  }

  /* A guard clause to check if the data is NULL */
  if (NULL == data) {
    gll_set_err_code(error, DATA_NULL);
    return count;
  }

  /* A guard clause to check if the list is empty */
  if (0 == list->size) {
    gll_set_err_code(error, LIST_EMPTY);
    return count;
  }

  /* Count the occurrences of the data in the list */
  _GLLNode *current = list->head;
  while (NULL != current) {
    if (0 == list->data_compare(data, current->data)) {
      count++;
    }

    current = current->next;
  }

  return count;
}

void *gll_peek(GLLList *list, size_t index, GLLError *error) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* A guard clause to check if the list is NULL */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return NULL;
  }

  /* A guard clause to check if the list is empty */
  if (0 == list->size) {
    gll_set_err_code(error, LIST_EMPTY);
    return NULL;
  }

  /* A guard clause to check if the index is out of bounds */
  if (index < 0 || index >= list->size) {
    gll_set_err_code(error, INDEX_OUT_OF_RANGE);
    return NULL;
  }

  /* Get the data at the specified index */
  _GLLNode *current = list->head;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }

  /* ... copy the data to a new memory location */
  void *data = gll_calloc(1, list->data_size, error);
  if (NULL != data) {
    memcpy(data, current->data, list->data_size);
  }

  return data;  /* ... return the data */
}

_GLLNode *gll_get_node(
    GLLList *list,
    size_t index,
    GLLError *error
  ) {
  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* A guard clause to check if the list is NULL */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return NULL;
  }

  /* A guard clause to check if the list is empty */
  if (0 == list->size) {
    gll_set_err_code(error, LIST_EMPTY);
    return NULL;
  }

  /* A guard clause to check if the index is out of bounds */
  if (index < 0 || index >= list->size) {
    gll_set_err_code(error, INDEX_OUT_OF_RANGE);
    return NULL;
  }

  /* Get the node at the specified index */
  _GLLNode *current = list->head;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }

  return current;  /* ... return the node */
}

const char *gll_list_str(
    GLLList *list,
    GLLError *error
  ) {
  char *buffer = NULL;  /* Buffer for the string representation of the list */

  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* We can't do anything if the list is NULL ... */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return (const char *)buffer;  /* ... so we return NULL */
  }

  /* Try to allocate memory for the buffer */
  buffer = gll_calloc(9, sizeof(char), error);
  if (NULL == buffer) {
    return (const char *)buffer;  /* ... memory allocation failed */
  }

  snprintf(buffer, 9, "GLLList(");  /* List string prefix */

  if (0 == list->size) {
    strncat(buffer, "None)", strlen("None)"));  /* Empty list */
    return (const char *)buffer;  /* ... nothing more to do */
  }

  /* Data string buffer */
  char *data_str = NULL;

  /* If the list contains up to 7 elements, we populate the buffer with the
     data strings of the elements in the list.
   */
  if (list->size <= 7) {
    data_str = (char *) _gll_list_str_range(list, 0, list->size - 1, error);

    if (NULL == data_str) {  /* ... memory allocation failed */
      free(buffer);
      buffer = NULL;
      return (const char *) buffer;  /* ... bail out */
    }

    /* Add the data string to the buffer */
    strncat(buffer, data_str, strlen(data_str));
  } else {
    /* If the list contains more than 7 elements, we populate the buffer with
       the data strings of the first 3 elements, the last 3 elements, and the
       ellipsis in between.
     */
    data_str = (char *) _gll_list_str_range(list, 0, 2, error);

    if (NULL == data_str) {  /* ... memory allocation failed */
      free(buffer);
      buffer = NULL;
      return (const char *) buffer;  /* ... bail out */
    }

    /* Add the data string to the buffer */
    strncat(buffer, data_str, strlen(data_str));
    strncat(buffer, ", ... , ", 8);  /* Ellipsis */
    free(data_str);
    data_str = NULL;

    data_str = (char *) _gll_list_str_range(list, list->size - 3,
      list->size - 1, error);

    if (NULL == data_str) {  /* ... memory allocation failed */
      free(buffer);
      buffer = NULL;
      return (const char *)buffer;  /* ... bail out */
    }

    /* Add the data string to the buffer */
    strncat(buffer, data_str, strlen(data_str));
  }

  strncat(buffer, ")", 1);  /* List string postfix */

  return (const char *)buffer;
}

const char *_gll_list_str_range(
  GLLList *list,
  size_t start,
  size_t end,
  GLLError *error
) {
  char *dest_str = NULL;  /* Buffer for the string representation of the list */

  gll_set_err_code(error, NO_ERROR);  /* Clear error code */

  /* We can't do anything if the list is NULL ... */
  if (NULL == list) {
    gll_set_err_code(error, LIST_NULL);
    return (const char *) dest_str;  /* ... so we return NULL */
  }

  /* A guard clause to check if the list is empty */
  if (0 == list->size) {
    gll_set_err_code(error, LIST_EMPTY);
    return (const char *) dest_str;  /* ... bail out */
  }

  /* Check if the start index is out of bounds */
  if (start > list->size - 1) {
    gll_set_err_code(error, LOWER_BOUND_OUT_OF_RANGE);
    return (const char *) dest_str;  /* ... bail out */
  }

  /* Check if the end index is out of bounds */
  if (end > list->size - 1) {
    gll_set_err_code(error, UPPER_BOUND_OUT_OF_RANGE);
    return (const char *) dest_str;  /* ... bail out */
  }

  /* Check if the start index is greater than the end index */
  if (start > end) {
    gll_set_err_code(error, BOUNDS_INVERTED);
    return (const char *) dest_str;  /* ... bail out */
  }

  const char *data_str = NULL;  /* Data string buffer */

  /* Populate buffer with the data strings of the elements in the range */
  for(size_t i = start; end >= i; i++) {
    data_str = list->data_str(gll_get_node(list, i, NULL)->data, error);
    size_t data_str_len = strlen(data_str);

    if (NULL == data_str) {  /* ... memory allocation failed */
      if (NULL != dest_str) {
        free(dest_str);
        dest_str = NULL;
      }
      return (const char *) dest_str;  /* ... bail out */
    }

    /* Add the data string to the buffer */
    if (start == i) {  /* ... first element in the range */
      dest_str = gll_calloc(strlen(data_str) + 1, sizeof(char), error);

      if (NULL == dest_str) {  /* ... memory allocation failed */
        free(data_str);
        data_str = NULL;
        return (const char *) dest_str;  /* ... bail out */
      }

      /* Copy the data string to the buffer */
      snprintf(dest_str, data_str_len + 1, "%s", data_str);
    } else {
      size_t dest_str_len = strlen(dest_str);
      dest_str = gll_realloc(dest_str, dest_str_len + data_str_len + 3, error);
      snprintf(dest_str + dest_str_len, data_str_len + 3, ", %s", data_str);
    }

    /* Free the data string buffer */
    free((void *) data_str);
    data_str = NULL;
  }

  return (const char *) dest_str;
}

void gll_set_err_code(GLLError *status, GLLError code) {
  if (NULL != status) {
    *status = code;
  }
};

void *gll_calloc(size_t number, size_t size, GLLError *status) {
  void *buffer = calloc(number, size);

  if (NULL == buffer) {
    if (ENOMEM == errno) {
      gll_set_err_code(status, NO_MEMORY);
    } else {
      gll_set_err_code(status, UNKNOWN_ERROR);
    }
  }

  return buffer;
}

void *gll_realloc(void *ptr, size_t new_size, GLLError *status) {
  void *buffer = realloc(ptr, new_size);

  if (NULL == buffer) {
    if (ENOMEM == errno) {
      gll_set_err_code(status, NO_MEMORY);
    } else {
      gll_set_err_code(status, UNKNOWN_ERROR);
    }
  }

  return buffer;
}

void gll_multi_free(size_t count, ...) {
    va_list args;
    va_start(args, count);
    for (size_t i = 0; i < count; ++i) {
        void *buffer = va_arg(args, void *);
        if (NULL != buffer) {
            free(buffer);
        }
    }
    va_end(args);

    return;
}

/* End of generic_Linked_list.c */