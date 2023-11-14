import LinkedList

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
