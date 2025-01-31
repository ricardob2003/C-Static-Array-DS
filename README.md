# Overview
This repository contains an enhanced Abstract Data Type (ADT) Bag implementation in C++, based on the textbook specifications. The project transitions the ArrayBag from a static array to a dynamic, resizable array, ensuring efficient memory management while preventing memory leaks and dangling pointers.

## Key Features
-  Dynamic Resizable Array: The bag starts with a size of 10 and doubles when full.
-  Random Item Selection: Implements grabFromBag() to randomly select an item.
-  Memory Management: Follows GoodMemory.h and GoodMemory.cpp best practices.
-  Thorough Testing: Expanded driver tests with thousands of items.

### Project Structure
BagInterface.h – Defines the ADT interface.
ArrayBagRecursive.h/.cpp – Implements the resizable ArrayBag with recursion.
arrayBagRecursive-driver.cpp – Driver for rigorous testing.
GoodMemory.h/.cpp – Ensures safe memory allocation and deallocation.
