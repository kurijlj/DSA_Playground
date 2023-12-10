classdef Linked_List_Node < handle
    %% -------------------------------------------------------------------------
    %%
    %% Class: Linked_List_Node
    %%
    %% -------------------------------------------------------------------------
    %
    %% Description: This class implements a common node for a linked list.
    %
    %% Properties:
    %       data_ - The data stored in the node.
    %       next_ - The next node in the linked list.
    %
    %% Methods:
    %       Linked_List_Node(data) - Constructor.
    %       getData()              - Returns the data stored in the node.
    %       setData(data)          - Sets the data stored in the node.
    %       getNext()              - Returns the next node in the linked list.
    %       setNext(next)          - Sets the next node in the linked list.
    %       disp()                 - Displays the node.
    %       str_rep()              - Returns a string representation of
    %                                the node.
    %
    %% Example:
    %       lln = Linked_List_Node(1);
    %       lln.disp();
    %       lln.str_rep();
    %
    %% (C) Copyright 2023 Ljubomir Kurij
    %
    %% -------------------------------------------------------------------------

    properties (Access = private)
        data_ = NaN
        next_ = NaN
    end   % End of private properties

    methods

        function lln = Linked_List_Node(data)
            lln.data_ = data;
        end   % End of constructor

        function data = data(obj)
            data = obj.data_;
        end   % End of data method

        function set_data(obj, data)
            obj.data_ = data;
        end   % End of set_data method

        function next = next(obj)
            next = obj.next_;
        end   % End of next method

        function set_next(obj, next)
            obj.next_ = next;
        end   % End of set_next method

        function disp(obj)
            printf("Linked_List_Node(%d)\n", obj.data_);
        end   % End of disp method

        function result = str_repr(obj)
            result = sprintf("Linked_List_Node(%d)", obj.data_);
        end   % End of str_repr method

    end   % End of methods

end   % End of LinkedListNode class

% End of file LinkedListNode.m
