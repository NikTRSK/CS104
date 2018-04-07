- **Name**: Nikica Trajkovski
- **USC ID**: 1559186096
- **Email**: trajkovs@usc.edu

**NOTE:** I have included my answers to **Questions 2** in the file **hw3.md** (instead of hw3.txt).

#Homework 3

###Problem 1:
Nothing to submit.

###Problem 2: Amortized Analysis
The answers are found in the **hw2.md** file.

###Problem 3: Copy Constructors and Operator Overloading
To compile:
`make llisttest`
* This will compile the library and the unit test
To run:
`./llisttest`
* You can compile and run with `make run_llisttest`
* You can compile, run, and valgrind the file and test with `make grind_llisttest`

#### NOTE: As previously calling get() or set() with an invalid location (index) will raise an exception and will cause the execution to terminate. Accordingly, I have designed the getNodeAt() function to throw an exception for an invalid location. Additionally, if the program were to be ran and the above 2 functions called with the invalid parameters and valgrinded, it would natually cause memory leaks since it never gets to dealocate memory. Since the get() and set() functions were prebuilt, I couldn't handle the exeption in any other way.
#### Likewise, [] operator behaves similarly like the get() function, since get() will raise an exception for out of range locations.
In normal execution the program runs without any issues or leaks.

###Problem 4: Stacks
The stack just calls functions from the Linked List. It inserts, accesses and deletes the first item always, making the runtime O(1).

To compile:
Either compile with g++ (`g++ -Wall -g stackint.h stackint.cpp [test_file] -o [output_filename]`) or edit the makefile (if using GTests). The stack files are `stackint.h` and `stackint.cpp`.

###Problem 5: Simple Arithmetic Parser and Evaluator
Examples of valid statements and the expected result (shows in the comment):
* 10 // 10
* <<10 // 40
* (<<14 *(>>123+333 )) // 20328
* <>(2 * 1* ( >500000000 + <<0)) // 500000000
* <>(1 * >3 * 3) // 2
* (5) // 5
* (12+(34*123)) // 4194
* ( >235 ) // 117
* <( 235 ) // 470
* ((30+<40+20)) // 130
* ((30+<40+20)+10) // 140
* ((30+<50+(<<<<123*256)+214)) // 504152
* ( (30+<50+ (<123*256) +214) *255) // 16146600

Examples of invalid statements that will cause 'Malformed' to be outputed.
* (522> + 20)
* (>>21  + <<(254>> + 212 * (212*2)))
* ((<123*234)
* (1337*9001+42)
* (*1138*3720)
* (12+34*123)
* ()
* (30<+50)
* (30< 50)
* (5 + 10 ())
* (>>21  + <<(254>> + 212 * (212*2)))
* (>>21  + <<(+))
* (<<2542 +*20)
* ( (30+<50+ (<123*256) +214) *255 +)

To compile:
`make parser`
* the .cpp file is `hw3p5_arith.cpp`

To run:
`./parser input_filename`