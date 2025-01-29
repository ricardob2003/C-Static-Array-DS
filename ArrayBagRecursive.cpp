// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2025 Pearson Education, Hoboken, New Jersey.

/** Implementation file for the class ArrayBagRecursive: Recursive version.
 @file ArrayBagRecursive.cpp */

#include "ArrayBagRecursive.h"
#include "random" //RB 01-27-25: Included for random number generation
#include <cstddef>
#include <iostream> // RB 01-26-2025: Included for std::cout and std::endl

/** RB 01-23-25: Refactor to support a dynamic array. The class will dynamically resize
 its storage array to accommodate more items.
 Initial capacity is at 10, and will double in size when the array is full.
*/

// Constructor
template <class ItemType>
ArrayBagRecursive<ItemType>::ArrayBagRecursive() : itemCount(0), maxItems(10)
{
   items = new ItemType[maxItems]; // Allocate memory for the dynamic array
}

// Destructor
// RB 01-23-25: Destructor added to free dynamically allocated memory
template <class ItemType>
ArrayBagRecursive<ItemType>::~ArrayBagRecursive()
{
   delete[] items;  // RB 01-23-25: Free the memory allocated for the array
   items = nullptr; // RB 01-23-25: Set the pointer to null to avoid dangling pointers
}

/** RB 01-26-2025: Resizes the dynamic array when the bag is full. */
template <class ItemType>
void ArrayBagRecursive<ItemType>::resizeArray()
{
   std::cout << "Resizing the array. Old capacity: " << maxItems; // RB 01-26-2025: Log before resizing
   maxItems *= 2;                                                 // RB 01-26-2025: Double the capacity
   ItemType *tempItems = new ItemType[maxItems];                  // RB 01-26-2025: Allocate a new larger array

   // RB 01-26-2025: Copy existing items into the new array
   for (int i = 0; i < itemCount; ++i)
   {
      tempItems[i] = items[i];
   }

   delete[] items;                                             // RB 01-26-2025: Free the old array
   items = tempItems;                                          // RB 01-26-2025: Update the pointer to the new array
   std::cout << " -> New capacity: " << maxItems << std::endl; // RB 01-26-2025: Log after resizing
} // end resizeArray

// Get the current size of the bag
template <class ItemType>
int ArrayBagRecursive<ItemType>::getCurrentSize() const
{
   return itemCount;
}

// Check if the bag is empty
template <class ItemType>
bool ArrayBagRecursive<ItemType>::isEmpty() const
{
   return itemCount == 0;
}

/** RB 01-26-2025: Adds a new item to the bag, resizing if necessary. */
template <class ItemType>
bool ArrayBagRecursive<ItemType>::add(const ItemType &newEntry)
{
   if (itemCount == maxItems) // RB 01-26-2025: Check if resizing is needed
   {
      resizeArray(); // RB 01-26-2025: Resize the array when full
   }

   items[itemCount] = newEntry; // RB 01-26-2025: Add the new item to the array
   itemCount++;                 // RB 01-26-2025: Increment the item count
   return true;                 // RB 01-26-2025: Adding always succeeds due to dynamic resizing
} // end add

/**
 * @brief Removes the first occurrence of a given entry from the bag.
 * @param anEntry The item to be removed from the bag.
 * @return True if the item was successfully removed; otherwise, false.
 * @note RB 01-27-2025: Updated to include debug statements for better traceability.
 */
template <class ItemType>
bool ArrayBagRecursive<ItemType>::remove(const ItemType &anEntry)
{
   // Find the index of the item to be removed
   int locatedIndex = getIndexOf(anEntry, 0);

   // Check if the item exists and the bag is not empty
   bool canRemoveItem = !isEmpty() && (locatedIndex > -1);
   if (canRemoveItem)
   {
      // Replace the removed item with the last item in the array
      items[locatedIndex] = items[itemCount - 1];

      // Decrease the item count
      itemCount--;
   }
   else
   {
      // Debug: Log if the item could not be removed
      std::cerr << "Warning: Could not remove " << anEntry
                << ". Item not found or bag is empty." << std::endl;
   }

   return canRemoveItem;
}

// Clear the bag
template <class ItemType>
void ArrayBagRecursive<ItemType>::clear()
{
   itemCount = 0;
}

// Check if the bag contains a specific item
template <class ItemType>
bool ArrayBagRecursive<ItemType>::contains(const ItemType &anEntry) const
{
   return getIndexOf(anEntry, 0) > -1;
}

// Get the frequency of a specific item in the bag
template <class ItemType>
int ArrayBagRecursive<ItemType>::getFrequencyOf(const ItemType &anEntry) const
{
   return countFrequency(anEntry, 0);
}

// Convert the bag to a vector
template <class ItemType>
std::vector<ItemType> ArrayBagRecursive<ItemType>::toVector() const
{
   std::vector<ItemType> bagContents;
   for (int i = 0; i < itemCount; i++)
   {
      bagContents.push_back(items[i]);
   }
   return bagContents;
}

#include <random> // RB 01-27-2024 For random number generation

/**
 * @brief Randomly selects and removes an item from the bag.
 * @param theBag Reference to the bag from which an item will be removed.
 * @return The randomly selected item.
 * @note If the bag is empty, a default-constructed ItemType is returned with a warning.
 * @note RB 01-27-2025: Added debug messages to track random selection and removal.
 */
template <class ItemType>
ItemType ArrayBagRecursive<ItemType>::grabFromBag(ArrayBagRecursive<ItemType> &theBag)
{
   // Check if the bag is empty
   if (theBag.getCurrentSize() == 0)
   {
      std::cerr << "Warning: Cannot grab from an empty bag." << std::endl;
      return ItemType(); // Return default-constructed ItemType
   }

   // Select a random index within the current size
   int randomIndex = rand() % theBag.getCurrentSize();
   ItemType grabbedItem = theBag.items[randomIndex];
   // Attempt to remove the selected item
   if (!theBag.remove(grabbedItem))
   {
      std::cerr << "Error: Failed to remove " << grabbedItem
                << ". This may indicate an issue with remove logic." << std::endl;
   }

   return grabbedItem; // Return the randomly selected item
}

// Private helper: Count the frequency of an item
template <class ItemType>
int ArrayBagRecursive<ItemType>::countFrequency(const ItemType &anEntry, int searchIndex) const
{
   int frequency = 0;
   if (searchIndex < itemCount)
   {
      if (items[searchIndex] == anEntry)
      {
         frequency = 1 + countFrequency(anEntry, searchIndex + 1);
      }
      else
      {
         frequency = countFrequency(anEntry, searchIndex + 1);
      }
   }
   return frequency;
}

// Private helper: Get the index of an item
template <class ItemType>
int ArrayBagRecursive<ItemType>::getIndexOf(const ItemType &target, int searchIndex) const
{
   if (searchIndex >= itemCount)
   {
      return -1; // Item not found
   }
   if (items[searchIndex] == target)
   {
      return searchIndex;
   }
   return getIndexOf(target, searchIndex + 1); // Recursive search
}
