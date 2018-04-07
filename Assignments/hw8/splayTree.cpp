#include "splayTree.h"
 
splayTree::splayTree() {}
splayTree::~splayTree() {}

void splayTree::add(const std::string& word) {
  this->root = insertNode(this->root, word);
}

void splayTree::reportAll(std::ostream& output) {
  inOrderHelper(this->root, output);
}

Node<std::string, int>* splayTree::insertNode(Node<std::string, int>* node, const std::string& word) {
    // if empty tree, insert at root
    if (node == NULL) {

      Node<std::string, int>* newNode = new Node<std::string, int>(word, 1, NULL);
      return newNode;
    }
 
    // splay the node (if the key exists to the top)
    node = splay(node, word);
 
    // if the word already exists, increment the count. After splay it will be the top item
    if (node->getKey() == word) { 
      node->setValue(node->getValue()+1);
      return node;
    }
 
    // create a new node. And add it to the top.
    Node<std::string, int>* newNode = new Node<std::string, int>(word, 1, NULL);
 
    // make node right child if the new item is smaller than the node
    if (node->getKey() > word)
    {
        newNode->setRight(node);
        
        if (node->getLeft() != NULL)
          node->getLeft()->setParent(newNode);

        newNode->setLeft(node->getLeft());
        node->setLeft(NULL);
        node->setParent(newNode);
    }
 
    // make node left child if the new item is greater than the node
    else
    {
        newNode->setLeft(node);

        if (node->getRight() != NULL)
          node->getRight()->setParent(newNode);

        newNode->setRight(node->getRight());
        node->setRight(NULL);
        node->setParent(newNode);
    }
 
    return newNode;
}

Node<std::string, int>* splayTree::splay(Node<std::string, int>* node, const std::string& toAdd) {
  // Case 1: Node is the root
  if (node == NULL || node->getKey() == toAdd)
    return node;

  // Left cases
  if (node->getKey() > toAdd) {
    // howhere to go. Return
    if (node->getLeft() == NULL)
      return node;

    // Zig-Zig
    if (node->getLeft()->getKey() > toAdd) {
      // Make the splayed item node's left grandchild
      node->getLeft()->setLeft(splay(node->getLeft()->getLeft(), toAdd));
      // Perform right for the Zig.
      node = rightRotation(node);
    }
    // Zig-Zag
    else if (node->getLeft()->getKey() < toAdd) {
      // Make the splayed item node's left-right grandchild
      node->getLeft()->setRight(splay(node->getLeft()->getRight(), toAdd));

      // Take care of the diamond shape.
      if (node->getLeft()->getRight() != NULL)
        node->setLeft(leftRotation(node->getLeft()));
    }

    // Perform the second rotation
    if (node->getLeft() == NULL)
      return node;
    else
      return rightRotation(node);
  }
  // Right cases
  else {
    // howhere to go. Return
    if (node->getRight() == NULL) return node;

    // Zag-Zag
    if (node->getRight()->getKey() < toAdd) {
      // Make the splayed item node's right grandchild
      node->getRight()->setRight(splay(node->getRight()->getRight(), toAdd));
      // Perform rotation to get rid of the Zag
      node = leftRotation(node);
    }

    // Zag-Zig
    else if (node->getRight()->getKey() > toAdd) {
      // Make the splayed item right-left grandchild
      node->getRight()->setLeft(splay(node->getRight()->getLeft(), toAdd));

      // Take care of the diamond shape
      if (node->getRight()->getLeft() != NULL)
        node->setRight(rightRotation(node->getRight()));
    }

    // Perform the second rotation
    if (node->getRight() == NULL)
      return node;
    else
      return leftRotation(node);
  }
}

  /*       z         ZAG Rotation      y
   *      / \                         / \
   *     T0  y                       z  T2
   *        / \                     / \
   *       T1 T2                   T0 T1
   */
  Node<std::string, int>* splayTree::leftRotation(Node<std::string, int>* z) {
    // temp pointers for rotation
    Node<std::string, int> *y = z->getRight();
    Node<std::string, int> *T1 = y->getLeft();

    y->setLeft(z);
    z->setRight(T1);
    // parent z to y
    if (y != NULL)
      z->setParent(y);
    // parent T1 and z
    if (T1 != NULL)
      T1->setParent(z);

    // y is the new root of the subtree
    return y;
  }

  /*       z         ZIG Rotation      y
   *      / \                         / \
   *     y  T2                       T0  z
   *    / \                             / \
   *  T0  T1                           T1 T2
   */
  Node<std::string, int>* splayTree::rightRotation(Node<std::string, int>* z) {
    // temp pointers for rotation
    Node<std::string, int> *y = z->getLeft();
    Node<std::string, int> *T1 = y->getRight();

    y->setRight(z);
    z->setLeft(T1);
    // parent z to y
    if (y != NULL)
      z->setParent(y);
    // parent T1 to z
    if (T1 != NULL)
      T1->setParent(z);

    // y is the new root of the subtree
    return y;
  }

  void splayTree::inOrderHelper(Node<std::string, int> *r, std::ostream& output) const {
    if (r != NULL) {
      inOrderHelper (r->getLeft(), output);
      output << r->getKey() << " " << r->getValue() << "\n";
      inOrderHelper (r->getRight(), output);
    }
  }