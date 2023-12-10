# ==============================================================================
# test.py - Demonstrate the usage of the find_middle_node() method.
#
#  Copyright (C) 2023 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# ==============================================================================


# ==============================================================================
#
# 2023-12-10 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
#
# * test.py: created.
#
# ==============================================================================


# ==============================================================================
# Modules Import Section
# ==============================================================================
import LinkedList


# ==============================================================================
# Main Section
# ==============================================================================
if __name__ == "__main__":
    # Create an empty linked list.
    print("Creating an empty linked list...")
    ll = LinkedList.LinkedList()
    print(ll)

    # Check if the find_middle_node() method works on the empty linked list.
    print("Finding the middle node of the empty linked list...")
    print("Middle: ", ll.find_middle_node())

    # Extend the linked list with a single node.
    print("Extending the linked list with a single node...")
    ll.append(0)
    print(ll)
    # Check if the find_middle_node() method works on the linked list with a
    # single node.
    print("Finding the middle node of the linked list with a single node...")
    print("Middle: ", ll.find_middle_node())

    # Extend the linked list to contain even number of nodes.
    print("Extending the linked list to contain even number of nodes...")
    ll.append(1)
    ll.append(2)
    ll.append(3)
    print(ll)
    # Check if the find_middle_node() method works on the linked list with even
    # number of nodes.
    print(
        "Finding the middle node of the linked list with " +
        "even number of nodes..."
        )
    print("Middle: ", ll.find_middle_node())

    # Extend the linked list to contain odd number of nodes.
    print("Extending the linked list to contain odd number of nodes...")
    ll.append(4)
    print(ll)
    # Check if the find_middle_node() method works on the linked list with odd
    # number of nodes.
    print(
        "Finding the middle node of the linked list with " +
        "odd number of nodes..."
        )
    print("Middle: ", ll.find_middle_node())

    # End of Main Section

# End of test.py
