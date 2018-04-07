#ifndef _SPLAY_TREE_H
#define _SPLAY_TREE_H

#include <string>
#include <iostream>
#include "Map.h"
#include "bst.h"

class splayTree : public BinarySearchTree<std::string, int>, public Map
{
public:
  // default constructor and destructor used
  splayTree();
  virtual ~splayTree();
  /**
  * Adds a word to the map. If this is the first time the word
  * has been encountered, it is added with a count of 1. Otherwise,
  * the count for the word is incremented by 1.
  */
  virtual void add(const std::string& word);

  /**
  * Reports the contents of the map. Each pair of <word, count> is
  * printed to a new line of the stream. The words should appear in
  * alphabetical order, and the count should be separated from the 
  * word by a space.
  */
  virtual void reportAll(std::ostream& output);

private:
  virtual Node<std::string, int>* insertNode(Node<std::string, int>* node, const std::string& toAdd);
  Node<std::string, int>* splay(Node<std::string, int>* node, const std::string& toAdd);
  Node<std::string, int>* leftRotation(Node<std::string, int>* z);
  Node<std::string, int>* rightRotation(Node<std::string, int>* z);
  void inOrderHelper(Node<std::string, int> *r, std::ostream& output) const;
};

#endif
