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

typedef enum _generic_ll_error {
  NO_ERROR,
  CALLOC_ERROR,
  DATA_SIZE_ZERO,
  DATA_TO_STRING_NULL,
  DATA_COMPARE_NULL,
  DESTINATION_BUFFER_NULL,
  DATA_NULL,
  LIST_NULL,
  INDEX_OUT_OF_BOUNDS,
  LIST_EMPTY,
  DATA_NOT_FOUND
} GLLError;

static char const * const gll_error_message[] = {
  "No error.",
  "Error allocating memory using calloc.",
  "Data size is set to zero.",
  "Pointer to `data_to_string` function is NULL.",
  "Pointer to `data_compare` function is NULL.",
  "Pointer to destination buffer is NULL.",
  "Pointer to data is NULL.",
  "Pointer to list is NULL.",
  "Index out of bounds.",
  "List is empty.",
  "Data not found."
};


/* ==========================================================================
 * Data Structures Section
 * ========================================================================== */

/* -------------------------------------------------------------------------- 
 * Structure: _GLLNode
 * -------------------------------------------------------------------------- 
 * Description: 
 * 
 * Data members:
 *            void *data: Pointer to the data stored in the node.
 *   _GLLNode *next: Pointer to the next node in the linked list.
 * 
 * Methods:
 * 
 * Usage:
 * 
 * -------------------------------------------------------------------------- */
typedef struct _gll_node {
    void *data;
    struct _gll_node *next;
} _GLLNode;

/* -------------------------------------------------------------------------- 
 * Structure: GLLList
 * -------------------------------------------------------------------------- 
 * Description: A generic linked list structure that uses a heap to store the
 *              elements. Linked list is implemented as a singly linked list.
 * 
 *              User must provide the following functions (mandatory) to work:
 *                 *data_to_string():  Converts the data to a string. It is
 *                                     used whenever the data needs to be 
 *                                     printed.
 *                   *data_compare():  Compares two data elements and returns
 *                                     -1 if the first data element is less than
 *                                     the second data element, 0 if the first
 *                                     data element is equal to the second data
 *                                     element, and 1 if the first data element
 *                                     is greater than the second data element.
 * 
 * Data members:
 *    data_size:                Size of the data stored in the linked list.
 *    *head:                    Pointer to the head of the linked list.
 *    *tail:                    Pointer to the tail of the linked list.
 *    size:                     Number of elements in the linked list.
 *    *data_to_string():        Pointer to a function that converts the data to
 *                              a string.
 *    *data_compare():          Pointer to a function that compares two data
 *                              elements.
 * 
 * Methods:
 * 
 * Usage:
 * 
 * -------------------------------------------------------------------------- */
typedef struct _gll_list {
    size_t data_size;
    _GLLNode *head;
    _GLLNode *tail;
    size_t size;
    int (*data_to_string)(char **buffer, void *data, GLLError *error);
    char (*data_compare)(void *data1, void *data2);
} GLLList;


/* ==========================================================================
 * Function Prototypes Section
 * ========================================================================== */

/* -------------------------------------------------------------------------- 
 * Function: _gll_create_node
 * -------------------------------------------------------------------------- 
 * Description: Create a new node for the linked list.
 * 
 *              The function allocates memory for the new node and for the data
 *              stored in the node. The size of the data is passed as an
 *              argument. The function copies the data to the memory allocated
 *              for the data. This way, the data stored in the node is not
 *              affected by changes to the original data. Data from the stack
 *              can also be stored in the node. User does not have to worry
 *              about the lifetime of the data stored in the node, and to free
 *              the memory allocated for the data stored in the node.
 * 
 *              The copy of the data is done using memcpy() function. The data
 *              is copied byte by byte, and the size of the data is passed as an
 *              argument. The function does not check if the data is a string or
 *              a structure. The function does not add a null terminator to the
 *              data if the data is a string. The function does not check if the
 *              data is a valid string. The function does not check if the data
 *              is a valid structure. The next pointer is set to NULL.
 * 
 *              The function returns a pointer to the new node.
 * 
 *              If the function fails to allocate memory for the new node, or
 *              the data it returns NULL, and the error parameter is set to
 *              CALLOC_ERROR. If the error parameter is NULL, the function will
 *              not set the error parameter.
 * 
 *              This function is used internally by the linked list functions.
 *              It is not intended to be used by the user.
 * 
 * Parameters:
 *  - void *data: The data to be stored in the new node.
 *  - GLLError *error: A pointer to a GLLError variable to store
 *    the error code. If NULL, the function will not set the error parameter.
 * 
 * Returns:
 *  - _GLLNode *: A pointer to the new node.
 * 
 * -------------------------------------------------------------------------- */
_GLLNode *_gll_create_node(
  const void *data,
  const size_t data_size,
  GLLError *error
);

