- **Name**: Nikica Trajkovski
- **USC ID**: 1559186096
- **Email**: trajkovs@usc.edu

#Homework 5: Project Part 2: QT

###Problem 1: UML
The problem can be found in the **hw5.md** file

**All of the .cpp files are under the */src* dir and all of the .h files are under the */lib* dir. There is also an */img* dir that countaines all the image files for P1 and P4**

###Problem 3: Implement Merge Sort
To compile:
Since the project requires only for a .pro file to be submitted the compilation for the msort_test is done manually.
`g++ -Wall -g -std=c++11 ./src/msort_test.cpp ./lib/msort.h -o msort_test`
- c++11 is only used for the initialized list in the vector 

To run:
`./msort_test`


###Problem 4: QT

To compile:
`qmake`
`make`

To run:
`./debugger`

**FEW NOTES**
- I changed a few of the internal facile functions since I was experiencing strange behaviour with the math operations while using QT/C++11.
- The name of the program is inspired by Professor Cote and all his awesome puns/jokes.
- Clearly there are memory leaks. I cleaned up everything that I assigned but valgrind still blows up with leaks.

####NOTES ON PROGRAM BEHAVIOR
**Load Window**
- There are two error messages for file input
    + No filename entered
    + Error loading/wrong filename

**Debugger Window**
Behaves very similarly to GDB
- The user has to press **Run** before any of the navigation buttons can be used.
- **Breakpoint** works at any point in time.
- Once the program execution finishes the user will see a message notification (via a QLabel) about the event. Then the user can press the **Run** button to restart the program.

**Inspect Values Window**
- The user can see the values of the variables currently in use.
- Default sorting is Name (Ascending)
- If the window is open the values are shown/updated only once the **Update Values** button is pressed.
- If the program is not running there are no values to be shown.

**An EXCEPTION** terminates the program immidiately and shows the appropriate error message.
