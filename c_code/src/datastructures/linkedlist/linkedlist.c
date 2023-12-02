/* ==========================================================================
 * linkedlist.c - Main program file demonstrating linked list functionality.
 *
 *  Copyright (C) 2023 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * ========================================================================== */


/* ==========================================================================
 *
 * 2023-11-28 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * linkedlist.c: created.
 *
 * ========================================================================== */


/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Standard Library headers */
#include <stdio.h>

/* Project headers */
#include "linkedlist.h"


/* ==========================================================================
 * Main function
 * ========================================================================== */
int main(int argc, char *argv[])
{
    /* Create a new linked list */
    printf("Creating a new linked list...\n");
    linkedlist_t *list = create_linkedlist();
    print_linkedlist(list);

    /* Insert some nodes at the tail of the list */
    printf("Inserting some nodes at the tail of the list...\n");
    push_back(list, 1);
    push_back(list, 2);
    push_back(list, 3);
    push_back(list, 4);
    print_linkedlist(list);

    /* Insert some nodes at the head of the list */
    printf("Inserting some nodes at the head of the list...\n");
    push_front(list, 0);
    push_front(list, -1);
    push_front(list, -2);
    print_linkedlist(list);

    /* Remove some nodes from the tail of the list */
    printf("Removing some nodes from the tail of the list...\n");
    print_node(pop_back(list));
    print_node(pop_back(list));
    print_linkedlist(list);

    /* Remove some nodes from the head of the list */
    printf("Removing some nodes from the head of the list...\n");
    print_node(pop_front(list));
    print_node(pop_front(list));
    print_linkedlist(list);

    /* Insert some nodes at the middle of the list */
    printf("Inserting some nodes at the middle of the list...\n");
    insert_node(list, 2, 2);
    insert_node(list, 3, 3);
    print_linkedlist(list);

    /* Remove some nodes from the middle of the list */
    printf("Removing some nodes from the middle of the list...\n");
    print_node(remove_node(list, 2));
    print_node(remove_node(list, 2));
    print_linkedlist(list);

    /* Reverse the list */
    printf("Reversing the list...\n");
    reverse_linkedlist(list);
    print_linkedlist(list);

    /* Destroy the list */
    printf("Destroying the list...\n");
    destroy_linkedlist(list);
    list = NULL;

    /* Create list with some nodes and test pop_back until list is empty */
    printf("Creating a new linked list...\n");
    list = create_linkedlist();
    push_back(list, 1);
    push_back(list, 2);
    push_back(list, 3);
    print_linkedlist(list);
    printf("Removing some nodes from the tail of the list...\n");
    print_node(pop_back(list));
    print_node(pop_back(list));
    print_node(pop_back(list));
    pop_back(list);
    print_linkedlist(list);

    /* Destroy the list */
    printf("Destroying the list...\n");
    destroy_linkedlist(list);
    list = NULL;

    /* Create list with some nodes and test pop_front until list is empty */
    printf("Creating a new linked list...\n");
    list = create_linkedlist();
    push_front(list, 1);
    push_front(list, 2);
    push_front(list, 3);
    print_linkedlist(list);
    printf("Removing some nodes from the head of the list...\n");
    print_node(pop_front(list));
    print_node(pop_front(list));
    print_node(pop_front(list));
    pop_front(list);
    print_linkedlist(list);

    /* Destroy the list */
    printf("Destroying the list...\n");
    destroy_linkedlist(list);
    list = NULL;

    return 0;
}