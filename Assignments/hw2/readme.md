- **Name**: Nikica Trajkovski
- **USC ID**: 1559186096
- **Email**: trajkovs@usc.edu

**NOTE:** I have included my answers to **Questions 1-5** in the file **hw2.md** (instead of hw2.txt).

#Homework 2

###Problem 1: GIT
The answers are found in the **hw2.md** file.

###Problem 2: Review
Nothing to submit.

###Problem 3: Runtime analysis
The answers are found in the **hw2.md** file.

###Problem 4: Abstract Data Types
The answer is found in the **hw2.md** file.

###Problem 5: Linked Lists, Recursion
The answers are found in the **hw2.md** file.

###Problem 6: Linked Lists, Recursion
**First add main function to the `hw2p6_merge.cpp` file.**
* **NOTE:** You have to add the includes and a main function in the file. Currently the file only has the merge function and nothing else.

To compile:
`make merge`
* This will generate an executable `hw2p6_merge`
* Alternatively, you can compile the file manually:
    - `g++ -g -Wall hw2p6_merge.cpp -o hw2p6_merge.cpp`

To run:
`./hw2p6_merge`

###Problem 7: Linked List
To compile:
`make`
* This will compile both the supplied test file and my own rendition of the test file
* Alternatively, you can compile the files manually:
    - `g++ -g -Wall llistint.h llistint.cpp testAddToEmptyList.cpp -o testAddToEmptyList`
    - `g++ -g -Wall llistint.h llistint.cpp llisttest.cpp -o llisttest`

To run:
* The supplied file: `./testAddToEmptyList`
* My test file: `./llisttest`

#### NOTE: Calling get() or set() with an invalid location (index) will raise an exception and will cause the execution to terminate. Accordingly, I have designed the getNodeAt() function to throw an exception for an invalid location. Additionally, if the program were to be ran and the above 2 functions called with the invalid parameters and valgrinded, it would natually cause memory leaks since it never gets to dealocate memory. Since the get() and set() functions were prebuilt, I couldn't handle the exeption in any other way.
In normal execution the program runs without any issues or leaks.