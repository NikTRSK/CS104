## CS 104: Spring 2016 Homework 8 Tests

Here you will find two test files for running tests for the Splay Tree and the Hash Table. 

Before raising a grading dispute, please copy these test files into your VM and run them against your program. In the event you would like to raise a grading dispute, create a new issue on GitHub by responding to the grade report you were issued. Assigning your grader to the issue and leave a comment explaining what you want regraded and what you believe the error is. 

### Running the Splay Tree Tests

To run the Splay Tree tests, use the provided makefile in this directory to compile you code with the tests. There are tests in the `splay_tests/` folder which need to be run. There are two ways to run the tests, and they are done in the following ways:

```
./splaytest input_file splay_output verify_output
```

```
./splaytest seed num_words splay_output verify_output
```

The first way will read in an `input_file` and generate two output files: `splay_output` will contain your output when using the `reportAll()` method, and the `verify_output` file will contain the solution output. You need to then compare the two files to make sure they match. You can do this with a `diff` command at the command line. 

The second way will insert random words into your splay tree. Run this option with the following input:

| Seed | Number of Words |
|:-:|:-:|
| 57821 | 10 |
| 57821 | 100 |
| 57821 | 1000 |
| 57821 | 10000 |
| 57821 | 100000 |

This will insert increasing orders of magnitude. You have to check the output again.

### Running the Hash Table Tests

To run the Hash Table tests, you have to use the provided makefile to compile the code. There is a compiled binary file `hashtable_sol.o` that will be compiled into the test, and your output will be checked against that solution. Just as with the Splay Tree tests, you need to run the tests in two different ways:

```
./hashtest input_file splay_output verify_output
```

```
./hashtest seed num_words splay_output verify_output
```

Again, the tests are in the `hash_tests/` directory, and those need to be run and checked manually.

For the random tests, we checked the same input as above, except for the last test:

| Seed | Number of Words |
|:-:|:-:|
| 57821 | 10 |
| 57821 | 100 |
| 57821 | 1000 |
| 57821 | 10000 |

