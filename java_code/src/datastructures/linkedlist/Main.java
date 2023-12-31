// =============================================================================
// Main.java - Demonstrate the implementation of a common linked list.
//
//  Copyright (C) 2023 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// =============================================================================


// =============================================================================
//
// 2023-11-13 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * Mian.java: created.
//
// =============================================================================


// =============================================================================
// Packages import section
// =============================================================================
package datastructures.linkedlist;


// =============================================================================
// Main class
// =============================================================================
public class Main {
    // -------------------------------------------------------------------------
    // Main method
    // -------------------------------------------------------------------------
public static void main(String[] args) {
        // Test the constructor
        System.out.println("Test the constructor:");
        LinkedList list = new LinkedList();
        list.print();

        // Test the append() method
        System.out.println("Test the append() method:");
        list.append(0);
        list.append(1);
        list.append(2);
        list.append(3);
        list.append(4);
        list.print();

        // Test the prepend() method
        System.out.println("Test the prepend() method:");
        list.prepend(-1);
        list.prepend(-2);
        list.print();

        // Test the insert() method
        System.out.println("Test the insert() method:");
        list.insert(0, -3);
        list.insert(1, -4);
        list.insert(2, -5);
        list.print();

        // Test the popBack() method
        System.out.println("Test the popBack() method:");
        System.out.println(list.popBack().getData());
        list.print();

        // Test the popFront() method
        System.out.println("Test the popFront() method:");
        System.out.println(list.popFront().getData());
        list.print();

        // Test the remove() method
        System.out.println("Test the remove() method:");
        System.out.println(list.remove(0).getData());
        list.print();

        // Test the get() method
        System.out.println("Test the get() method:");
        System.out.println(list.get(0).getData());
        System.out.println(list.get(1).getData());

        // Test the set() method
        System.out.println("Test the set() method:");
        System.out.println(list.set(0, 10).getData());
        System.out.println(list.set(1, 11).getData());
        list.print();

        // Test the reverse() method
        System.out.println("Test the reverse() method:");
        list.reverse();
        list.print();
    }
}

// End of Main.java
