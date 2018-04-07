## CS 104: Spring 2016 Homework 2 Tests

Here you will find two Google Test files which were used to test problems 6 and 7 from Homework 2.

Before raising a grading dispute, please copy these test files into your VM and run them against your program. In the event you would like to raise a grading dispute, create a new issue on GitHub by responding to the grade report you were issued. Assigning your grader to the issue and leave a comment explaining what you want regraded and what you believe the error is. 

### A Note on Google Tests:

If your code segfaults on one of the tests, any tests afterward will not be run. You can open the Google Test file and comment out that specific test, recompile, and rerun. This is how we tested your code. 

### Problem 6:

To run this test, you will need to copy and paste your implementation of `merge` into the test file. You can do this on line [24](https://github.com/usc-csci104-spring2016/homework-resources/blob/master/hw2_tests/gtest_llistint_recursive_merge.cpp#L24).

Use the usual Google Test compile process, and then run the test:

```
g++ -g -Wall gtest_llistint_recursive_merge.cpp -I /usr/local/opt/include/gtest -l gtest -l gtest_main -pthread -o gtest_recursive
```

### Problem 7:

To run this test, you will need to compile the executable with your `LListInt` implementation. A header file for the `LListInt` class is also provided in this directory, so you will not need to change any of the `#include` statements in the test file. 

Use the usual Google Test compile process, and then run the test:

```
g++ -g -Wall gtest_llistint.cpp your_llistint.cpp -I /usr/local/opt/include/gtest -l gtest -l gtest_main -pthread -o gtest_llistint
```