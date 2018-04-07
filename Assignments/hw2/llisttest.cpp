#include "llistint.h"
#include <iostream>
#include <stdlib.h> // srand, rand

using namespace std;

int main() {
  LListInt * list = new LListInt();

  srand(time(0));
  int n = 50; // number of list items;

  cout << "Generating values for " << n << " items..." << endl;
  int *input = new int[n];
  for (int i = 0; i < n; i++)
    input[i] = rand() % 100 + 1; // generate a number between 1 and 100
  cout << "Values generated." << endl;

  // Check if the list is initially empty.
  if (list->empty())
    cout << "SUCCESS: List is empty initially." << endl;
  else
    cout << "FAIL:: List is not empty initially when it should be." << endl;

  cout << endl;
  // test edge cases
  cout << "===== Testing INSERT function =====" << endl;
  if (list->empty()) {
    cout << "Trying to insert at location beyond the scope..." << endl;
    list->insert(5, 152);
    list->insert(1, 4);
    cout << "Inserting at a negative position..." << endl;
    list->insert(-1, -10);
    list->insert(-5, 1245);
    if (list->empty())
      cout << "SUCCESS: List is still empty after insertions at invalid locations." << endl;
    else
      cout << "FAIL:: List is not empty when it should be. Check INSERT function." << endl;
  }

  cout << endl;
  // insert a bunch of items in the list
  for (int i = 0; i < n; i++) {
    cout << "Inserting " << input[i] << " to position " << i << endl;
    list->insert(i, input[i]);
  }

  cout << endl;
  // check the number of items in the list
  if (list->size() == n)
    cout << "SUCCESS: The list has " << n << " items." << endl;
  else
    cout << "FAIL:: The list has " << list->size() << " items. Expected " << n << " items." << endl;

  cout << endl;

  // add item beyond the scope of the list. More edge case testing for safety
  cout << "Adding item at " << n << " + 1 position. (1 after end of list)..." << endl;
  list->insert(n+1, 1984);
  cout << "Adding item at " << n << " + 5 position. (5 after end of list)..." << endl;
  if (list->size() == n)
    cout << "SUCCESS: The list still has " << n << " items. INSERT failed and didn't crash." << endl;
  else
    cout << "FAIL:: The list has " << list->size() << " items. Expected " << n << " items. Check INSERT funciton" << endl;

  cout << endl;
  // add at nth position;
  cout << "Adding item at " << n << "th position. (end of list)" << endl;
  list->insert(n, 1984);
  if (list->size() == n+1)
    cout << "SUCCESS: The list has " << n+1 << " items. INSERT at tail is good." << endl;
  else
    cout << "FAIL:: The list has " << list->size() << " items. Expected " << n+1 << " items. Check INSERT funciton" << endl;

  cout << endl;
  int befSize = list->size();
  cout << "Size before inserting at middle: " << list->size() << endl;
  cout << "Now inserting in the middle of the list at location " << list->size()/2 << "..." << endl;
  list->insert(list->size()/2, 10295120);

  if (list->size() == befSize+1)
    cout << "SUCCESS: Size after inserting at middle: " << list->size() << endl;
  else
    cout << "FAIL: Check insert function for the case of inserting in the middle." << endl;

  if (list->get(befSize/2) == 10295120)
    cout << "SUCCESS: Item inserted at the correct location" << endl;
  else
    cout << "FAIL: Wrong inserted value. Check insert function for the case of inserting in the middle." << endl;

  cout << endl;
  cout << "===== Testing REMOVE function =====" << endl;
  if (!list->empty()) {
    cout << "Current size: " << list->size() << ", and the head is: " << list->get(0) << endl;
    cout << "Deleting at head..." << endl;
    list->remove(0);
    cout << "Now the size is: " << list->size() << ", and the head is: " << list->get(0) << endl;
    cout << "tail is: " << list->get(list->size()-1) << endl;
    cout << "Deleting at tail..." << endl;
    list->remove(list->size()-1);
    cout << "Now size is: " << list->size() << ", and the tail is: " << list->get(list->size()-1) << endl;
    cout << "MIDDLE OUT. The middle element is: " << list->get(list->size()/2) << endl;
    cout << "Deleting element at: " << list->size()/2 << endl;
    list->remove(list->size()/2);
    cout << "Now size is: " << list->size() << ", and the middle element is: " << list->get(list->size()/2) << endl;
  }

  befSize = list->size();
  cout << "Trying to remove at location beyond the scope..." << endl;
  list->remove(list->size()+50);
  cout << "Trying to remove at size (n)" << endl;
  list->remove(list->size());
  cout << "Trying to remove at negative index" << endl;
  list->remove(-1);
  list->remove(-5);

  if (list->size() == befSize)
    cout << "SUCCESS: Remove didn't fail and still has the same size!!!" << endl;
  else
    cout << "FAIL: Size mismatch after trying to remove items out of range. Check REMOVE function." << endl;

  cout << "Removing all items from list..." << endl;
  int size = list->size();
  for (int i = 0; i < size; i++) {
    cout << "Removing at " << i << " VAL: " << list->get(0) << endl;
    list->remove(0);
  }

  // check if list empty
  if (list->empty())
    cout << "SUCCESS: List is empty after running remove on all items." << endl;
  else
    cout << "FAIL:: List is not empty after running remove on all items. The size is: " << list->size() << endl;

  cout << "Recreating list..." << endl;
  for (int i = 0; i < n; i++)
    list->insert(i, input[i]);

  bool valChanged = true;
  cout << "Now setting all values to 42..." << endl;
  for (int i = 0; i < list->size(); i++)
    list->set(i, 42);

  for (int i = 0; i < list->size(); i++) {
    if (list->get(i) != 42)
      valChanged = false;
  }

  if (valChanged == true)
    cout << "SUCCESS: All items set to 42" << endl;
  else
    cout << "FAIL: Set function didn't set all values to 42" << endl;

  // Clean up memory.
  delete list;

  delete [] input;
}