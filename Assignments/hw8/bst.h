/**
 * bst.h
 *  Implements a(n unbalanced) BST storing Key,Value pairs
 */
#ifndef BST_H
#define BST_H
#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <iomanip>

/* -----------------------------------------------------
 * Regular Binary Tree Nodes
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
  class Node {
 public:
  Node (const KeyType & k, const ValueType & v, Node<KeyType, ValueType> *p)
    : _item(k, v)
   // the default is to create new nodes as leaves
    { _parent = p; _left = _right = NULL; }
  
  virtual ~Node()
  { }
  
  std::pair<const KeyType, ValueType> const & getItem () const
    { return _item; }
  
  std::pair<const KeyType, ValueType> & getItem ()
    { return _item; }
  
  const KeyType & getKey () const
  { return _item.first; }
  
  const ValueType & getValue () const
  { return _item.second; }
  
  /* the next three functions are virtual because for AVL-Trees,
     we'll want to use AVL nodes, and for those, the
     getParent, getLeft, and getRight functions should return 
     AVL nodes, not just ordinary nodes.
     That's an advantage of using getters/setters rather than a struct. */
  
  virtual Node<KeyType, ValueType> *getParent () const
    { return _parent; }
  
  virtual Node<KeyType, ValueType> *getLeft () const
    { return _left; }
  
  virtual Node<KeyType, ValueType> *getRight () const
    { return _right; }

  Node<KeyType, ValueType> *getSuccessor() {
    // edge case. if empty
    if (this == NULL)
      return NULL;
    // create a new node and initialize it to the current location
    Node<KeyType, ValueType>* node = this;

    // Case 1: Node has right subtree
    // fetch the leftmost child
    if (node->getRight() != NULL) { // if the node has a right child
      node = getRight();
      // go all the way down to the left
      while (node->getLeft() != NULL)
        node = node->getLeft();
      return node;  // return the leftmost node
    }
    // Case 2: No right subtree
    // if not get the parent's leftmost child
    Node<KeyType, ValueType>* parent = node->getParent();  // get the node's parent
    while(parent != NULL && node == parent->getRight()) {
      node = parent; 
      parent = parent->getParent();
    }
    return parent;
  }

  void setParent (Node<KeyType, ValueType> *p)
  { _parent = p; }
  
  void setLeft (Node<KeyType, ValueType> *l)
  { _left = l; }
  
  void setRight (Node<KeyType, ValueType> *r)
  { _right = r; }
  
  void setValue (const ValueType &v)
  { _item.second = v; }

  void setKey (const KeyType &k)
  { _item.first = k; }
  
 protected:
  std::pair<const KeyType, ValueType> _item;
  Node <KeyType, ValueType> *_left, *_right, *_parent;
};

/* -----------------------------------------------------
 * Regular Binary Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class BinarySearchTree {
 protected:
  // Main data member of the class
  Node<KeyType, ValueType> *root;

 public:
  /**
   * Constructor
   */
  BinarySearchTree () { root = NULL; }

  /**
   * Destructor
   */
  virtual ~BinarySearchTree () { deleteAll (root); }

  /**
   * Prints the entire tree structure in a nice format 
   *  
   * It will denote subtrees in [] brackets.
   *  This could be helpful if you want to debug your functions. 
   */  
  void print () const
  { 
    printRoot (root);
    std::cout << "\n";
  }

  void postPrint() {
    if (this->root != NULL)
      postPrintHelper(root, 0);
  }

  bool empty () {
    return root == NULL;
  }
  /*
   * returns the minimum of the subtree
   */
  Node<KeyType, ValueType> *getMin(Node<KeyType, ValueType> *node) {
    Node<KeyType, ValueType> *curr = node;

    while (curr->getLeft() != NULL)
      curr = curr->getLeft();
    return curr;
  }
    
  /**
   * An In-Order iterator
   *  !!! You must implement this !!!
   */
  class iterator {
  public:
    /**
     * Initialize the internal members of the iterator
     */
    // iterator() {}
    iterator(Node<KeyType,ValueType>* ptr) {
      curr = ptr;
    }
    
    std::pair<const KeyType,ValueType>& operator*()
      { return curr->getItem();  }
    
    std::pair<const KeyType,ValueType>* operator->() 
      { return &(curr->getItem()); }
    
    /**
     * Checks if 'this' iterator's internals have the same value
     *  as 'rhs'
     */
    bool operator==(const iterator& rhs) const {
      return curr == rhs.curr;
    }
    
    /**
     * Checks if 'this' iterator's internals have a different value
     *  as 'rhs'
     */
    bool operator!=(const iterator& rhs) const {
      return curr != rhs.curr;
    }
    
    /**
     * Advances the iterator's location using an in-order sequencing
     */
    iterator& operator++() {
      curr = curr->getSuccessor();
      return *this;
    }
    
  protected:
    Node<KeyType, ValueType>* curr;
    //you are welcome to add any necessary variables and helper functions here.
  };
  
  /**
   * Returns an iterator to the "smallest" item in the tree
   */
  iterator begin() {
    Node<KeyType, ValueType>* walk = root;
    // go all the way to the left until no more left children left
    // smallest value is the leftmost chold
    while (walk->getLeft() != NULL)
      walk = walk->getLeft();
    return iterator(walk);
  }

  /**
   * Returns an iterator whose value means INVALID
   */
  iterator end() {
    iterator bst(NULL);
    //return iterator(NULL);
    return bst;
  }
  
  /**
   * Returns an iterator to the position of the given key
   */
  iterator find(const KeyType & key) {
    Node<KeyType, ValueType>* val = internalFind(key);
    return iterator(val);
  }

 protected:
  /**
   * Helper function to find a node with given key, k and 
   * return a pointer to it or NULL if no item with that key
   * exists
   */
  Node<KeyType, ValueType>* internalFind(const KeyType& k) const 
  {
    Node<KeyType, ValueType> *curr = root;
    while (curr) {
      if (curr->getKey() == k) {
	return curr;
      } else if (k < curr->getKey()) {
	curr = curr->getLeft();
      } else {
	curr = curr->getRight();
      }
    }
    return NULL;
  }
  
  /**
   * Helper function to print the tree's contents
   */
  void printRoot (Node<KeyType, ValueType> *r) const
  {
    if (r != NULL) {
      std::cout << "[";
      printRoot (r->getLeft());
      std::cout << " (" << r->getKey() << ", " << r->getValue() << ") ";
      printRoot (r->getRight());
      std::cout << "]";
    }
  }

  /*
   * Post order traversal. Much easier to read
   */
  void postPrintHelper(Node<KeyType, ValueType>* node, int indentation) {
    if (node != NULL)
      std::cout << std::setw(indentation) << std::right << "-" << node->getKey() << std::endl;
    if(node->getLeft() != NULL)
      postPrintHelper(node->getLeft(), indentation+3);
    if(node->getRight() != NULL)
      postPrintHelper(node->getRight(), indentation+3);
  }


  /**
   * Helper function to delete all the items
   */
  void deleteAll (Node<KeyType, ValueType> *r)
  {
    if (r != NULL)
      {
	deleteAll (r->getLeft());
	deleteAll (r->getRight());
	delete r;
      }
  }

  
};

#endif