/* --------------------------------------------------------------------------   
  * Function: gll_create
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
  *               - compare two data.
  *
  *               First function is used to convert data to string, and is used
  *               for printing the data in the linked list. Second function is
  *               used to compare two data. If the pointers to these two
  *               functions are NULL, the function returns NULL, and sets the
  *               error code to DATA_TO_STRING_NULL or DATA_COMPARE_NULL,
  *               respectively.
  * 
  *               The function returns NULL if memory allocation fails, and sets
  *               the error code to CALLOC_ERROR.
  *
  * Parameters:
  *  - data_to_string: pointer to a function that converts data to string.
  *  - data_compare: pointer to a function that compares two data.
  *  - error: pointer to GLLError to store error code.
  *
  * Returns:
  * - GLLList: pointer to the generic linked list.
  * 
  * ------------------------------------------------------------------------- */
GLLList *gll_create(
  const size_t data_size,
  int (*data_to_string)(char **buffer, void *data, GLLError *error),
  char (*data_compare)(void *data1, void *data2),
  GLLError *error
);

/* --------------------------------------------------------------------------
 * Function: gll_push_front
 * --------------------------------------------------------------------------
 * 
 * Description: Add an element to the front of the list.
 * 
 *              If the list is NULL, the function returns NULL and sets the
 *              error code to LIST_NULL.
 * 
 *              If the data is NULL, the function returns NULL and sets the
 *              error code to DATA_NULL.
 * 
 *              If the memory allocation for the new node fails, the function
 *              returns original list and sets the error code to CALLOC_ERROR.
 * 
 *              If the error is NULL, the function does not set the error.
 * 
 * Complexity: O(1)
 * 
 * Parameters:
 *  - list: The list to which we add the element.
 *  - data: The data of the new element.
 *  - error: A pointer to a variable of type GLLError, where we store the
 *           error code if an error occurs.
 * 
 * Return: The list with the new element added to the front, or original list
 *         if an error occurs.
 * 
 * -------------------------------------------------------------------------- */
GLLList *gll_push_front(
  GLLList *list,
  const void *data,
  GLLError *error
);

/* --------------------------------------------------------------------------
 * Function: gll_push_back
 * --------------------------------------------------------------------------
 * 
 * Description: Add an element to the end of the list.
 * 
 *             If the list is NULL, the function returns the list and sets the
 *             error code to LIST_NULL.
 * 
 *             If the data is NULL, the function returns the list and sets the
 *             error code to DATA_NULL.
 * 
 *              If the memory allocation for the new node fails, the function
 *              returns original list and sets the error code to CALLOC_ERROR.
 * 
 *             If the error is NULL, the function does not set the error.
 * 
 * Complexity: O(1)
 * 
 * Parameters:
 *  - list: The list to which we add the element.
 *  - data: The data of the new element.
 *  - error: A pointer to a variable of type GLLError, where we store the
 *           error code if an error occurs.
 * 
 * Return: The list with the new element added to the front, or original list
 *         if an error occurs.
 * 
 * -------------------------------------------------------------------------- */
GLLList *gll_push_back(
  GLLList *list,
  const void *data,
  GLLError *error
);

void *gll_pop_front(
  GLLList *list,
  GLLError *error
);

GLLList *gll_delete_at_front(
  GLLList *list,
  GLLError *error
);

void *gll_pop_back(
  GLLList *list,
  GLLError *error
);

GLLList *gll_delete_at_back(
  GLLList *list,
  GLLError *error
);

void gll_node_free(_GLLNode *node);

/* --------------------------------------------------------------------------
 * Function: gll_free
 * --------------------------------------------------------------------------
 * 
 * Description: Free the memory allocated for the list and its elements.
 * 
 *              If the list is NULL, the function does nothing. If the list is
 *              empty, the function frees the memory allocated for the list
 *              data structure.
 * 
 *              If the list is not empty, the function frees the memory
 *              allocated for the list data structure and its nodes.
 * 
 * Complexity: O(n)
 * 
 * Parameters:
 *  - list: The list to free.
 * 
 * Return: void
 * 
 * -------------------------------------------------------------------------- */
void gll_free(GLLList *list);

/* --------------------------------------------------------------------------
 * Function: gll_is_empty
 * --------------------------------------------------------------------------
 * 
 * Description: Check if the list is empty.
 * 
 *              If the list is NULL, the function returns false and sets the
 *              error code to LIST_NULL.
 * 
 *              If the error is NULL, the function does not set the error.
 * 
 * Parameters:
 *  - list: The list to check if it is empty.
 *  - error: A pointer to a variable of type GLLError, where we store the
 *           error code if an error occurs.
 * 
 * Return: True if the list is empty, false otherwise.
 * 
 * -------------------------------------------------------------------------- */
bool gll_is_empty(GLLList *list, GLLError *error);

/* --------------------------------------------------------------------------
 * Function: gll_size
 * --------------------------------------------------------------------------
 * 
 * Description: Get the number of elements in the list.
 * 
 *             If the list is NULL, the function returns zero and sets the
 *             error code to LIST_NULL.
 * 
 *             If the error is NULL, the function does not set the error.
 * 
 * Parameters:
 *  - list: The list for which we get the number of elements.
 *  - error: A pointer to a variable of type GLLError, where we store the
 *           error code if an error occurs.
 * 
 * Return: The number of elements in the list, or zero if an error occurs.
 * 
 * -------------------------------------------------------------------------- */
