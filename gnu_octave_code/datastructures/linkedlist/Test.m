%% -------------------------------------------------------------------------
%%
%% This is a sample test file for the Linked_List class..
%%
%% -------------------------------------------------------------------------
%
%% (C) Copyright 2023 Ljubomir Kurij
%
%% -------------------------------------------------------------------------

%% Clear workspace and close all figures
clear all;
close all;
clc;

%% Create a new list
printf('Creating a new list...\n');
list = Linked_List();

%% Add some elements at the end
printf('Adding some elements at the end ...\n');
printf('Adding 1 ...\n');
list.push_back(1);
printf('Adding 2 ...\n');
list.push_back(2);
printf('Adding 3 ...\n');
list.push_back(3);
printf('Adding 4 ...\n');
list.push_back(4);
printf('Adding 5 ...\n');
list.push_back(5);

%% Print the list
disp(list);

%% Remove the first element
printf('Removing the first element ...\n');
list.pop_front();

%% Print the list
disp(list);

%% Remove the last element
printf('Removing the last element ...\n');
list.pop_back();

%% Print the list
disp(list);

%% Delete the element at index 1
printf('Deleting the element at index 1 ...\n');
list.delete(1);

%% Print the list
disp(list);

%% Insert an element at index 1
printf('Inserting an element at index 1 ...\n');
list.insert(1, 2);

%% Print the list
disp(list);

%% Get the element at index 1
printf('Getting the element at index 1 ...\n');
disp(list.get(1));

%% Add some elements at the beginning
printf('Adding some elements at the beginning ...\n');
printf('Adding 0 ...\n');
list.push_front(0);
printf('Adding -1 ...\n');
list.push_front(-1);
printf('Adding -2 ...\n');
list.push_front(-2);

%% Print the list
disp(list);

%% Set the element at index 1
printf('Setting the element at index 1 to -3 ...\n');
list.set(1, -3);

%% Print the list
disp(list);

%% Get the size of the list
printf('Getting the size of the list ...\n');
disp(list.length());

%% Reverse the list
printf('Reversing the list ...\n');
list.reverse();

%% Print the list
disp(list);
