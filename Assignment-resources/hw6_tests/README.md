## CS 104: Spring 2016 Homework 6 Tests

Here you will find a Google Test for your heap implementation, as well as a series of instructions for checking your maze solver. 

Before raising a grading dispute, please copy these test files into your VM and run them against your program. In the event you would like to raise a grading dispute, create a new issue on GitHub by responding to the grade report you were issued. Assigning your grader to the issue and leave a comment explaining what you want regraded and what you believe the error is. 

### Running the Google Test
The Google Test is in [heap_gtest.cpp](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw6_tests/heap_gtest.cpp). 

The following may need to be updated to test your particular implementation:
+ Line [10](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw6_tests/heap_gtest.cpp#L10) needs to be changed to include your own heap implementation.
+ Line [12](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw6_tests/heap_gtest.cpp#L12) contains a `define` statement which is used to activate our random d-ary tests. When this is set to `1`, your heap will be constructed with a random d-ary value for each test. All of the tests run the same with this change. You should run your program with both options `0` and `1`.
+ Line [13](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw6_tests/heap_gtest.cpp#L13) contains a `define` statement to toggle the large tests. Change this to `0` if you find your implementation takes too long to run (if, for example, your runtime is not correct, then inserting 1,000,000 elements will take a very long time).

Run the tests by compiling with all the necessary Google Test flags, as usual.

### Running the Maze Solver Tests

These are the instructions for running the tests for your maze program. You will need to modify your code to output information, and those instructions follow below. In order to test the effectiveness of your A* solver, we constructed an acceptable range of values for the number of explored nodes and path length. When deciding the values for ranges, we considered the numerous ways that ties could be broken in your heap implementation, took the maximum of those values, and then added a percentage buffer. The ranges are therefore **not negotiable**.

+ In `kruskalishmaze.cpp`, in the `createMaze()` method starting on line `49`, change the call to `srand` so the seed is `57821`. This ensures all students will receive the same mazes.
+ In `mazesolver.cpp`, we need a way to check the length of the student's paths. To do this you will add some code to print out to a file (alternatively, you can print the information to the console, but students may be printing debug information, in which case a file might be easier to understand. It's up to you.):

```.cpp
// Should be added to solveByDFSRecursive() after their call
// to display->reportSolution()
std::ofstream outputFile;
outputFile.open("problem4_results.txt", std::ios_base::app);
if(outputFile)
{
	outputFile << "DFS Recursive Path Length: " << path.size() << std::endl;
	outputFile << "DFS Recursive Visited: " << vt.numVisited() << std::endl;
}
outputFile.close();
```

```.cpp
// Should be added to solveByAStar() after their call
// to display->reportSolution()
std::ofstream outputFile;
outputFile.open("problem4_results.txt", std::ios_base::app);
if(outputFile)
{
	outputFile << "A* " << choice << " Path Length: " << path.size() << std::endl;
	outputFile << "A* " << choice << " Visited: " << vt.numVisited() << std::endl;
	if(choice == 3)
	{
		outputFile << std::endl << std::endl << std::endl;
	}
}
outputFile.close();
```

You will likely have to `#include <fstream>` at the top of `mazesolver.cpp` as well.

### Running the Tests:
Now that the code has been modified, the tests can be run.

Compile your code with `qmake` and `make` at the command line. Run your executable with `./Maze`, and do the following:

1. Choose the `small` option for maze size and generate the small maze.
1. Choose the `DFS Recursive` option, and solve the maze.
1. Choose the `A* 1` option, and solve the maze.
1. Choose the `A* 2` option, and solve the maze.
1. Choose the `A* 3` option, and solve the maze.

Once this is done, the output file (or the terminal window) will contain the inforamtion about the path length as well as the number of explored nodes. Repeat the above steps for a total of 8 mazes, in the following order:

1. Small
1. Small (simple)
1. Medium
1. Medium (simple)
1. Large
1. Large (simple)
1. Huge
1. Huge (simple)

In the end, there will be 8 different mazes, each with 4 searches run. Once the results are generated, examine the output file (or the terminal window) and check the following allowable ranges (**Note:** DFS Recursive has no length/explored requirements). The **bold** values are for full credit, and the *italic* values are for half credit. Half credit is given for a 5% tolerance:

| Maze Size/Type | Optimal Length | Number of Explored: A* 1 | Number of Explored: A* 2 | Number of Explored: A* 3 |
|:-:|:-:|---|---|---|
| Small | **20** (*<= 21*) | **92-100** (*87-105*) | **43-61** (*40-64*) | **54-73** (*51-76*) |
| Small (simple) | **20** (*<= 21*) | **81-95** (*77-99*) | **44-59** (*41-62*) | **54-70** (*51-73*) |
| Medium | **48** (*<= 50*) | **396-400** (*376-420*) | **231-302** (*218-315*) | **282-331** (*267-346*) |
| Medium (simple) | **64** (*<= 67*) | **394-397** (*374-417*) | **296-347** (*280-363*) | **340-357** (*323-374*) |
| Large | **158** (*<= 166*) | **2401-2416** (*2281-2536*) | **1547-1651** (*1467-1731*) | **1880-1981** (*1784-2077*) |
| Large (simple) | **316** (*<= 332*) | **2355-2367** (*2237-2485*) | **2207-2230** (*2096-2341*) | **2259-2275** (*2146-2388*) |
| Huge | **184** (*<= 193*) | **5605-5617** (*5324-5898*) | **3435-3723** (*3256-3902*) | **4242-4344** (*4027-4559*) |
| Huge (simple) | **250** (*<= 263*) | **5407-5455** (*5135-5727*) | **3862-3998** (*3665-4195*) | **4180-4263** (*3969-4474*) |