%% -------------------------------------------------------------------------
%%
%% This is a sample test file for the find_middle_node function
%%
%% -------------------------------------------------------------------------
%
%% (C) Copyright 2023 Ljubomir Kurij
%
%% -------------------------------------------------------------------------

% Clear workspace and close all figures
clear all;
close all;
clc;

% Create an empty list
printf('Creating an empty list...\n');
list = Linked_List();
disp(list);

% Check if find_middle_node works on an empty list
printf('Checking if find_middle_node works on an empty list...\n');
disp(list.find_middle_node());

%% Add a single node to the list
printf('Adding a single node to the list...\n');
list.push_back(1);
disp(list);
% Check if find_middle_node works on a list with a single node
printf('Checking if find_middle_node works on a list with a single node...\n');
disp(list.find_middle_node());

% Extend the lit to even number of nodes
printf('Extending the list to even number of nodes...\n');
list.push_back(2);
list.push_back(3);
list.push_back(4);
disp(list);
% Check if find_middle_node works on a list with even number of nodes
printf( ...
       '%s %s\n', ...
       'Checking if find_middle_node works on a list with', ...
       'even number of nodes...' ...
    );
disp(list.find_middle_node());

% Extend the lit to odd number of nodes
printf('Extending the list to odd number of nodes...\n');
list.push_back(5);
disp(list);
% Check if find_middle_node works on a list with odd number of nodes
printf( ...
       '%s %s\n', ...
       'Checking if find_middle_node works on a list with', ...
       'odd number of nodes...' ...
    );
disp(list.find_middle_node());

% End of test.m
