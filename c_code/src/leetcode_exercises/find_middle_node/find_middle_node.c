/* ==========================================================================
 * find_middle_node.c - Demonstrate find_middle_node() function.
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
 * 2023-12-09 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * find_middle_node.c: created.
 *
 * ========================================================================== */


/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Standard Library headers */
#include <stdio.h>
#include <stdlib.h>

/* Project headers */
#include "linkedlist.h"


/* ==========================================================================
 * Main function
 * ========================================================================== */
int main(int argc, char *argv[])
{
    /* Create an empty linked list */
    printf("Creating an empty linked list...\n");
    linkedlist_t *list = create_linkedlist();
    printf("List: ");
    print_linkedlist(list);
    printf("Test if find_middle_node() works on an empty list...\n");
    printf("Middle node: %d\n", find_middle_node(list));

    /* Add a single node to the list */
    printf("Adding a single node to the list...\n");
    push_back(list, 0);
    printf("List: ");
    print_linkedlist(list);
    printf(
        "Test if find_middle_node() works on a"
        " list with a single node...\n"
        );
    printf("Middle node: %d\n", find_middle_node(list));

    /* Expand the list to have even number of nodes */
    printf("Expanding the list to have even number of nodes...\n");
    push_back(list, 1);
    push_back(list, 2);
    push_back(list, 3);
    printf("List: ");
    print_linkedlist(list);
    printf(
        "Test if find_middle_node() works on a"
        " list with even number of nodes...\n"
        );
    printf("Middle node: %d\n", find_middle_node(list));

    /* Expand the list to have odd number of nodes */
    printf("Expanding the list to have odd number of nodes...\n");
    push_back(list, 4);
    printf("List: ");
    print_linkedlist(list);
    printf(
        "Test if find_middle_node() works on a"
        " list with odd number of nodes...\n"
        );
    printf("Middle node: %d\n", find_middle_node(list));

    /* Destroy the list */
    printf("Destroying the list...\n");
    destroy_linkedlist(list);

    return EXIT_SUCCESS;
}