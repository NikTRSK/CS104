/*
 * avlbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 * 2016-03-31  Cote      Modify for AVL Trees
 */
#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>  // maybe not needed
#include <stdexcept>
#include <cstdlib>
#include <algorithm>  // max
#include "bst.h"

template <class KeyType, class ValueType>
class AVLNode : public Node<KeyType, ValueType>
{
public:
  AVLNode (KeyType k, ValueType v, AVLNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { height = 1; } // changed this. Can I?
  
  virtual ~AVLNode () {}
  
  int getHeight () const
    { return height; }
  
  void setHeight (int h)
    { height = h; }
  
  virtual AVLNode<KeyType, ValueType> *getParent () const
    { return (AVLNode<KeyType,ValueType>*) this->_parent; }
  
  virtual AVLNode<KeyType, ValueType> *getLeft () const
    { return (AVLNode<KeyType,ValueType>*) this->_left; }
  
  virtual AVLNode<KeyType, ValueType> *getRight () const
    { return (AVLNode<KeyType,ValueType>*) this->_right; }

 protected:
  int height;
};

/* -----------------------------------------------------
 * AVL Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class AVLTree : public BinarySearchTree<KeyType, ValueType>
{
public:

  void insert (const std::pair<const KeyType, ValueType>& new_item) {
  /* This one is yours to implement.
     It should insert the (key, value) pair to the tree, 
     making sure that it remains a valid AVL Tree.
     If the key is already in the tree, you should throw an exception. */
    // first we insert the new node using standard BST insert. Thank you Lab12 :)
    this->root = insertNode(static_cast<AVLNode<KeyType,ValueType>*>(this->root), new_item);
  }
  void remove (const KeyType &toRemove) {
  /* Implement this as well.  It should remove the (key, value) pair from
   * the tree which corresponds to the input parameter.
   * If the key is not in the tree, you should throw an exception.
   */

    this->root = removeNode(static_cast<AVLNode<KeyType,ValueType>*>(this->root), toRemove);
  }

  /*
   * Updates the value of the given key
   */
  void update (const KeyType &key, const ValueType &updatedValue) {
    Node<KeyType, ValueType>* updateVal = this->internalFind(key);
    if (updateVal == NULL)
      throw std::runtime_error("Item doesn't exist");
    updateVal->setValue(updatedValue);
  }

  private:

  /*
   * Insertion helper function
   */
  virtual AVLNode<KeyType, ValueType>* insertNode(AVLNode<KeyType, ValueType>* node, const std::pair<KeyType, ValueType>& toAdd) {
    if (node == NULL){
      AVLNode<KeyType, ValueType> * item = new AVLNode<KeyType, ValueType>(toAdd.first, toAdd.second, node);
      return item;
    }
    
    if (toAdd.first == node->getKey())
      throw std::runtime_error("Item already exists");
    else if (toAdd.first < node->getKey()) {
      node->setLeft(insertNode(node->getLeft(), toAdd));
    }
    else  {
      node->setRight(insertNode(node->getRight(), toAdd));
    }

    // set the old node's parent if inserting not at a leaf node
    if (node->getLeft() != NULL)
      node->getLeft()->setParent(node);
    if (node->getRight() != NULL)
      node->getRight()->setParent(node);
    
    // set/update height
    node->setHeight(1 + std::max(height(node->getLeft()), height(node->getRight()) ));
    return balanceTree(node, toAdd.first);
  }

  /*
   * Rebalancing function. Rebalances subtree if needed. If not returns the node
   */
  virtual AVLNode<KeyType, ValueType>* balanceTree(AVLNode<KeyType, ValueType>* node, const KeyType& toAdd) {
    bool balanced = isBalanced(node);
    if (!balanced) {
      // get the balance factor
      int balance = getBalance(node);
      if (balance > 1 && getBalance(node->getLeft()) >= 0)
        return rightRotation(node);
      // Left-Right case. Needs 2 rotations
      if (balance > 1 && getBalance(node->getLeft()) < 0) {
        // first perform a Left rotation on the left child
        node->setLeft(leftRotation(node->getLeft()));
        // then right rotate the node itself
        return rightRotation(node);
      }
      // Right-Right case
      if (balance < -1 && getBalance(node->getRight()) <= 0)
        return leftRotation(node);
      // Right-Left case. Needs 2 rotations
      if (balance < -1 && getBalance(node->getRight()) > 0) {
        // first perform a right rotation on the right child
        node->setRight(rightRotation(node->getRight()));
        // then left rotate the node itself
        return leftRotation(node);
      }
    }
    // node is balanced just return node
    return node;
  }  

  /*
    Rotations
  */
  // L-L case: 1 R rotation | L-R case: 1 L rotation, then 1 R rotation
  // R-R case: 1 L rotation | R-L case: 1 R rotation, then 1 L rotation
  AVLNode<KeyType, ValueType>* leftRotation(AVLNode<KeyType, ValueType>* z) {
    // temp pointers for rotation
    AVLNode<KeyType, ValueType>* zParent = z->getParent();
    AVLNode<KeyType, ValueType>* y = z->getRight(); // this will be the new root
    AVLNode<KeyType, ValueType>* T3 = y->getLeft();

    // pair y and z's parent
    // if z is the root
    if (zParent == NULL)
      y->setParent(NULL);
    else {
      if (zParent->getRight() == z)
        zParent->setRight(y);
      else
        zParent->setLeft(y);
      y->setParent(zParent);
    }

    // pair z and y->left
    z->setParent(y);
    y->setLeft(z);

    // pair T3 and z->right
    if (T3 != NULL)
      T3->setParent(z);
    z->setRight(T3);

    // height have changed for the shifted subtrees so we have to recalculate them
    z->setHeight(1 + std::max(height(z->getLeft()), height(z->getRight()) ));
    y->setHeight(1 + std::max(height(y->getLeft()), height(y->getRight()) ));
    
    // y is the new root of the subtree so we have to return it
    return y;
  }

  AVLNode<KeyType, ValueType>* rightRotation(AVLNode<KeyType, ValueType>* z) {
    // temp pointers for rotation
    AVLNode<KeyType, ValueType>* zParent = z->getParent();
    AVLNode<KeyType, ValueType>* y = z->getLeft(); // this will be the new root
    AVLNode<KeyType, ValueType>* T3 = y->getRight();

    // pair y and z's parent
    // if z is the root
    if (zParent == NULL)
      y->setParent(NULL);
    else {
      if (zParent->getRight() == z)
        zParent->setRight(y);
      else
        zParent->setLeft(y);
      y->setParent(zParent);
    }

    // pair z and y->right
    z->setParent(y);
    y->setRight(z);
    // z->setRight(NULL);

    // pair T3 and z->left
    if (T3 != NULL)
      T3->setParent(z);
    z->setLeft(T3);

    // height have changed for the shifted subtrees so we have to recalculate them
    z->setHeight(1 + std::max(height(z->getLeft()), height(z->getRight()) ));
    y->setHeight(1 + std::max(height(y->getLeft()), height(y->getRight()) ));

    // y is the new root of the subtree so we have to return it
    return y;
  }

  /*
   * Reduntant, but I'm afraid to mess with it, so I'll just leave it in
   */
  int height(AVLNode<KeyType, ValueType>* node) {
    // if tree is empty the height=0
    if (node == NULL)
      return 0;

    return node->getHeight();
  }

  /*
   * Checks the subtree balance
   */

  int getBalance(AVLNode<KeyType, ValueType>* root) {
    // an empty tree is a balanced tree
    if (root == NULL)
      return 0;
    return height(root->getLeft()) - height(root->getRight());
  }

  bool isBalanced(AVLNode<KeyType, ValueType>* root) {   
    // we can do this since we only care if it is balanced
    return std::abs(getBalance(root)) < 2;
  }

  /*
   * Swaps two nodes by reassigning pointers. THE BANE OF MY EXISTENCE
   * It's pretty messy (sorry) but it works so I'm not touching it.
   */
  void swapNodes(AVLNode<KeyType, ValueType> *& from, AVLNode<KeyType, ValueType> *& to) {
    // if at root change swap root with the minChild
    if (from == this->root) {
      // from->setParent(NULL);
      this->root = to;
    }
    if (to == this->root) {
      // to->setParent(NULL);
      this->root = from;
    }

    AVLNode<KeyType, ValueType> *fromP = from->getParent();
    AVLNode<KeyType, ValueType> *fromL = from->getLeft();
    AVLNode<KeyType, ValueType> *fromR = from->getRight();

    AVLNode<KeyType, ValueType> *toP = to->getParent();
    AVLNode<KeyType, ValueType> *toL = to->getLeft();
    AVLNode<KeyType, ValueType> *toR = to->getRight();

    // min child
    // if from has a parent
    if (from->getParent() != NULL)
      to->setParent(fromP);
    else
      to->setParent(NULL);

    // if neighbors
    // neighbor to right
    /*      15
           /  \....
          10 (from)
         /  \
        1   14 (to)
     */
    if (from->getRight() == to) {
      // set pointers for from node.
      from->setParent(to);
      from->setLeft(NULL);
      if (to->getRight() != NULL)
        from->setRight(toR);
      else
        from->setRight(NULL);
      // set pointers for to (minchild) node
      to->setRight(from);
      to->setLeft(fromL);

      // set that pointers back to the nodes
      // from's L child now points to to
      if (fromL->getParent() != to)
        fromL->setParent(to);

      // safety check
      if (fromP != NULL){
        // reasign from's parent to point to to
        
        // assign a child to from's parent
        if (fromP->getLeft() == from)
          fromP->setLeft(to);
        else if (fromP->getRight() == from)
          fromP->setRight(to);
        // if (fromP->getLeft() != to)
        //   fromP->setLeft(to);
      }

      // special case. if one item and there is a right parent
      if (from->getRight() != NULL) {

        // when in doubt use a temp pointer. aka brain fart
        // points to the to->r (most cases it's null)
        AVLNode<KeyType, ValueType> *tempR = from->getRight();

        // set from's parent right child to be from's right child
        from->getParent()->setRight(tempR);
        // set from->right's parent to to
        tempR->setParent(to);
        // not really needed since it's not gonna have left children, but what the heck. play it safe
        tempR->setLeft(NULL);

        // in case tempR has children
        if (tempR->getRight() != NULL) {
          from->setRight(tempR->getRight());
          tempR->setParent(from);
        }
        else {
          // shift from to be to the right
          tempR->setRight(from);
          // from points to it's child now
          from->setParent(tempR);
          from->setRight(NULL);
        }
      }
    }
    else {
      //to parent set
      from->setParent(toP);
      from->setLeft(toL);
      from->setRight(toR);

      to->setRight(fromR);
      to->setLeft(fromL);

      // from's parent now points to to
      if (fromP == NULL)
        to->setParent(NULL);
      else if (fromP->getRight() == from)
        to->getParent()->setRight(to);
      // if from is a root node
      else if (fromP->getLeft() == from)
        to->getParent()->setLeft(to);
      
      // to's parent now points to from
      if (toP == NULL)
        to->setParent(NULL);
      else if (toP->getRight() == to)
        from->getParent()->setRight(from);
      else if (toP->getLeft() == to)
        from->getParent()->setLeft(from);

      // set to's Parent
      if (toP == from) {
        toP->setRight(NULL);
        toP->setLeft(from);
      }

      // make to parent for it's children
      if (to->getLeft() != NULL)
        to->getLeft()->setParent(to);
      if (to->getRight() != NULL)
        to->getRight()->setParent(to);
    }    

    // swap node (from) and temp (to)
    AVLNode<KeyType, ValueType> *temp = to;
    to = from;
    from = temp;
  }

  /*
   * Remove Helper function. Throws an exception if node doesn't exist.
   */
  AVLNode<KeyType, ValueType> *removeNode(AVLNode<KeyType, ValueType> *node, const KeyType &toRemove) {

    // base case
    if(node == NULL) //return node; 
      throw std::runtime_error("Item doesn't exist.");
    
    if(toRemove < node->getKey()) node->setLeft(removeNode(node->getLeft(), toRemove));
    else if (toRemove > node->getKey()) node->setRight(removeNode(node->getRight(), toRemove));
    
    else {
      // if the node has one child
      // if it has only right child
      if (node->getLeft() == NULL) {
        Node<KeyType, ValueType> *temp = node;
        // promote the right child to the parent location
        node = node->getRight();
        delete temp;  // actual deletion
      }
      // if it has only left child
      else if (node->getRight() == NULL) {
        Node<KeyType, ValueType> *temp = node;
        // promote the left child to the parent location
        node = node->getLeft();
        delete temp;  // actual deletion
      }
      // if the node has 2 children
      else {
        // get the smallest value (get the inorder successor of the node) Smallest in the right subtree
        AVLNode<KeyType, ValueType> *temp = static_cast<AVLNode<KeyType,ValueType>*>(this->getMin(node->getRight()));
        swapNodes(node, temp);

        if (temp->getParent()->getRight() == temp)
          temp->getParent()->setRight(NULL);
        if (temp->getParent()->getLeft() == temp)
          temp->getParent()->setLeft(NULL);

        delete temp;
      }
    }
    // if the tree is empty after deletion, just return. No action is neccessary
    if (node == NULL)
      return node;

    // // update the height of the node's subtree
    node->setHeight(1 + std::max(height(node->getLeft()), height(node->getRight()) ));
    
    // // Rebalance tree if needed.
    return balanceTree(node, node->getKey());
  }
};

#endif