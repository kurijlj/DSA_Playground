class LinkedList:
    class Node:
        def __init__(self, data) -> None:
            self.__data = data
            self.__next = None

        def __str__(self) -> str:
            return 'Node(' + str(self.__data) + ')'

        @property
        def data(self):
            return self.__data
        
        @data.setter
        def data(self, data):
            self.__data = data

        @property
        def next(self):
            return self.__next
        
        @next.setter
        def next(self, next):
            self.__next = next

    def __init__(self) -> None:
        self.__head = None
        self.__tail = None
        self.__size = 0
    
    def __str__(self) -> str:
        current = self.__head
        result = "LinkedList("
        while current != None:
            result += str(current.data) + ", "
            current = current.next
        result += ")"

        return result
    
    def __len__(self) -> int:
        return self.__size
    
    def append(self, data):
        new_node = LinkedList.Node(data)

        if self.__head == None:
            self.__head = new_node
            self.__tail = new_node
        else:
            self.__tail.next = new_node
            self.__tail = new_node
        
        self.__size += 1

    def pop_back(self) -> Node:
        if self.__head == None:
            return None

        current = self.__head
        previous = None

        while current.next != None:
            previous = current
            current = current.next
        
        if previous == None:
            self.__head = None
            self.__tail = None
        else:
            previous.next = None
            self.__tail = previous
        
        self.__size -= 1

        return current

    def prepend(self, data):
        new_node = LinkedList.Node(data)

        if self.__head == None:
            self.__head = new_node
            self.__tail = new_node
        else:
            new_node.next = self.__head
            self.__head = new_node
        
        self.__size += 1

    def pop_front(self) -> Node:
        if self.__head == None:
            return None
        
        current = self.__head
        self.__head = self.__head.next

        if self.__head == None:
            self.__tail = None
        
        self.__size -= 1

        return current

    def get(self, index) -> Node:
        if index < 0 or index >= self.__size:
            return None
        
        current = self.__head
        i = 0

        while i < index:
            current = current.next
            i += 1
        
        return current

    def set(self, index, data):
        current = self.get(index)

        if current != None:
            current.data = data

    def insert(self, index, data):
        if index < 0 or index > self.__size:
            return None
        
        if index == 0:
            self.prepend(data)
        elif index == self.__size - 1:
            self.append(data)
        else:
            new_node = LinkedList.Node(data)
            current = self.get(index - 1)
            new_node.next = current.next
            current.next = new_node
            self.__size += 1
    
    def remove(self, index) -> Node:
        if index < 0 or index >= self.__size:
            return None
        
        if index == 0:
            return self.pop_front()
        elif index == self.__size - 1:
            return self.pop_back()
        else:
            previous = self.get(index - 1)
            current = previous.next
            previous.next = current.next
            self.__size -= 1
            return current
    
    def reverse(self):
        previous = None
        current = self.__head
        self.__tail = current

        while current != None:
            next = current.next
            current.next = previous
            previous = current
            current = next
        
        self.__head = previous