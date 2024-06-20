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
 * * generic_linked_list.h: created.
 *
 * ========================================================================== */


/* ==========================================================================
 * Header guard
 * ========================================================================== */

#ifndef GENERIC_LINKED_LIST_H
#define GENERIC_LINKED_LIST_H


/* ==========================================================================
 * Headers Include Section
 * ========================================================================== */

/* System headers */

/* Standard Library headers */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* External libraries headers */


/* ==========================================================================
 * Error Codes Section
 * ========================================================================== */

typedef enum {
  NO_ERROR,
  CALLOC_ERROR,
  DATA_TO_STRING_NULL,
  DATA_EQUALS_NULL,
  DESTINATION_BUFFER_NULL,
  DATA_NULL,
  LIST_NULL,
  INDEX_OUT_OF_BOUNDS,
  LIST_EMPTY
} GenericLLError;

static char const * const error_message[] = {
  "No error.",
  "Error allocating memory using calloc.",
  "Pointer to `data_to_string` function is NULL.",
  "Pointer to `data_equals` function is NULL.",
  "Pointer to destination buffer is NULL.",
  "Pointer to data is NULL.",
  "Pointer to list is NULL.",
  "Index out of bounds.",
  "List is empty."
};


/* ==========================================================================
 * Data Structures Section
 * ========================================================================== */

/* -------------------------------------------------------------------------- 
 * Structure: GenericLLNode
 * -------------------------------------------------------------------------- 
 * Description: 
 * 
 * Data members:
 *                   void *data: 
 *    struct generic_ll_node *next: 
 * 
 * Methods:
 * 
 * Usage:
 * 
 * -------------------------------------------------------------------------- */
typedef struct generic_ll_node {
    void *data;
    struct generic_ll_node *next;
} GenericLLNode;

/* -------------------------------------------------------------------------- 
 * Structure: GenericLL
 * -------------------------------------------------------------------------- 
 * Description: A generic linked list structure that uses a heap to store the
 *              elements. Linked list is implemented as a singly linked list.
 * 
 *              User must provide the following functions (mandatory) to work:
 *                 *data_to_string():  Converts the data to a string. It is
 *                                     used whenever the data needs to be 
 *                                     printed.
 *                    *data_equals():  Compares two data elements for equality.
 *                                     It is used to check if two data elements
 *                                     are equal, and for searching the linked
 *                                     list.
 * 
 *              User has to provide the following functions to compare the data
 *              elements (optional):
 *                           *data_less():  Compares two data elements and
 *                                          returns true if the first data
 *                                          element is less than the second data
 *                                          element. 
 *                        *data_greater():  Compares two data elements and
 *                                          returns true if the first data
 *                                          element is greater than the second
 *                                          data element.
 *                  *data_less_or_equal():  Compares two data elements and
 *                                          returns true if the first data
 *                                          element is less or equal to the
 *                                          second data element.
 *               *data_greater_or_equal():  Compares two data elements and
 *                                          returns true if the first data
 *                                          element is greater or equal to the
 *                                          second data element.
 * 
 *              If the user does not provide the optional functions, the linked
 *              list will not be able to sort the elements.
 * 
 * Data members:
 *    *head:                    Pointer to the head of the linked list.
 *    *tail:                    Pointer to the tail of the linked list.
 *    size:                     Number of elements in the linked list.
 *    *data_to_string():        Pointer to a function that converts the data to
 *                              a string.
 *    *data_equals():           Pointer to a function that compares two data
 *                              elements.
 *    *data_less():             Pointer to a function that compares two data 
 *                              elements.
 *    *data_greater():          Pointer to a function that compares two data 
 *                              elements.
 *    *data_less_or_equal():    Pointer to a function that compares two data
 *                              elements.
 *    *data_greater_or_equal(): Pointer to a function that compares two data
 *                              elements.
 *    *data_free():             Pointer to a function that frees the data. If
 *                              the pointer is NULL, the linked list will not
 *                              free the data, and it is the user's
 *                              responsibility to free the data.
 * 
 * Methods:
 * 
 * Usage:
 * 
 * -------------------------------------------------------------------------- */
typedef struct generic_ll {
    GenericLLNode *head;
    GenericLLNode *tail;
    size_t size;
    int (*data_to_string)(char **buffer, void *data, GenericLLError *error);
    bool (*data_equals)(void *data1, void *data2);
    bool (*data_less)(void *data1, void *data2);
    bool (*data_greater)(void *data1, void *data2);
    bool (*data_less_or_equal)(void *data1, void *data2);
    bool (*data_greater_or_equal)(void *data1, void *data2);
    void (*data_free)(void *data);
} GenericLL;


