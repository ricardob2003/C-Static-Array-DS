// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2025 Pearson Education, Hoboken, New Jersey.

/** Header file for an array-based implementation of the ADT bag.
 @file ArrayBagRecursive.h */

#ifndef ARRAY_BAG_RECURSIVE_
#define ARRAY_BAG_RECURSIVE_

#include "BagInterface.h"
#include <iostream> // 2025-01-26 RB: Included for std::cout and std::endl

template <class ItemType>
class ArrayBagRecursive : public BagInterface<ItemType>
{
private:
	// 2025-01-23 RB: Changed static array into a dynamically allocated array. Removed hardcoded DEFAULT_CAPACITY.

	ItemType *items; // Array of bag items
	int itemCount;	 // Current count of bag items
	int maxItems;		 // Max capacity of the bag

	// 2025-01-23 RB: Returns the index of the target in the array or -1 if not found.
	int getIndexOf(const ItemType &target, int searchIndex) const;

	// 2025-01-23 RB: Recursively counts the frequency of an entry in the array.
	int countFrequency(const ItemType &anEntry, int searchIndex) const;

	// 2025-01-23 RB: Declares the resizeArray method to dynamically expand the array when necessary.
	void resizeArray();

public:
	// 2025-01-23 RB: Constructor initializes the array and its parameters, preventing memory leaks.
	ArrayBagRecursive();

	// 2025-01-23 RB: Destructor frees dynamically allocated memory to prevent memory leaks.
	~ArrayBagRecursive();

	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType &newEntry);
	bool remove(const ItemType &anEntry);
	void clear();
	bool contains(const ItemType &anEntry) const;
	int getFrequencyOf(const ItemType &anEntry) const;
	std::vector<ItemType> toVector() const;

	// 2025-01-23 RB: Declares grabFromBag to randomly select an item from the bag.
	ItemType grabFromBag(ArrayBagRecursive<ItemType> &theBag);
}; // end ArrayBagRecursive

// #include "ArrayBagRecursive.cpp"
#endif
