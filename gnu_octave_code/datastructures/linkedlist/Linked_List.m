classdef Linked_List < handle
    %% ------------------------------------------------------------------------
    %%
    %% Class: Linked_List
    %%
    %% ------------------------------------------------------------------------
    %
    %% Description: This class implements a common linked list.
    %
    %% Properties:
    %       head_ - The head of the linked list.
    %       tail_ - The tail of the linked list.
    %       len_  - The length of the linked list.
    %
    %% Methods:
    %       disp()        - Display the linked list.
    %       str_repr()    - Return the string representation of the linked list.
    %       length()      - Return the length of the linked list.
    %       is_empty()    - Return whether the linked list is empty.
    %       push_back()   - Push a node to the back of the linked list.
    %       pop_back()    - Pop a node from the back of the linked list.
    %       push_front()  - Push a node to the front of the linked list.
    %       pop_front()   - Pop a node from the front of the linked list.
    %       get()         - Get the node at the given index.
    %       set()         - Set the node at the given index.
    %       insert()      - Insert a node at the given index.
    %       delete()      - Delete the node at the given index.
    %       reverse()     - Reverse the linked list.
    %
    %% Example:
    %       ll = Linked_List();
    %       ll.push_back(1);
    %       ll.push_back(2);
    %       ll.push_back(3);
    %       ll.push_front(0);
    %       ll.insert(2, 10);
    %       ll.delete(3);
    %       ll.reverse();
    %       ll.disp();
    %       ll.str_repr();
    %
    %% (C) Copyright 2023 Ljubomir Kurij
    %
    %% -------------------------------------------------------------------------

    properties (Access = public)
        head_
        tail_
        len_
    end  % End of private properties

    methods

        function ll = Linked_List()
            ll.head_ = NaN;
            ll.tail_ = NaN;
            ll.len_ = 0;
        end  % End of constructor

        function disp(obj)
            printf("Linked_List(");
            current = obj.head_;

            while isa(current, "Linked_List_Node")
                printf("%d", current.data());
                current = current.next();
                if isa(current, "Linked_List_Node")
                    printf(", ");
                end  % End of if (isa(current, "Linked_List_Node"))
            end  % End of while (isa(current, "Linked_List_Node"))

            printf(")\n");

        end  % End of disp

        function result = str_repr(obj)
            result = "Linked_List(";
            current = obj.head_;

            while isa(current, "Linked_List_Node")
                result = strcat(result, num2str(current.data()));
                current = current.next();
                if isa(current, "Linked_List_Node")
                    result = strcat(result, ", ");
                end  % End of if (isa(current, "Linked_List_Node"))
            end  % End of while (isa(current, "Linked_List_Node"))

            result = strcat(result, ")");

        end  % End of str_repr

        function len = length(obj)
            len = obj.len_;
        end  % End of length

        function empty = is_empty(obj)
            empty = obj.len_ == 0;
        end  % End of is_empty

        function push_back(obj, data)
            current = Linked_List_Node(data);

            if obj.is_empty()
                obj.head_ = current;
                obj.tail_ = current;
            else
                obj.tail_.set_next(current);
                obj.tail_ = current;
            end  % End of if (obj.is_empty())

            obj.len_ = obj.len_ + 1;

        end  % End of push_back

        function lln = pop_back(obj)
            if obj.is_empty()
                lln = NaN;
                return
            end  % End of if (obj.is_empty())

            lln = obj.head_;
            prev = NaN;

            while ...
                    isa(lln, "Linked_List_Node") && ...
                    isa(lln.next(), "Linked_List_Node")
                prev = lln;
                lln = lln.next();
            end  % End of while ( ...

            if isa(prev, "Linked_List_Node")
                prev.set_next(NaN);
                obj.tail_ = prev;
            else
                obj.head_ = NaN;
                obj.tail_ = NaN;
            end  % End of if(isa(prev, "Linked_List_Node"))

            obj.len_ = obj.len_ - 1;

        end  % End of pop_back

        function push_front(obj, data)
            current = Linked_List_Node(data);

            if obj.is_empty()
                obj.head_ = current;
                obj.tail_ = current;
            else
                current.set_next(obj.head_);
                obj.head_ = current;
            end  % End of if (obj.is_empty())

            obj.len_ = obj.len_ + 1;

        end  % End of push_front

        function lln = pop_front(obj)
            if obj.is_empty()
                lln = NaN;
                return
            end  % End of if (obj.is_empty())

            lln = obj.head_;
            obj.head_ = obj.head_.next();
            obj.len_ = obj.len_ - 1;

        end  % End of pop_front

        function lln = get(obj, idx)
            if idx < 0 || idx >= obj.len_
                lln = NaN;
                return
            end  % End of if (idx < 0 || idx >= obj.len_)

            lln = obj.head_;

            for i = 1:idx
                lln = lln.next();
            end  % End of for i = 1:idx

        end  % End of get

        function set(obj, idx, data)
            if idx < 0 || idx >= obj.len_
                return
            end  % End of if (idx < 0 || idx >= obj.len_)

            lln = obj.head_;

            for i = 1:idx
                lln = lln.next();
            end  % End of for i = 1:idx

            lln.set_data(data);

        end  % End of set

        function insert(obj, idx, data)
            if idx < 0 || idx > obj.len_
                return
            end  % End of if (idx < 0 || idx > obj.len_)

            if idx == 0
                obj.push_front(data);
                return
            end  % End of if (idx == 0)

            if idx == obj.len_
                obj.push_back(data);
                return
            end  % End of if (idx == obj.len_)

            current = obj.head_;

            for i = 1:idx - 1
                current = current.next();
            end  % End of for i = 1:idx-1

            new_node = Linked_List_Node(data);
            new_node.set_next(current.next());
            current.set_next(new_node);
            obj.len_ = obj.len_ + 1;

        end  % End of insert

        function lln = delete(obj, idx)
            if idx < 0 || idx >= obj.len_
                lln = NaN;
                return
            end  % End of if (idx < 0 || idx >= obj.len_)

            if idx == 0
                lln = obj.pop_front();
                return
            end  % End of if (idx == 0)

            if idx == obj.len_ - 1
                lln = obj.pop_back();
                return
            end  % End of if (idx == obj.len_-1)

            current = obj.head_;

            for i = 1:idx - 1
                current = current.next();
            end  % End of for i = 1:idx-1

            lln = current.next();
            current.set_next(current.next().next());
            obj.len_ = obj.len_ - 1;

        end  % End of delete

        function reverse(obj)
            if obj.is_empty()
                return
            end  % End of if (obj.empty())

            prev = NaN;
            current = obj.head_;
            next = current.next();

            while isa(next, "Linked_List_Node")
                current.set_next(prev);
                prev = current;
                current = next;
                next = next.next();
            end  % End of while (isa(next, "Linked_List_Node"))

            current.set_next(prev);
            obj.tail_ = obj.head_;
            obj.head_ = current;

        end  % End of reverse

    end  % End of methods

end  % End of class Linked_List

% End of file Linked_List.m
