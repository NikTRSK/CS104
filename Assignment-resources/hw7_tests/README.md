## CS 104: Spring 2016 Homework 7 Tests

Here you will find a Google Test for your BST, AVL Tree, as well as an executable to check your exam scheduling program. 

Before raising a grading dispute, please copy these test files into your VM and run them against your program. In the event you would like to raise a grading dispute, create a new issue on GitHub by responding to the grade report you were issued. Assigning your grader to the issue and leave a comment explaining what you want regraded and what you believe the error is. 

### Modifying Your BST Code
In order to test your code, we had to make a few modifications and expose/create new public methods. Please make the following changes to your BST:

Copy the following method into the public section of the `iterator` class:

```.cpp
// To be added into the public section of the iterator class. Needed for reassigning iterators. 
iterator &operator=(const iterator &rhs)
{
	this->_current = rhs._current;
	return *this;
}
```

Also, copy the following three methods into the public section of the `BinarySearchTree` class. **NOTE:** the `_root` variable in the first `if` statement in the `insertHelper` method may need to be changed to the name of the root variable you use in case you changed it.

```.cpp
// To be added into the public section of the BinarySearchTree class
void insert(const std::pair<KeyType, ValueType> &keyValuePair)
{
	insertHelper(keyValuePair, _root);
}
```

```.cpp
// To be added into the public section of the BinarySearchTree class
void insertHelper(const std::pair<KeyType, ValueType> &keyValuePair, Node<KeyType, ValueType> *root)
{
	if(root == NULL)
	{
		// This _root variable will need to change if student's have renamed their variable!!
		_root = new Node<KeyType, ValueType>(keyValuePair.first, keyValuePair.second, NULL);
	}
	else if(root->getKey() < keyValuePair.first)
	{
		if(root->getRight() != NULL)
		{
			insertHelper(keyValuePair, root->getRight());
		}
		else
		{
			root->setRight(new Node<KeyType, ValueType>(keyValuePair.first, keyValuePair.second, root));
		}
	}
	else if(root->getKey() > keyValuePair.first)
	{
		if(root->getLeft() != NULL)
		{
			insertHelper(keyValuePair, root->getLeft());
		}
		else
		{
			root->setLeft(new Node<KeyType, ValueType>(keyValuePair.first, keyValuePair.second, root));
		}
	}
	else
	{
		root->setValue(keyValuePair.second);
	}
}
```

```.cpp
// To be into the public section of the BinarySearchTree class
iterator find(const KeyType& k) const 
{
	Node<KeyType, ValueType>* curr = internalFind(k);
	iterator it(curr);
	return it;
}
```

### Running the BST Google Tests
The Google Test is in [bst_gtest.cpp](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/bst_gtest.cpp). To get it running, make the following changes:

+ Change line 6 to include your header file. 

Run the tests by compiling with all the necessary Google Test flags, as usual.

### Modifying Your AVL Tree Code
In the event you did not correctly implement the iterator for the BST, please paste the following code into your `operator++()` since we use the iterator to traverse the AVL tree.

```.cpp
{
	if(curr->getRight() != NULL)
	{
		curr = curr->getRight();

		while(curr->getLeft() != NULL)
		{
			curr = curr->getLeft();
		}
	}
	else if(curr->getRight() == NULL)
	{
		Node<KeyType, ValueType> *parent = curr->getParent();

		while(parent != NULL && curr == parent->getRight())
		{
			curr = parent;
			parent = parent->getParent();
		}

		curr = parent;
	}

	return *this;
}
```

### Running the AVL Tree Google Tests
The Google Test is in [avl_gtest.cpp](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/avl_gtest.cpp). To get it running, make the following changes:

+ Change line 7 to include your header file. 

Run the tests by compiling with all the necessary Google Test flags, as usual.

### Running the Exam Checker Tests
There are several tests provided in the `scheduling_tests/` directory within this repo. 

You will use the [exam_checker](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/exam_checker) executable to see if your code outputs a correct solution to a problem. To do this, run your exam scheduling executable for each of the inputs and redirect the output to a file. Then run the `exam_checker` executable as follows:

```
./exam_checker input_file your_solution_output
```

The following chart shows whether or not a solution exists for the tests:

| Test | Description | Valid Assignment? |
|:-:|---|:-:|
| [test1.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test1.in) | A single student with a single exam and a single time slot. | Yes |
| [test2.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test2.in) | Two students with a single exam and a single time slot. | Yes |
| [test3.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test3.in) | A single student with two exams and two time slots. | Yes | 
| [test4.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test4.in) | Two students with two exams and two time slots. | Yes | 
| [test5.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test5.in) | A single student with two exams and one time slot. | No | 
| [test6.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test6.in) | 10 students with three exams and two time slots. | Yes |
| [test7.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test7.in) | 10 students with three exams and two time slots. | No |
| [test8.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test8.in) | 10 students with 4 exams and 3 time slots. | Yes |
| [test9.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test9.in) | 5 students with 10 exams and 5 time slots. | Yes | 
| [test10.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test10.in) | 5 students with 10 exams and 5 time slots. | Yes |
| [test11.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test11.in) | 20 students with 10 classes and 4 time slots. | Yes |
| [test12.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test12.in) | 20 students with 10 classes and 3 times slots. | No |
| [test13.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test13.in) | 5 students, 4 exams, and 2 time slots | Yes |
| [test14.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test14.in) | 5 students, 4 exams, and 2 time slots | No |
| [test15.in](https://github.com/usc-csci104-spring2016/homework-resources/tree/master/hw7_tests/scheduling_tests/test15.in) | 34 students, 15 exams, and 9 time slots. This is a stress test, but should still run in a reasonable amount of time. | Yes |