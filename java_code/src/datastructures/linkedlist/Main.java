package datastructures.linkedlist;

public class Main {
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
