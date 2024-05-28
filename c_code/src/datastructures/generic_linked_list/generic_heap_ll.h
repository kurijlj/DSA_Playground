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
 * * generic_heap_ll.h: created.
 *
 * ========================================================================== */

/* ==========================================================================
 * Header guard
 * ========================================================================== */

#ifndef GENERIC_HEAP_LL_H
#define GENERIC_HEAP_LL_H


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
 * Data Structures Section
 * ========================================================================== */

/* -------------------------------------------------------------------------- 
 * Structure: heap_ll_node_t
 * -------------------------------------------------------------------------- 
 * Description: 
 * 
 * Data members:
 *                   void *data: 
 *    struct heap_ll_node *next: 
 * 
 * Methods:
 * 
 * Usage:
 * 
 * -------------------------------------------------------------------------- */
typedef struct heap_ll_node {
    void *data;
    struct heap_ll_node *next;
} heap_ll_node_t;

/* -------------------------------------------------------------------------- 
 * Structure: heap_ll_t
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
 * 
 * Methods:
 * 
 * Usage:
 * 
 * -------------------------------------------------------------------------- */
typedef struct heap_ll {
    heap_ll_node_t *head;
    heap_ll_node_t *tail;
    size_t size;
    int (*data_to_string)(char **buffer, void *data, char const **error);
    bool (*data_equals)(void *data1, void *data2);
    bool (*data_less)(void *data1, void *data2);
    bool (*data_greater)(void *data1, void *data2);
    bool (*data_less_or_equal)(void *data1, void *data2);
    bool (*data_greater_or_equal)(void *data1, void *data2);
} heap_ll_t;


/* ==========================================================================
 * End of Header guard
 * ========================================================================== */

#endif  /* GENERIC_HEAP_LL_H */