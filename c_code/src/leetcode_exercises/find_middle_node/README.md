# Find the Middle Node

## Description

The `find_middle_node()` function aims to determine the index of the middle node within a linked list. It employs the slow and fast pointer technique, ensuring optimal performance.

## Features

1. **Handling Empty Lists**: If the linked list is empty, the method returns -1, providing a clear indication of an invalid scenario.

2. **Even Number of Elements**: For linked lists with an even number of elements, the method returns the index of the second middle node. This consideration enhances the applicability of the method across various scenarios.

## Implementation

The algorithmic approach involves initializing two pointers, a slow and a fast one. The slow pointer advances one step at a time, while the fast pointer moves two steps at a time. This allows for efficient traversal, culminating in the identification of the middle node.

## Usage

```c
#include "linkedlist.h"  // Include your linked list header file

// ...

linkedlist_t *my_list = create_linkedlist();
// Populate the linked list

int middle_index = find_middle_node(my_list);
// Handle the result accordingly
```