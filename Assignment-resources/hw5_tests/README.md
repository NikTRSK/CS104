## CS 104: Spring 2016 Homework 5 Tests

Here you will find a Google Test for your mergesort algorithm, as well as a series of instructions for checking your GUI elements. 

Before raising a grading dispute, please copy these test files into your VM and run them against your program. In the event you would like to raise a grading dispute, create a new issue on GitHub by responding to the grade report you were issued. Assigning your grader to the issue and leave a comment explaining what you want regraded and what you believe the error is. 

### Running the Google Test
The Google Test is in [gtest_mergesort.cpp](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw5_tests/gtest_mergesort.cpp). 

The following may need to be updated to test your particular implementation:
+ Starting on line [8](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw5_tests/gtest_mergesort.cpp#L8) there are three `define` statements. Right now, the `vector` option is set to `1`. If you used either a `list` or a `deque` to implement mergesort, you have to change the `define` statement to `1` for that option. Only one of the three options should ever be set to `1`.
+ You need to `include` your implementation on line [29](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw5_tests/gtest_mergesort.cpp#L29).
+ On line [33](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw5_tests/gtest_mergesort.cpp#L33), there is another `define` macro. We expected your function to be called `mergeSort`, but if you changed the interface, you need to change the name of your function here. As long as you kept the name, though, you don't have to do anything here. 

Run the tests by compiling with all the necessary Google Test flags, as usual.

### Running the GUI Tests:
In order to test your GUI implementation, we created a set of instructions to run on everyone's program. There are also several Facile programs included in this directory that are used in our tests. Each window is broken down into two components: The actual GUI, and then the functionality that window is supposed to support. The final tests are comprehensive with several instructions for each program. 

Below you will find the set of instructions. You should compile your executable and run it. We ignored all console output when running your program.

#### Load Window GUI:

| Number | Description |
|:-:|---|
|1. | The Load Window should be the first and only window that shows when you run their executable. |
|2. | The Load Window has a text entry box for entering the file name. |
|3. | The Load Window has a button to quit the program. |
|4. | The Load Window has a button to load the chosen file. |
|5. | The Load Window GUI is arranged in an appealing layout. |

#### Load Window Functionality:

| Number | Description |
|:-:|---|
|1. | When the "quit" button is pressed from the Load Window, the program should quit without any errors. |
|2. | When the "load" button is pressed from the Load Window and the text field is empty, either a suitable error message should appear, or no action should be taken. |
|3. | When the "load" button is pressed with an invalid file name (insert some random text into the field), a suitable error message should appear. |
|4. | When the "load" button is pressed with a valid `Facile` file name, the Load Window should close and the Debugger window should appear. |
|5. | When the "enter/return" key is pressed with the cursor in the text field (with either a valid file or an invalid file) the program should respond accordingly. | 

#### Debugger Window GUI:

| Number | Description |
|:-:|---|
|1. | The Debugger Window has a scrolling box to view the `Facile` program, and the lines can be selected. |
|2. | The Debugger Window has a breakpoint button. |
|3. | The Debugger Window has a continue button. |
|4. | The Debugger Window has a next button. |
|5. | The Debugger Window has a step button. |
|6. | The Debugger Window has an inspect button. |
|7. | The Debugger Window has a quit button. |
|8. | The Debugger Window GUI is arranged in an appealing layout. |

#### Debugger Window Functionality:

| Number | Description |
|:-:|---|
|1. | When the quit button is pressed from the Debugger Window, the program terminates without any errors. |
|2. | When the inspect button is pressed, the Values Window opens (just verify it opens).
|3. | When a line from the `Facile` program is selected and the breakpoint button is pressed, a visual cue should indicate the selected line has a breakpoint. |
|4. | When a line from the `Facile` program is selected and it already has a breakpoint enabled, if the breakpoint button is pressed the visual cue should go away. |
|5. | Run the program with `facile_test2.txt`. When the continue button is pressed, the program should not crash (there is no required output, just make sure the program is stable).
|6. | Run the program with `facile_test2.txt`. Set a breakpoint on the `PRINTALL` line. When the continue button is pressed, there should be a visual cue to show the program halted on the line. |
|7. | Run the program with `facile_test2.txt`. Set a breakpoint on the declaration of `SAM` and press continue. The program should halt on the second line. When the next button is pressed, a visual cue should indicate execution is on the `PRINTALL` line. |
|8. | Repeat the previous test, but use the step button to advance to the `PRINTALL` line. |
|9. | Run the program with `facile_test3.txt`. Set a breakpoint on lines 2 and 4. Press continue, and check the program halts on line 2. Press continue again and check the program halts on line 4. |
|10. | Run the program with `facile_test20.txt`. Set a breakpoint on the `GOTO` line and press continue. Use either step or next to advance the program by one line. The program should halt on line 4 with a visual indication. |
|11. | Run the program with `facile_test22.txt`. Set a breakpoint on the `GOSUB` line and press continue. Press the step button and check the program halts on line 8. |
|12. | Run the program with `facile_test22.txt`. Set a breakpoint on the `GOSUB` line and press continue. Press the next button and check the program halts on line 4. The entire subroutine should run. |
|13. | Run the program with `facile_test36.txt`. Set a breakpoint on the `IF` statement and press continue. Press any of the execution buttons (step, next, or continue), and an error message should appear indicating an invalid jump. |
|14. | Run the program with `facile_test39.txt`. Set a breakpoint on line 2 and press continue so the program halts on line 2. Press any of the execution buttons (step, next, or continue), and an error message should appear indicating a divide by zero error. |
|15. | Run the program with `facile_test44.txt`. Set a breakpoint on line 2. Press continue and check execution halts on line 2. Press continue again to run the rest of the program. If breakpoints are cleared, set a breakpoint on line 2 (do not deduct points if breakpoints don't persist). Press continue. Check the program halts on line 2. The program should be able to execute multiple times. |

#### Values Window GUI:

| Number | Description |
|:-:|---|
|1. | The Values Window should have a scrolling box to display all of the variable values. |
|2. | The Values Window has a hide button. |
|3. | The Values Window has an update button. |
|4. | The Values Window has a way to choose between the 4 sorting options (variable name ascending/descending, and variable value ascending/descending). Only one should be selectable at a time. |
|5. | The Values Window GUI is arranged in an appealing layout. |

#### Values Window Functionality:

| Number | Description |
|:-:|---|
|1. | When the hide button is pressed the Values Window closes. |
|2. | When the Values Window first opens, the sorting option defaults to variable name (either ascending or descending). |
|3. | Run the program with `facile_test2.txt` and put a breakpoint on line 2. Run the program with continue, and open the Values Window. Press the update button and check that the variable `FRODO` has a value of 4. Press either step or next, and return to the Values Window. Press the update button and check the variable `SAM` has a value of 10. Both `FRODO` and `SAM` should be in the display window. |
|4. | Run the program with `facile_test2.txt` and put a breakpoint on line 3. Run the program with continue, and open the Values Window. Verify that all of the sorting options work to reorganize the variables (use update after picking the option to resort the variables).
|5. | Run the program with `facile_test2.txt` and put a breakpoint on line 3. Run the program with continue, and open the Values Window. Then continue the program until it terminates (If the Values Window closes on program termination, reopen it. Do not deduct points for this behavior). Rerun the program until it halts on line 3. Press update in the Values Window to check the variables `FRODO` and `SAM` are only shown once (they should not be duplicated). |

#### Full Tests:

| Number | Description |
|:-:|---|
|1. | Run the program with `facile_test48.txt`. Spend about a minute setting breakpoints, running the program with various step, continue, and next commands, and inspect the variable values along the way. In particular, this program makes use of subroutines to calculate Fibonacci numbers. |
|2. | Run the program with `facile_test49.txt`. Spend about a minute setting breakpoints, running the program with various step, continue, and next commands, and inspect the variable values along the way. In particular, this program calculates powers of 2 with `IF` statements and `GOTO` statements for program control. |
|3. | Run the program with `facile_test50.txt`. Spend about a minute setting breakpoints, running the program with various step, continue, and next commands, and inspect the variable values along the way. This is a large program (1000 lines) and there are various arithmetic statements. |