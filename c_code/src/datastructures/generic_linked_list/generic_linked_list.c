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
  * Internal Declarations Section
 * ========================================================================== */

/* --------------------------------------------------------------------------
 * Function: _generic_ll_string_length
 * --------------------------------------------------------------------------
 * 
 * Description: Calculate the size of the string representation of the list.
 * 
 *              The string representation of the list is in the following form:
 * 
 *                GenericLL(data1, data2, data3, ..., dataN-2, dataN-1, dataN)
 * 
 *              where data1, data2, data3, ..., dataN-2, dataN-1, and dataN are
 *              the string representations of the data of the elements of the
 *              list. If the list is empty, the string representation is:
 * 
 *                GenericLL(None)
 * 
 *              If the list has less than eight elements, the string
 *              representation is in the following form:
 * 
 *                GenericLL(data1, data2, data3, data4, data5, data6, data7)
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
 *  - error: A pointer to a variable of type GenericLLError, where we store the
 *           error code if an error occurs.
 * 
 * Return: The size of the string representation of the list, or zero if an
 *         error occurs.
 * 
 * -------------------------------------------------------------------------- */
static int _generic_ll_string_length(
  GenericLL *list,
  GenericLLError *error
);


/* ==========================================================================
 * Algorithms Definitions Section
 * ========================================================================== */

/* Consider this instead ----------------------------------------------------
static Node *create_node(const void *data, size_t sizeof_data, int *error) {
    *error = 0;

    if (NULL == data) {
        *error = 1;

        return NULL;
    }

    if (0 == sizeof_data) {
        *error = 2;

        return NULL;
    }

    Node *node = calloc(1, sizeof(Node));
    if (NULL == node) {
        *error = 3;

        return NULL;
    }

    node->data = calloc(1, sizeof_data);
        if (NULL == node->data) {
        *error = 4;

        free(node);
        return NULL;
    }

    memcpy(node->data, data, sizeof_data);

    return node;
}
 * -------------------------------------------------------------------------- */
GenericLLNode *generic_ll_create_node(
    void *data, 
    GenericLLError *error
    ) {
  *error = NO_ERROR; /* Set error to default value */

  GenericLLNode *node = calloc(1, sizeof(GenericLLNode));
  if (node == NULL) {
    *error = CALLOC_ERROR;

    return NULL;
  }

  node->data = data;

  return node;

}

GenericLL *generic_ll_create(
    int (*data_to_string)(char **buffer, void *data, GenericLLError *error),
    bool (*data_equals)(void *data1, void *data2),
    bool (*data_less)(void *data1, void *data2),
    bool (*data_greater)(void *data1, void *data2),
    bool (*data_less_or_equal)(void *data1, void *data2),
    bool (*data_greater_or_equal)(void *data1, void *data2),
    void (*data_free)(void *data),
    GenericLLError *error
    ) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == data_to_string) {
    if (NULL != error) {
      *error = DATA_TO_STRING_NULL;
    }

    return NULL;
  }

  if (NULL == data_equals) {
    if (NULL != error) {
      *error = DATA_EQUALS_NULL;
    }

    return NULL;
  }

  GenericLL *heap = calloc(1, sizeof(GenericLL));
  if (heap == NULL) {
    if (NULL != error) {
      *error = CALLOC_ERROR;
    }

    return NULL;
  }

  heap->data_to_string = data_to_string;
  heap->data_equals = data_equals;
  heap->data_less = data_less;
  heap->data_greater = data_greater;
  heap->data_less_or_equal = data_less_or_equal;
  heap->data_greater_or_equal = data_greater_or_equal;
  heap->data_free = data_free;

  return heap;
}

GenericLL *generic_ll_push_front(
    GenericLL *list,
    void *data,
    GenericLLError *error
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

  GenericLLNode *node = generic_ll_create_node(data, error);
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

GenericLL *generic_ll_push_back(
    GenericLL *list,
    void *data,
    GenericLLError *error
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

  GenericLLNode *node = generic_ll_create_node(data, error);
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

void *generic_ll_pop_front(GenericLL *list, GenericLLError *error) {
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

  GenericLLNode *node = list->head;
  if (1 == list->size) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    list->head = list->head->next;
  }
  list->size--;

  void *data = node->data;
  free(node);
  return data;
}

GenericLL *generic_ll_delete_at_front(GenericLL *list, GenericLLError *error) {
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

  void *data = generic_ll_pop_front(list, error);
  if (NULL == data) {
    return list;
  }

  if (NULL != list->data_free) {
    list->data_free(data);
  }

  return list;
}

void *generic_ll_pop_back(GenericLL *list, GenericLLError *error) {
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

  GenericLLNode *node = list->tail;
  if (1 == list->size) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    GenericLLNode *current = list->head;
    while (current->next != list->tail) {
      current = current->next;
    }

    list->tail = current;
    list->tail->next = NULL;
  }

  list->size--;

  void *data = node->data;
  free(node);
  return data;
}

GenericLL *generic_ll_delete_at_back(GenericLL *list, GenericLLError *error) {
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

  void *data = generic_ll_pop_back(list, error);
  if (NULL == data) {
    return list;
  }

  if (NULL != list->data_free) {
    list->data_free(data);
  }

  return list;
}

void generic_ll_free(GenericLL *list, GenericLLError *error) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return;
  }

  if (0 == list->size) {
    free(list);

    return;
  }

  GenericLLNode *current = list->head;
  while (NULL != current) {
    GenericLLNode *next = current->next;
    if (NULL != list->data_free) {
      list->data_free(current->data);
    }
    free(current);
    current = next;
  }

  free(list);
}

