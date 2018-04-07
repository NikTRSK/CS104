- **Name**: Nikica Trajkovski
- **USC ID**: 1559186096
- **Email**: trajkovs@usc.edu

#Homework 8: Splay Trees, Hash Tables

#### Note: To keep the Data Structures more general I am converting to lowercase within the main program and not within the data structures.

###Problem 4: Splay Tree

###Problem 5: Hash Table
The hash table throws an out_of_range exception if the word limit is reached.

###Problem 6: Report
**Desciption**: Takes in the type of datastructure to use and  the input file and prints out each word followed by how many times it appears in the text. Finally it prints out the total runtime for all the add operations.
**Note**: This means it calculates the time before the reportAll runs, as I felt that the reporting was not indicative of the runtime.

*To compile*
Run `make`

*To run*
`./zipf option [4 | 5] input_file`


What large input cases did you use?
* I used Hamlet, The Time Machine, and Anna Karenina, all from http://www.textfiles.com/. For the once that were over the limit for the hash table I resized them before running the tests.

Which implementation ran faster? How much faster was it?
* The Splay Tree ran faster. It ran at most twice as fast. See results below, which are averages over 10 runs for each file:
* Hamlet
    - Splay Tree: 0.0210435
    - Hash Table: 0.0386171
* The Time Machine
    - Splay Tree: 0.0334198
    - Hash Table: 0.0684099
* Anna Karenina
    - Splay Tree: 0.0600526
    - Hash Table: 0.1356378

Another observation: The larger the input file, the bigger the difference between the Splay Tree and Hash Table, which was expected.

Why do you think that one was faster? Was it because of the chosen input or is there a guarantee made that affects this?
* The Splay Tree ran faster since the input was not random. Since the Enlish language (or any other language for that matter) has patterns (as outlined in the General Description), the most used data was kept on the top which allowed for quick access.
* On the other hand, the hashing function along with the resizing caused the Hash Table to run slower.

How do you think the running time would compare to the two if you were to implement your Map in the following fashions? Briefly justify each, although you do not need to quantify how much slower/faster with any specificity.
* **Unsorted List**: In an unsorted list (ex. Linked List) we would have O(1) add to front or back. However the update and find would be O(n) in the worst case. This would cause the unsorted list to run much slower. For example, if we add **the** fairly late in the process, we would have to do a lot of searches pretty often to find it, since it is the most common English word. In a splay tree the would be (pretty much) always near the top. 
* **Sorted list**: We would be able to perform binary search on it to quickly find and update the item but inserting is much more difficult. Depending on implementation but say using an array we would have to shift all the elements to insert the new element, which for a large input creates a lot of overhead (a lot of copying). Also there is the resizing issue which also creates a big overhead for a large input.
* **Binary search tree, non-rotating variety**: In the worst case the operations will actually take O(n) since we might have to look through all of the leaf nodes before we know if the item exists and if we need to update it or create a new one. On average we are looking at O(logn) runtime but this is still much slower than what a splay tree could give us for the particular types of inputs that were used, sice the data is not random.
* **Binary search tree with AVL balancing**: Due to the nature of AVLs we have a O(logn) guarantee for all operations. However, the constants are really large due to the complexity so it would still run slower than a splay tree. Additionally, since most of our most access data is on the top in the splay tree the splay tree would often outperform AVLs in the particular task. AVL and splay tree would be the closest as far as performance go. AVL should outperform for splay tree for a random input.


Final remarks: **SPLAY TREES ARE AWESOME**, Professor Cote was right.
