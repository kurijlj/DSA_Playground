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
    /* Create a new linked list */
    std::cout << "Creating a new linked list..." << std::endl;
    LinkedList *list = new LinkedList();
    list->print();

    /* Insert some nodes at the tail of the list */
    std::cout << "Inserting some nodes at the tail of the list..." << std::endl;
    list->append(1);
    list->append(2);
    list->append(3);
    list->append(4);
    list->append(5);
    list->print();

    /* Insert some nodes at the head of the list */
    std::cout << "Inserting some nodes at the head of the list..." << std::endl;
    list->prepend(0);
    list->prepend(-1);
    list->prepend(-2);
    list->print();

    /* Remove some nodes from the tail of the list */
    std::cout << "Removing some nodes from the tail of the list..." << std::endl;
    list->pop_back();
    list->pop_back();
    list->print();

    /* Remove some nodes from the head of the list */
    std::cout << "Removing some nodes from the head of the list..." << std::endl;
    list->pop_front();
    list->pop_front();
    list->print();

    /* Insert some nodes at the middle of the list */
    std::cout << "Inserting some nodes at the middle of the list..." << std::endl;
    list->insert(0, -1);
    list->insert(2, 10);
    list->insert(list->size() - 1, 4);
    list->print();


    /* Remove some nodes from the middle of the list */
    std::cout << "Removing some nodes from the middle of the list..." << std::endl;
    list->remove(0);
    list->remove(2);
    list->remove(list->size() - 1);
    list->print();

    /* Set some nodes in the list */
    std::cout << "Setting some nodes in the list..." << std::endl;
    list->set(0, -10);
    list->set(2, 100);
    list->set(list->size() - 1, 40);
    list->print();

    /* Reverse the list */
    std::cout << "Reversing the list..." << std::endl;
    list->reverse();
    list->print();

    /* Destroy the list */
    std::cout << "Destroying the list..." << std::endl;
    list->~LinkedList();
    list = nullptr;

    /* Create list with some nodes and test pop_back until list is empty */
    std::cout << "Creating a new linked list..." << std::endl;
    list = new LinkedList();
    list->append(1);
    list->append(2);
    list->append(3);
    list->append(4);
    list->print();
    std::cout << "Removing nodes from the tail of the list..." << std::endl;
    std::cout << list->pop_back()->string() << std::endl;
    std::cout << list->pop_back()->string() << std::endl;
    std::cout << list->pop_back()->string() << std::endl;
    std::cout << list->pop_back()->string() << std::endl;
    if (list->pop_back() == nullptr)
        std::cout << "List is empty!" << std::endl;
    else
        std::cout << "List is not empty!" << std::endl;

    /* Destroy the list */
    std::cout << "Destroying the list..." << std::endl;
    list->~LinkedList();

    /* Create list with some nodes and test pop_front until list is empty */
    std::cout << "Creating a new linked list..." << std::endl;
    list = new LinkedList();
    list->prepend(1);
    list->prepend(2);
    list->prepend(3);
    list->prepend(4);
    list->print();
    std::cout << "Removing nodes from the head of the list..." << std::endl;
    list->pop_front();
    list->pop_front();
    list->pop_front();
    list->pop_front();
    if (list->pop_front() == nullptr)
        std::cout << "List is empty!" << std::endl;
    else
        std::cout << "List is not empty!" << std::endl;

    /* Destroy the list */
    std::cout << "Destroying the list..." << std::endl;
    list->~LinkedList();

    /* Test edge cases (list->size() = 1) for the insert() and remove methods()
     */
    list = new LinkedList();
    list->append(1);
    list->print();
    std::cout << "Inserting a node at the head of the list..." << std::endl;
    list->insert(0, 0);
    list->print();
    std::cout << "Inserting a node at the tail of the list..." << std::endl;
    list->insert(1, 1);
    list->print();
    std::cout << "Removing a node from the head of the list..." << std::endl;
    list->remove(0);
    list->print();
    std::cout << "Removing a node from the tail of the list..." << std::endl;
    list->remove(list->size() - 1);
    list->print();

    /* Destroy the list */
    std::cout << "Destroying the list..." << std::endl;
    list->~LinkedList();
}