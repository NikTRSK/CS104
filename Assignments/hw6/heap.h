#ifndef __HEAP_H
#define __HEAP_H

#include <vector>
#include <utility>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <stdexcept>


template <typename T>
class MinHeap {
   public:
     MinHeap (int d);
     /* Constructor that builds a d-ary Min Heap
        This should work for any d >= 2,
        but doesn't have to do anything for smaller d.*/

     ~MinHeap ();

     void add (T item, int priority);
       /* adds the item to the heap, with the given priority. */

     const T & peek () const;
       /* returns the element with smallest priority. */

     void remove ();
       /* removes the element with smallest priority. */

     bool isEmpty ();
       /* returns true iff there are no elements on the heap. */

     //=====================
     // VISUALIZER FUNCTIONS
     //=====================
     // prints the priorities of all nodes at a given level
     void printLevel(int level);
     // postorder traversal of the tree. Prints the structure of the tree
     void printTree();

 private:
    std::vector<std::pair<T, int> > items;  // stores the actual values as pairs(Item, priority)
    int d_ary; // type of the heap
    //=====================
    // HELPER FUNCTIONS
    //=====================
    void bubbleUp(int pos); // used for the add function
    void trickleDown(int parent);  // used for the remove function
    void printTreeHelper(int level, int indentation); // used by the printTree()
    int getSmallestChild(int child);  // used by trickleDown to find the smallest child of a parent
};

template <typename T>
MinHeap<T>::MinHeap(int d) {
  if (d >= 2) {
    d_ary = d;
  }
  else
    throw std::out_of_range ("Cannot create a MinHeap smaller than 2");
}

template <typename T>
MinHeap<T>::~MinHeap() {}

template <typename T>
void MinHeap<T>::add(T item, int priority) {
  items.push_back(std::make_pair(item, priority));  // add the new item at the end
  bubbleUp(items.size()-1); // pass in the added element
}

template <typename T>
const T & MinHeap<T>::peek() const {
  if (items.empty())
    throw std::out_of_range ("Heap is empty");
  return items.at(0).first;
}

template <typename T>
void MinHeap<T>::remove() {
   // The C++ developers though that undefined behavior for one of the core classes is a good thing.
  iter_swap(items.begin() + 0, items.begin() + items.size()-1); // swap the first and last items
  items.pop_back(); // remove the last (smallest) values
  trickleDown(0); // properly reorder the items
}

template <typename T>
bool MinHeap<T>::isEmpty() {
  return items.empty();
}

template <typename T>
void MinHeap<T>::printLevel(int level) {
  if ( (d_ary*pow(level-1,2)+1) >= items.size() ) // if out of bounds nothing to print
    return;
  if (level == 0) // if at root level print root
    std::cout << items.at(0).second;
  else {
    int initNode = d_ary*pow(level-1,2)+1;  // get the initial node at the level
    // print all the nodes at the level
    for (int i = initNode; i < initNode + pow(d_ary, level); i++) {
      if (i < items.size())
        std::cout << items.at(i).second << "   ";
    }
  }
  std::cout << std::endl;
}

template <typename T>
void MinHeap<T>::printTree() {
  if (!items.empty())
    printTreeHelper(0, 0);
}

template <typename T>
void MinHeap<T>::printTreeHelper(int level, int indentation) {
  // only do stuff if there are items at the level
  if (level < items.size() && !items.empty()) {
    std::cout << std::setw(indentation) << std::right << "-" << items.at(level).second << std::endl;
    // recurse on each child and print it's children
    for (int child = level*d_ary+1; child <= level*d_ary + d_ary; child++)
      printTreeHelper(child, indentation+3);
  }
  else
    return;
}

// HELPER FUNCTIONS
template <typename T>
void MinHeap<T>::bubbleUp(int pos) {
  // swap items if inbounds and if parent is smaller than child
  if ((pos > 0 && pos < items.size()) && items.at(pos).second < items.at((pos-1)/d_ary).second) {
    iter_swap(items.begin() + pos, items.begin() + ((pos-1)/d_ary));
    bubbleUp((pos-1)/d_ary);  // rinse and repeat
  }
}

template <typename T>
void MinHeap<T>::trickleDown(int parent) {
  int child = d_ary*parent+1;  // initialize the child of parent
  if (child < items.size() && parent < items.size()) {  // both child and parents are inbound
    int smallestChild = getSmallestChild(child);  // grab the smallest child
    // if child is smaller than parent swap
    if (items.at(smallestChild).second < items.at(parent).second) {
      iter_swap(items.begin() + smallestChild, items.begin() + parent);
    }
    trickleDown(smallestChild); // rinse and repeat. Now check smallestChild's children
  }
}

template <typename T>
int MinHeap<T>::getSmallestChild(int child) {
  int smallestChild = child;  // make the first element as the smallest
  // starting at child+1 since we already set child to be smallest
  for (int i = child+1; i < child+d_ary; i++) {
    if (i < items.size()) { // if there are children to check
      // if i smaller then make it the smallestChild
      if (items.at(smallestChild).second > items.at(i).second)
        smallestChild = i;
    }
  }
  return smallestChild;
}

#endif