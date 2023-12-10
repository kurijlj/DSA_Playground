# ==============================================================================
# test.py - Demonstrate the implementation of the LinkedList class.
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
# 2023-11-14 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
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
    # Create a new linked list
    print("Creating a new linked list...\n")
    ll = LinkedList.LinkedList()

    # Append some data to the linked list
    print("Appending some data to the linked list...\n")
    ll.append(1)
    ll.append(2)
    ll.append(3)
    ll.append(4)
    ll.append(5)

    # Print the linked list
    print("Printing the linked list...")
    print(ll)
    print("\n")

    # Print the size of the linked list
    print("Printing the size of the linked list...")
    print(len(ll))
    print("\n")

    # Pop the last node from the linked list
    print("Popping the last node from the linked list...")
    print(ll.pop_back())
    print(ll)
    print("\n")

    # Pop the first node from the linked list
    print("Popping the first node from the linked list...")
    print(ll.pop_front())
    print(ll)
    print("\n")

    # Prepend some data at the beginning of the linked list
    print("Inserting some data at the beginning of the linked list...\n")
    ll.prepend(0)
    ll.prepend(-1)
    ll.prepend(-2)
    print(ll)
    print("\n")

    # Get some data from the linked list
    print("Getting some data from the linked list...\n")
    print(ll.get(0))
    print(ll.get(1))
    print(ll.get(2))
    print("\n")

    # Set some data in the linked list
    print("Setting some data in the linked list...\n")
    ll.set(0, 0)
    ll.set(len(ll) - 1, 4)
    print(ll)
    print("\n")

    # Insert some data at the middle of the linked list
    print("Inserting some data at the middle of the linked list...\n")
    ll.insert(3, 2)
    ll.insert(4, 3)
    print(ll)
    print("\n")

    # Remove some data from the linked list
    print("Removing some data from the linked list...\n")
    ll.remove(3)
    ll.remove(4)
    ll.remove(0)
    ll.remove(len(ll) - 1)
    print(ll)
    print("\n")

    # Reverse the linked list
    print("Reversing the linked list...\n")
    ll.reverse()
    print(ll)
    print("\n")

    # End of Main Section

# End of test.py
