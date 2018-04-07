- **Name**: Nikica Trajkovski
- **USC ID**: 1559186096
- **Email**: trajkovs@usc.edu

#Homework 6: Heaps, A*

###Problem 2: Heaps and Heap Operations
The problem can be found in the **hw6.md** file


###Problem 3: Create a d-ary Heap
####Exceptions:
* The **constructor** throws an out_of_range exception for a value of the tree <2.
* The **peek()** function throws an out_of_range("Heap empty") exception if the heap is empty.

I also added a **printLevel** function that prints a given level and a **printTree** function that uses postorder traversal to generate a vertical tree.
I found these functions quite useful when testing.

###Problem 4: A-MAZE-ing Problem Solver

To compile:
`qmake`
`make`

To run:
`./Maze`

**FEW NOTES**
Due to the implementation of the MinHeap (most likely different tie breakers) the paths between A* and BFS may vary ever so slightly (as per numerous discussions on Piazza).