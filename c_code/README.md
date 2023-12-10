# C Code

This repository contains a C implementation of essential data structures and algorithms.

- [C Code](#c-code)
  - [Directory Contents](#directory-contents)
  - [Compiling Instructions](#compiling-instructions)

## Directory Contents
- [**datastructures**](./src/datastructures/)
  - [*linkedlist*](./src/datastructures/linkedlist/) - This directory includes the
  implementation of a common singly linked list.
- [**leetcode_exercises**](./src/leetcode_exercises/)
  - [*find_middle_node*](./src/leetcode_exercises/find_middle_node/) - Here, you can
  find the implementation of the slow and fast pointer algorithm for retrieving
  the index of a middle list node.

## Compiling Instructions
Build as a regular CMake project:
1. Create a build directory and `cd` into it. Then create a directory structure
and makefiles using:
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -S ./path/to/src -B .
$ cmake --build . --config Debug
```
or
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -S ./path/to/src -B .
$ make
```

for \*NIX platforms,

2. or using:
```
$ cmake -DCMAKE_C_COMPILER=clang -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -S ./path/to/src -B .
$ cmake --build . --config Debug
```
or
```
$ cmake -DCMAKE_C_COMPILER=clang -DBUILD_SHARED_LIBS:BOOL=FALSE -DBUILD_TESTING:BOOL=FALSE -S ./path/to/src -B .
$ msbuild.exe myproject.sln
```

for the Win64 platform.

Build parameters can take the following values:
```
-DCMAKE_C_COMPILER=(clang-c/cl/gcc/...)
-DCMAKE_BUILD_TYPE=(Debug/RelWithDebInfo/Release/MinSizeRel)
-DBUILD_SHARED_LIBS:BOOL=(TRUE/FALSE)
-DBUILD_TESTING:BOOL=(TRUE/FALSE)
-G ("NMake Makefiles"/"Unix Makefiles"/...)
```