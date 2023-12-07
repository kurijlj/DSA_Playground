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
#include <cstdlib>
#include <iostream>

/* Project headers */
#include "linkedlist.hpp"


/* ==========================================================================
 * Main function
 * ========================================================================== */
int main(int argc, char *argv[])
{
    /* Create an empty linked list */
    std::cout << "Creating an empty linked list..." << std::endl;
    LinkedList *list = new LinkedList();
    std::cout << "List: " << list->string() << std::endl;
    std::cout << "Test if find_middle_node() works on an empty list..." << std::endl;
    std::cout << "Middle node: " << list->find_middle_node() << std::endl << std::endl;

    /* Add a node to the list */
    std::cout << "Adding a node to the list..." << std::endl;
    list->append(0);
    std::cout << "List: " << list->string() << std::endl;
    std::cout << "Test if find_middle_node() works on a list with one node..."
        << std::endl;
    std::cout << "Middle node: " << list->find_middle_node() << std::endl << std::endl;

    /* Expand list to have even number of nodes */
    std::cout << "Expanding list to have even number of nodes..." << std::endl;
    list->append(1);
    list->append(2);
    list->append(3);
    std::cout << "List: " << list->string() << std::endl;
    std::cout << "Test if find_middle_node() works on a list with even number of "
        "nodes..." << std::endl;
    std::cout << "Middle node: " << list->find_middle_node() << std::endl << std::endl;

    /* Expand list to have odd number of nodes */
    std::cout << "Expanding list to have odd number of nodes..." << std::endl;
    list->append(4);
    std::cout << "List: " << list->string() << std::endl;
    std::cout << "Test if find_middle_node() works on a list with odd number of "
        "nodes..." << std::endl;
    std::cout << "Middle node: " << list->find_middle_node() << std::endl << std::endl;

    /* Delete list */
    std::cout << "Deleting list..." << std::endl;
    delete list;

    return EXIT_SUCCESS;
}