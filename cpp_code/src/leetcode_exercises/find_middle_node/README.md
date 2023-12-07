# Find the Middle Node

## Description

The `find_middle_node()` method aims to determine the index of the middle node within a linked list. It employs the slow and fast pointer technique, ensuring optimal performance.

## Features

1. **Handling Empty Lists**: If the linked list is empty, the method returns -1, providing a clear indication of an invalid scenario.

2. **Even Number of Elements**: For linked lists with an even number of elements, the method returns the index of the second middle node. This consideration enhances the applicability of the method across various scenarios.

## Implementation

The algorithmic approach involves initializing two pointers, a slow and a fast one. The slow pointer advances one step at a time, while the fast pointer moves two steps at a time. This allows for efficient traversal, culminating in the identification of the middle node.

## Usage

```cpp
#include "linkedlist.h"  // Include your linked list header file

// ...

LinkedList myList;
// Populate the linked list

int middleIndex = myList.find_middle_node();
// Handle the result accordingly
```