bool generic_ll_is_empty(GenericLL *list, GenericLLError *error) {
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

size_t generic_ll_size(GenericLL *list, GenericLLError *error) {
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

bool generic_ll_contains(
    GenericLL *list,
    void *data,
    GenericLLError *error
  ) {
  if (NULL != error) {
    *error = NO_ERROR; /* Set error to default value */
  }

  if (NULL == list) {
    if (NULL != error) {
      *error = LIST_NULL;
    }

    return false;
  }

  if (NULL == data) {
    if (NULL != error) {
      *error = DATA_NULL;
    }

    return false;
  }

  GenericLLNode *current = list->head;
  while (NULL != current) {
    if (list->data_equals(data, current->data)) {
      return true;
    }

    current = current->next;
  }

  return false;
}

/* --------------------------------------------------------------------------
 * Function: generic_ll_count_occurrences
 * --------------------------------------------------------------------------
 * 
 * Description: Count the number of occurrences of the data in the list.
 * 
 *              If the list is NULL, the function returns zero and sets the
 *              error code to LIST_NULL.
 * 
 *              If the data is NULL, the function returns zero and sets the
 *              error code to DATA_NULL.
 * 
 *              If the list is empty, the function returns zero and sets the
 *              error code to LIST_EMPTY.
 * 
 *              If the error is NULL, the function does not set the error.
 * 
 * Parameters:
 *  - list: The list in which we count the occurrences of the data.
 *  - data: The data for which we count the occurrences.
 *  - error: A pointer to a variable of type GenericLLError, where we store the
 *           error code if an error occurs.
 * 
 * Return: The number of occurrences of the data in the list, or zero if an
 *         error occurs, or if the occurrence count is zero.
 * 
 * -------------------------------------------------------------------------- */
size_t generic_ll_count_occurrences(
    GenericLL *list,
    void *data,
    GenericLLError *error
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

  GenericLLNode *current = list->head;
  while (NULL != current) {
    if (list->data_equals(data, current->data)) {
      count++;
    }

    current = current->next;
  }

  return count;
}

void *generic_ll_get_data(GenericLL *list, size_t index, GenericLLError *error) {
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

  GenericLLNode *current = list->head;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }

  return current->data;
}

GenericLLNode *generic_ll_get_node(
    GenericLL *list,
    size_t index,
    GenericLLError *error
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

  GenericLLNode *current = list->head;
  for (size_t i = 0; i < index; i++) {
    current = current->next;
  }

  return current;
}

static int _generic_ll_string_length(GenericLL *list, GenericLLError *error) {
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

  size += 10; /* "GenericLL(" */

  if (0 == list->size) {
    size += 4;  /* "None" */
  } else {
    /* Calculate the size of the data of the first three or less elements */
    for(size_t i = 0; 3 > i && list->size > i; i++) {
      int data_str_size = list->data_to_string(
        &data_str,
        generic_ll_get_data(list, i, NULL),
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
            generic_ll_get_data(list, i, NULL),
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
            generic_ll_get_data(list, i, NULL),
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

int generic_ll_to_string(
    char **buffer,
    GenericLL *list,
    GenericLLError *error
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
  size = _generic_ll_string_length(list, error);

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
  offset += sprintf(*buffer + offset, "GenericLL(");

  if (0 == list->size) {
    offset += sprintf(*buffer + offset, "None");
  } else {
    char *data_str = NULL;  /* Buffer for the string representation of the data */

    /* Copy the string representation of the data of the first three or less 
       elements
    */
    for(size_t i = 0; 3 > i && list->size > i; i++) {
      int data_str_size = list->data_to_string(
        &data_str,
        generic_ll_get_data(list, i, NULL),
        error
      );

      if (data_str_size <= 0) {
        free(*buffer);
        *buffer = NULL;
        return 0;
      }

      offset += sprintf(*buffer + offset, "%s", data_str);
      free(data_str);
      data_str = NULL;

      if (list->size - 1 != i) {
        offset += sprintf(*buffer + offset, ", ");
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
            generic_ll_get_data(list, i, NULL),
            error
          );

          if (data_str_size <= 0) {
            free(*buffer);
            *buffer = NULL;
            return 0;
          }

          offset += sprintf(*buffer + offset, "%s", data_str);
          free(data_str);
          data_str = NULL;

          if(list->size - 1 > i) {
            offset += sprintf(*buffer + offset, ", ");
          }
        }
      } else {
        /* Copy the string representation of the data of the last three 
           elements, if list has more than seven elements. We use three dots to 
           indicate that there are more elements
        */
        offset += sprintf(*buffer + offset, "..., ");
        for(size_t i = list->size - 3; list->size > i; i++) {
          int data_str_size = list->data_to_string(
            &data_str,
            generic_ll_get_data(list, i, NULL),
            error
          );

          if (data_str_size <= 0) {
            free(*buffer);
            *buffer = NULL;
            return 0;
          }

          offset += sprintf(*buffer + offset, "%s", data_str);
          free(data_str);
          data_str = NULL;

          if(list->size - 1 > i) {
            offset += sprintf(*buffer + offset, ", ");
          }
        }
      }
    }
  }

  offset += sprintf(*buffer + offset, ")");

  return size;
}

/* End of generic_Linked_list.c */