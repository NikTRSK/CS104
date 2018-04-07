- **Name**: Nikica Trajkovski
- **USC ID**: 1559186096
- **Email**: trajkovs@usc.edu

#Homework 7: Heaps, A*

###Problem 1: AVL Trees
The answers can be found https://github.com/usc-csci104-spring2016/hw_trajkovs/blob/master/hw7/AVLs.png (in the root directory).

###Problem 2: BST Iterators
Other than the standard iterators I also impelemented a find iterator

###Problem 3: AVL Trees

I added a **postPrint()** function to the BST class which does a post-order traversal.

I also added an **update()** function that updates the value of a given key.

####Exceptions:
* **insert()** throws an std::runtime_error for a duplicate key insertion with the appropriate mesage.
* **remove()** throws an std::runtime_error for a non-existing item with the appropriate mesage.
* **update()** throws an std::runtime_error for a non-existing item with the appropriate mesage.

###Problem 4: Exam Scheduling
I split up the scheduling functions into a separate file called scheduling.h

To compile:
`make`

Alternatively you can run:
g++ -g -Wall exam_scheduling.cpp bst.h avlbst.h scheduling.h -o exam_scheduling

To run:
`./exam_scheduling`