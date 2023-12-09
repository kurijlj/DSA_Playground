/* ==========================================================================
 * linkedlist.h - A header only implementation of a linked list.
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
 * * linkedlist.h: created.
 *
 * ========================================================================== */


#ifndef LINKEDLIST_H
#define LINKEDLIST_H


/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Standard Library headers */
#include <stdio.h>
#include <stdlib.h>


/* ==========================================================================
 * Abstract Data Types Definition Section
 * ========================================================================== */
typedef struct node {
    int data;
    struct node *next;
} node_t;

typedef struct linkedlist {
    node_t *head;
    node_t *tail;
    int size;
} linkedlist_t;


/* ==========================================================================
 * Function Prototypes Section
 * ========================================================================== */
node_t *create_node(int data);
void destroy_node(node_t *node);
int string_node(node_t *node, char *str);
void print_node(node_t *node);
linkedlist_t *create_linkedlist(void);
void destroy_linkedlist(linkedlist_t *list);
void print_linkedlist(linkedlist_t *list);
node_t *get_node(linkedlist_t *list, int index);
void push_back(linkedlist_t *list, int data);
node_t *pop_back(linkedlist_t *list);
void push_front(linkedlist_t *list, int data);
node_t *pop_front(linkedlist_t *list);
void set_node(linkedlist_t *list, int index, int data);
void insert_node(linkedlist_t *list, int index, int data);
node_t *remove_node(linkedlist_t *list, int index);
void reverse_linkedlist(linkedlist_t *list);


/* ==========================================================================
 * Function Definitions Section
 * ========================================================================== */
node_t *create_node(int data) {
    node_t *node = (node_t *) malloc (sizeof(node_t));
    node->data = data;
    node->next = NULL;
    return node;
}

void destroy_node(node_t *node) {
    free(node);
}

int string_node(node_t *node, char *str) {
    return snprintf(str, 100, "node(%d)", node->data);
}

void print_node(node_t *node) {
    printf("node(%d)\n", node->data);
}

linkedlist_t *create_linkedlist(void) {
    linkedlist_t *list = (linkedlist_t *) malloc (sizeof(linkedlist_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void destroy_linkedlist(linkedlist_t *list) {
    node_t *node = list->head;
    while (node != NULL) {
        node_t *next = node->next;
        destroy_node(node);
        node = next;
    }
    free(list);
}

void print_linkedlist(linkedlist_t *list) {
    node_t *node = list->head;
    printf("linkedlist(");
    while (node != NULL) {
        printf("%d", node->data);
        if (node->next != NULL) {
            printf(", ");
        }
        node = node->next;
    }
    printf(")\n");
}

node_t *get_node(linkedlist_t *list, int index) {
    if (0 > index || index >= list->size) {
        return NULL;
    }

    node_t *node = list->head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }

    return node;
}

void push_back(linkedlist_t *list, int data) {
    node_t *node = create_node(data);
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

node_t *pop_back(linkedlist_t *list) {
    if (list->head == NULL) {
        return NULL;
    }

    node_t *node = list->tail;
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        node_t *prev = get_node(list, list->size - 2);
        prev->next = NULL;
        list->tail = prev;
    }
    list->size--;
    return node;
}

void push_front(linkedlist_t *list, int data) {
    node_t *node = create_node(data);
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;
        list->head = node;
    }
    list->size++;
}

node_t *pop_front(linkedlist_t *list) {
    if (list->head == NULL) {
        return NULL;
    }

    node_t *node = list->head;
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = node->next;
    }
    list->size--;
    return node;
}

void set_node(linkedlist_t *list, int index, int data) {
    node_t *node = get_node(list, index);
    if (node != NULL) {
        node->data = data;
    }
}

void insert_node(linkedlist_t *list, int index, int data) {
    if (0 > index || index > list->size) {
        return;
    }

    if (index == 0) {
        push_front(list, data);
    } else if (index == list->size) {
        push_back(list, data);
    } else {
        node_t *prev = get_node(list, index - 1);
        node_t *node = create_node(data);
        node->next = prev->next;
        prev->next = node;
        list->size++;
    }
}

node_t *remove_node(linkedlist_t *list, int index) {
    if (0 > index || index >= list->size) {
        return NULL;
    }

    if (index == 0) {
        return pop_front(list);
    } else if (index == list->size - 1) {
        return pop_back(list);
    } else {
        node_t *prev = get_node(list, index - 1);
        node_t *node = prev->next;
        prev->next = node->next;
        list->size--;
        return node;
    }
}

void reverse_linkedlist(linkedlist_t *list) {
    node_t *prev = NULL;
    node_t *curr = list->head;
    node_t *next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    list->tail = list->head;
    list->head = prev;
}

/* --------------------------------------------------------------------------
 *
 * Function: find_middle_node
 *
 *
 * --------------------------------------------------------------------------
 * 
 * Description:
 *      Find the middle node of a linked list. It returns the index of the
 *      middle node if the list is not empty, otherwise it returns -1.
 * 
 *      This method uses the "slow and fast" pointer technique to find the
 *      middle node. The slow pointer moves one node at a time, while the fast
 *      pointer moves two nodes at a time. When the fast pointer reaches the end
 *      of the list, the slow pointer will be pointing to the middle node.
 * 
 *      Time complexity: O(n)
 *      Space complexity: O(1)
 * 
 * Usage:
 *      int idx = find_middle_node(list);
 * 
 * Returns:
 *      The index of the middle node if the list is not empty, otherwise it
 *      returns -1.
 * -------------------------------------------------------------------------- */
int find_middle_node(linkedlist_t *list) {
    int idx = -1;
    if(list->head == NULL) {
        return idx;
    }

    node_t *slow = list->head;
    node_t *fast = list->head;
    idx = 0;
    while (fast != NULL && fast->next != NULL) {
        idx++;
        slow = slow->next;
        fast = fast->next->next;
    }

    return idx;
}

#endif  /* LINKEDLIST_H */