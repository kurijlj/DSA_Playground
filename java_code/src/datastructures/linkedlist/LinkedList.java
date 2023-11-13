package datastructures.linkedlist;

public class LinkedList {
    private Node head = null;
    private Node tail = null;
    private int size = 0;

    class Node {
        private int data;
        private Node next;

        public Node(int data) {
            this.data = data;
            this.next = null;
        }

        public int getData() {
            return this.data;
        }

        public void setData(int data) {
            this.data = data;
        }

        public Node getNext() {
            return this.next;
        }

        public void setNext(Node next) {
            this.next = next;
        }
    }

    public LinkedList() {
        this.head = null;
        this.tail = null;
        this.size = 0;
    }

    public void append(int data) {
        Node newNode = new Node(data);

        if (this.head == null) {
            this.head = newNode;
            this.tail = newNode;
        } else {
            this.tail.setNext(newNode);
            this.tail = newNode;
        }

        this.size++;
    }

    public void print() {
        Node current = this.head;

        System.out.print("LinkedList(");
        while (current != null) {
            System.out.print(current.getData() + " ");
            current = current.getNext();
        }
        System.out.println(")");

        System.out.println();
    }

    public Node popBack() {
        if (this.head == null) {
            return null;
        }

        Node current = this.head;
        Node previous = null;

        while (current.getNext() != null) {
            previous = current;
            current = current.getNext();
        }

        if (previous == null) {
            this.head = null;
            this.tail = null;
        } else {
            previous.setNext(null);
            this.tail = previous;
        }

        this.size--;

        return current;
    }

    public void prepend(int data) {
        Node newNode = new Node(data);

        if (this.head == null) {
            this.head = newNode;
            this.tail = newNode;
        } else {
            newNode.setNext(this.head);
            this.head = newNode;
        }

        this.size++;
    }

    public Node popFront() {
        if (this.head == null) {
            return null;
        }

        Node current = this.head;
        this.head = this.head.getNext();
        this.size--;

        if(this.size == 0) {
            this.tail = null;
        }

        return current;
    }

    public Node get(int index) {
        if (index < 0 || index >= this.size) {
            return null;
        }

        Node current = this.head;
        int i = 0;

        while (i < index) {
            current = current.getNext();
            i++;
        }

        return current;
    }

    public Node set(int index, int data) {
        Node current = this.get(index);

        if (current != null) {
            current.setData(data);
        }

        return current;
    }

    public Node insert(int index, int data) {
        if (index < 0 || index > this.size) {
            return null;
        }

        if (index == 0) {
            this.prepend(data);
            return this.head;
        }

        if (index == this.size) {
            this.append(data);
            return this.tail;
        }

        Node previous = this.get(index - 1);
        Node newNode = new Node(data);

        newNode.setNext(previous.getNext());
        previous.setNext(newNode);

        this.size++;

        return newNode;
    }

    public Node remove(int index) {
        if (index < 0 || index >= this.size) {
            return null;
        }

        if (index == 0) {
            return this.popFront();
        }

        if (index == this.size - 1) {
            return this.popBack();
        }

        Node previous = this.get(index - 1);
        Node current = previous.getNext();

        previous.setNext(current.getNext());
        current.setNext(null);

        this.size--;

        return current;
    }

    public void reverse() {
        Node previous = null;
        Node current = this.head;
        Node next = null;

        while (current != null) {
            next = current.getNext();
            current.setNext(previous);
            previous = current;
            current = next;
        }

        this.tail = this.head;
        this.head = previous;
    }
}