size_t gll_size(GLLList *list, GLLError *error);

/* --------------------------------------------------------------------------
 * Function: gll_contains
 * --------------------------------------------------------------------------
 * 
 * Description: Check if the list contains the specified data.
 * 
 *              If the list is NULL, the function returns false and sets the
 *              error code to LIST_NULL.
 * 
 *              If the data is NULL, the function returns false and sets the
 *              error code to DATA_NULL.
 * 
 *              If the error is NULL, the function does not set the error.
 * 
 * Complexity: O(n)
 * 
 * Parameters:
 *  - list: The list to check.
 *  - data: The data to check for.
 *  - error: A pointer to a variable of type GLLError, where we store the
 *           error code if an error occurs.
 * 
 * Return: Index of the first node that contains the given data, or SIZE_MAX if
 *         the data is not found or an error occurs.
 * 
 * -------------------------------------------------------------------------- */
size_t gll_contains(GLLList *list, void *data, GLLError *error);

size_t gll_count_occurrences(
  GLLList *list,
  void *data,
  GLLError *error
);

/* --------------------------------------------------------------------------   
 * Function: gll_get_data
 * --------------------------------------------------------------------------   
 * 
 * Description: Retrieve the data stored in the node at the specified index.
 * 
 *              Retrieved pointer to the data is a pointer to the copy of the
 *              data stored in the node. This way, the data stored in the node
 *              is not affected by changes to the data. The user does not have
 *              to worry about the lifetime of the data stored in the node, and
 *              to free the memory allocated for the data stored in the node.
 *              But the user has to free the memory allocated for the data
 *              returned by this function.
 * 
 *              If the list is NULL, the function returns NULL and sets the
 *              error to LIST_NULL.
 * 
 *              If the list is empty, the function returns NULL and sets the
 *              error to LIST_EMPTY.
 * 
 *              If the index is less than 0 or greater than or equal to the size
 *              of the list, the function returns NULL and sets the error to
 *              INDEX_OUT_OF_BOUNDS. If the index is valid, the function returns
 *              the data stored in the node at the specified index.
 * 
 *              If the error is NULL, the function does not set the error.
 * 
 * Complexity: O(n)
 * 
 * Parameters:
 *  - list: pointer to the linked list.
 *  - index: index of the element for which to get the data.
 *  - error: pointer to GLLError to store error code.
 * 
 * Returns:
 *  - void *: pointer to the data stored in the first element, or NULL if the
 *            list is NULL, empty, or the index is out of bounds.
 * 
 * -------------------------------------------------------------------------- */
void *gll_get_data(GLLList *list, size_t index, GLLError *error);

/* --------------------------------------------------------------------------
 * Function: gll_get_node
 * --------------------------------------------------------------------------
 * 
 * Description: Returns the node at the specified index in the list.
 * 
 *              If the list is NULL, the function returns NULL and sets the
 *              error to LIST_NULL.
 * 
 *              If the list is empty, the function returns NULL and sets the
 *              error to LIST_EMPTY.
 * 
 *              If the index is less than 0 or greater than or equal to the size
 *              of the list, the function returns NULL and sets the error to
 *              INDEX_OUT_OF_BOUNDS. If the index is valid, the function returns
 *              the data stored in the node at the specified index.
 * 
 *              If the error is NULL, the function does not set the error.
 * 
 * Complexity: O(n)
 * 
 * Parameters:
 *  - list: The list from which to get the node.
 *  - index: The index of the node to get.
 *  - error: A pointer to a variable of type GLLError to store the error
 *           code.
 * 
 * Returns:
 *  - The node at the specified index in the list, or NULL if an error occurs.
 * 
 * -------------------------------------------------------------------------- */
_GLLNode *gll_get_node(
  GLLList *list,
  size_t index,
  GLLError *error
);

/* --------------------------------------------------------------------------
 * Function: gll_to_string
 * --------------------------------------------------------------------------
 * 
 * Description: Generate a string representation of the list.
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
 *              If the buffer is NULL, the function returns zero and sets the
 *              error code to DESTINATION_BUFFER_NULL.
 * 
 *              If the error is NULL, the function does not set the error.
 * 
 * Parameters:
 *  - buffer: A pointer to a pointer to a char, where we store the string
 *            representation of the list.
 *  - list: The list for which we generate the string representation.
 *  - error: A pointer to a variable of type GLLError, where we store the
 *           error code if an error occurs.
 * 
 * Return: The size of the string representation of the list, or zero if an
 *         error occurs.
 * 
 * -------------------------------------------------------------------------- */
int gll_to_string(
  char **buffer,
  GLLList *list,
  GLLError *error
);

/* ==========================================================================
 * End of Header guard
 * ========================================================================== */

#endif  /* GENERIC_LINKED_LIST_H */

/* End of file generic_linked_list.h */