/* ==========================================================================
 * Function Prototypes Section
 * ========================================================================== */

/* -------------------------------------------------------------------------- 
 * Function: generic_ll_create_node
 * -------------------------------------------------------------------------- 
 * Description: Create a new node for the linked list.
 * 
 *              The function allocates memory for the new node and sets the
 *              data pointer to the data passed as an argument. The next
 *              pointer is set to NULL.
 * 
 *              The function returns a pointer to the new node.
 * 
 *              If the function fails to allocate memory for the new node, it
 *              returns NULL, and the error parameter is set to CALLOC_ERROR.
 *              If the error parameter is NULL, the function will not set the
 *              error parameter.
 * 
 *              This function is used internally by the linked list functions.
 *              It is not intended to be used by the user.
 * 
 * Parameters:
 *  - void *data: The data to be stored in the new node.
 *  - GenericLLError *error: A pointer to a GenericLLError variable to store
 *    the error code. If NULL, the function will not set the error parameter.
 * 
 * Returns:
 *  - GenericLLNode *: A pointer to the new node.
 * 
 * -------------------------------------------------------------------------- */
GenericLLNode *generic_ll_create_node(void *data, GenericLLError *error);

/* -------------------------------------------------------------------------
  * Function: generic_ll_create
  * -------------------------------------------------------------------------
  * 
  * Description: Create a generic linked list.
  * 
  *              The function creates a generic linked list and returns a
  *              pointer to it.
  * 
  *              The function also initializes the pointers to the functions
  *              that:
  *               - convert data to string.
  *               - compare two data for equality.
  *               - compare two data for less.
  *               - compare two data for greater.
  *               - compare two data for less or equal.
  *               - compare two data for greater or equal.
  *
  *               of which the pointers to first two functions are mandatory.
  *               First function is used to convert data to string, and is used
  *               for printing the data in the linked list. Second function is
  *               used to compare two data for equality, and is used for
  *               searching the linked list. If the pointers to the first two
  *               functions are NULL, the function returns NULL, and sets the
  *               error code to DATA_TO_STRING_NULL or DATA_EQUALS_NULL,
  *               respectively. Pointers to the rest of the functions can be
  *               NULL, and are used for sorting the linked list. If any of the
  *               pointers to the sorting functions are NULL, the lists sorting
  *               facilities (i.e. functions) are disabled.
  * 
  *               The function returns NULL if memory allocation fails, and sets
  *               the error code to CALLOC_ERROR.
  *
  * Parameters:
  *  - data_to_string: pointer to a function that converts data to string.
  *  - data_equals: pointer to a function that compares two data for equality.
  *  - data_less: pointer to a function that compares two data for less.
  *  - data_greater: pointer to a function that compares two data for greater.
  *  - data_less_or_equal: pointer to a function that compares two data for less
  *    or equal.
  *  - data_greater_or_equal: pointer to a function that compares two data for
  *    greater or equal.
  *  - data_free: pointer to a function that frees the data.
  *  - error: pointer to GenericLLError to store error code.
  *
  * Returns:
  * - GenericLL: pointer to the generic linked list.
  * 
  * ------------------------------------------------------------------------- */
GenericLL *generic_ll_create(
  int (*data_to_string)(char **buffer, void *data, GenericLLError *error),
  bool (*data_equals)(void *data1, void *data2),
  bool (*data_less)(void *data1, void *data2),
  bool (*data_greater)(void *data1, void *data2),
  bool (*data_less_or_equal)(void *data1, void *data2),
  bool (*data_greater_or_equal)(void *data1, void *data2),
  void (*data_free)(void *data),
  GenericLLError *error
);

GenericLL *generic_ll_push_front(
  GenericLL *list,
  void *data,
  GenericLLError *error
);

void generic_ll_free(GenericLL *list, GenericLLError *error);

void *generic_ll_get(GenericLL *list, size_t index, GenericLLError *error);

GenericLLNode *generic_ll_get_node(
  GenericLL *list,
  size_t index,
  GenericLLError *error
);

int generic_ll_to_string(
  char **buffer,
  GenericLL *list,
  GenericLLError *error
);

/* ==========================================================================
 * End of Header guard
 * ========================================================================== */

#endif  /* GENERIC_LINKED_LIST_H */

/* End of file generic_linked_list.h */