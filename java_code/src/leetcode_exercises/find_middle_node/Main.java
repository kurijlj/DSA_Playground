// =============================================================================
// Main.java - Demonstrate the findMiddleNode() method.
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
// 2023-12-09 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * Mian.java: created.
//
// =============================================================================


// =============================================================================
// Packages import section
// =============================================================================
package leetcode_exercises.find_middle_node;


// =============================================================================
// Main class
// =============================================================================
public class Main {
    // -------------------------------------------------------------------------
    // Main method
    // -------------------------------------------------------------------------
    public static void main(String[] args) {
        // Create empty linked list
        System.out.println("Create empty linked list:");
        LinkedList list = new LinkedList();
        list.print();

        // Test if the findMiddleNode() method works correctly on an empty list
        System.out.println("Test if the findMiddleNode() method works correctly on an empty list:");
        System.out.println(list.findMiddleNode());

        // Test if the findMiddleNode() method works correctly on a list with one node
        System.out.println("Test if the findMiddleNode() method works correctly on a list with one node:");
        list.append(0);
        list.print();
        System.out.println("Middle: " + list.findMiddleNode());

        // Test if the findMiddleNode() method works correctly on a list with even number of nodes
        System.out.println("Test if the findMiddleNode() method works correctly on a list with even number of nodes:");
        list.append(1);
        list.append(2);
        list.append(3);
        list.print();
        System.out.println("Middle: " + list.findMiddleNode());

        // Test if the findMiddleNode() method works correctly on a list with odd number of nodes
        System.out.println("Test if the findMiddleNode() method works correctly on a list with odd number of nodes:");
        list.append(4);
        list.print();
        System.out.println("Middle: " + list.findMiddleNode());
    }
}

// End of Main.java
