#include <iostream>
#include <vector>
#include "ArrayBagRecursive.h"
#include "ArrayBagRecursive.cpp"

/**
 * @brief Displays the contents of the bag up to a maximum of 40 items.
 *
 * @tparam ItemType The type of items stored in the bag.
 * @param bag A reference to the ArrayBagRecursive object whose contents are to be displayed.
 */
template <typename ItemType>
void displayBag(ArrayBagRecursive<ItemType> &bag)
{
     // RB 01-27-25: Display the size of the bag
     std::cout << "The bag contains " << bag.getCurrentSize() << " items:" << std::endl;
     std::vector<ItemType> bagItems = bag.toVector();

     // RB 01-27-25: Display up to 40 items from the bag
     int numberOfEntries = (int)bagItems.size();
     for (int i = 0; i < numberOfEntries && i < 40; i++)
     {
          std::cout << bagItems[i] << " ";
     }

     // RB 01-27-25: Show a message if there are more than 40 items
     if (numberOfEntries > 40)
     {
          std::cout << "... (" << numberOfEntries - 40 << " more items not shown)";
     }
     std::cout << std::endl
               << std::endl;
}

/**
 * @brief Tests the functionality of the ArrayBagRecursive class, including add, remove, and grabFromBag methods.
 *
 * @tparam ItemType The type of items stored in the bag.
 * @param bag A reference to the ArrayBagRecursive object to be tested.
 * @param numItemsToTest The number of items to add and test in the bag.
 */
template <typename ItemType>
void bagTester(ArrayBagRecursive<ItemType> &bag, int numItemsToTest)
{
     // RB 01-27-25: Check if the bag is initially empty
     std::cout << "isEmpty: returns " << bag.isEmpty()
               << "; should be 1 (true)" << std::endl;
     displayBag(bag);

     // RB 01-27-25: Dynamically generate items of type ItemType
     std::vector<ItemType> items;
     for (int i = 1; i <= numItemsToTest; i++)
     {
          items.push_back(static_cast<ItemType>(i)); // Convert integer to ItemType
     }

     // RB 01-27-25: Add items to the bag and display progress
     std::cout << "Adding " << numItemsToTest << " items to the bag:" << std::endl;
     for (int i = 0; i < numItemsToTest; i++)
     {
          bag.add(items[i]);
          if (i < 40 || i == numItemsToTest - 1 || i % 1000 == 0)
          {
               std::cout << "Added " << items[i] << " to the bag." << std::endl;
          }

          // RB 01-27-25: Test grabFromBag after adding 40 items
          if (i == 39)
          {
               std::cout << "Displaying bag before it exceeds 40 entries:" << std::endl;
               displayBag(bag);

               // Test grabFromBag method
               std::cout << "Testing the grabFromBag method:" << std::endl;
               for (int j = 0; j < 2; j++) // Perform two grabs
               {
                    try
                    {
                         ItemType grabbedItem = bag.grabFromBag(bag);
                         std::cout << "Randomly grabbed item: " << grabbedItem << std::endl;
                         displayBag(bag);
                    }
                    catch (const std::logic_error &e)
                    {
                         std::cout << "Error: " << e.what() << std::endl;
                         break;
                    }
               }
          }
     }

     // RB 01-27-25: Verify the bag's capacity and current size
     std::cout << "Expected capacity: At least " << numItemsToTest
               << ". Actual size: " << bag.getCurrentSize() << std::endl;
     displayBag(bag);

     // RB 01-27-25: Test additional methods
     std::cout << "isEmpty: returns " << bag.isEmpty()
               << "; should be 0 (false)" << std::endl;

     std::cout << "getCurrentSize: returns " << bag.getCurrentSize()
               << "; should be " << numItemsToTest << std::endl;

     std::cout << "contains(500): returns " << bag.contains(static_cast<ItemType>(500))
               << "; should be 1 (true)" << std::endl;

     std::cout << "getFrequencyOf(1): returns "
               << bag.getFrequencyOf(static_cast<ItemType>(1)) << "; should be 1" << std::endl;

     std::cout << "remove(1): returns " << bag.remove(static_cast<ItemType>(1))
               << "; should be 1 (true)" << std::endl;

     std::cout << "getFrequencyOf(1): returns "
               << bag.getFrequencyOf(static_cast<ItemType>(1)) << "; should be 0" << std::endl;

     std::cout << std::endl;

     // RB 01-27-25: Test grabFromBag method again
     std::cout << "\nTesting grabFromBag..." << std::endl;
     for (int i = 0; i < 2; i++) // Perform two grabs
     {
          try
          {
               ItemType grabbedItem = bag.grabFromBag(bag);
               std::cout << "Randomly grabbed item: " << grabbedItem << std::endl;
          }
          catch (const std::logic_error &e)
          {
               std::cout << "Error: " << e.what() << std::endl;
               break;
          }
     }

     displayBag(bag);

     // RB 01-27-25: Clear the bag and verify it is empty
     std::cout << "\nClearing the bag..." << std::endl;
     bag.clear();
     std::cout << "After clearing the bag, isEmpty: returns " << bag.isEmpty()
               << "; should be 1 (true)" << std::endl;
     displayBag(bag);
}

// RB 01-27-25: Test the Object of Bag using a different methodlogy to ensure proper use

template <typename ItemType>
void bagTesterRandom(ArrayBagRecursive<ItemType> &bag, int numItemsToTest)
{
     // Add items to the bag
     std::cout << "Adding items to the bag:" << std::endl;
     for (ItemType i = 1; i <= numItemsToTest; i++)
     {
          bag.add(i);
          bag.add(i); // Add in pairs
     }
     displayBag(bag);

     // Test grabFromBag method
     std::cout << "\nTesting the grabFromBag method:" << std::endl;
     for (int i = 0; i < 2; i++)
     {
          ItemType grabbedItem = bag.grabFromBag(bag);
          std::cout << "Randomly grabbed item: " << grabbedItem << std::endl;
          displayBag(bag);
     }

     // Remove one item from each pair
     std::cout << "\nRemoving one item from each pair:" << std::endl;
     for (ItemType i = 1; i <= 40; i++)
     {
          bag.remove(i);
          std::cout << "Removed " << i << " once." << std::endl;
          std::cout << "getFrequencyOf(" << i << "): " << bag.getFrequencyOf(i) << std::endl;
          std::cout << "getCurrentSize: " << bag.getCurrentSize() << std::endl;
     }

     // Test grabFromBag on an empty bag
     std::cout << "\nTesting grabFromBag on an empty bag:" << std::endl;
     while (bag.getCurrentSize() > 0)
     {
          bag.grabFromBag(bag);
     }
     bag.grabFromBag(bag); // Try grabbing from an empty bag

     // Clear the bag
     std::cout << "\nClearing the bag..." << std::endl;
     bag.clear();
     std::cout << "After clearing the bag, isEmpty: " << bag.isEmpty() << std::endl;
     displayBag(bag);
}

/**
 * @brief The main function to test the ArrayBagRecursive class with integers.
 *
 * @return int Returns 0 on successful execution.
 */
int main()
{
     // RB 01-27-25: Test with integer type
     std::cout << "Testing the Array-Based Bag with integers:" << std::endl;

     ArrayBagRecursive<int> bag; // Use int as the ItemType
     int numItemsToTest = 10000; // Adjust this value to test different sizes
     bagTester(bag, numItemsToTest);
     std::cout << "\n***** Second Test*****\n"
               << std::endl;

     bagTesterRandom(bag, 10000);
     std::cout << "All done!" << std::endl;

     return 0;
}
