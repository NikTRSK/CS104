## CS 104: Spring 2016 Homework 3 Tests

Here you will find two Google Test files which were used to test problems 3 and 4 from Homework 3, as well as a folder containing tests for the arithmetic parser in problem 5.

Before raising a grading dispute, please copy these test files into your VM and run them against your program. In the event you would like to raise a grading dispute, create a new issue on GitHub by responding to the grade report you were issued. Assigning your grader to the issue and leave a comment explaining what you want regraded and what you believe the error is. 

### A Note on Google Tests:

If your code segfaults on one of the tests, any tests afterward will not be run. You can open the Google Test file and comment out that specific test, recompile, and rerun. This is how we tested your code. 

### Problem 3:
To run this test, you will need to compile the executable with your `LListInt` implementation. Please copy your `llistint.h` file into this directory. 

Since this problem was focused on the copy constructor, assignment operator, bracket accessor, and concatenation operator, we substituted implementations for `insert`, `remove`, and `getNodeAt` into your code. This meant we could test your code and focus on the above four functions.

These are produced below:

```cpp
/* 
 * Replace your struct with this Item struct, which has a constructor. 
 */
struct Item 
{
    Item(int aVal, Item *aNext, Item *aPrev) : val(aVal), prev(aPrev), next(aNext) { }
    int val;
    Item *prev;
    Item *next;
};
```

```cpp
/* 
 *This implementation will retreive either the head or the tail of the list in O(1).
 */
LListInt::Item *LListInt::getNodeAt(int loc) const
{
    if(loc < 0 || loc >= size_) { return NULL; }
    
    Item *temp;
    if(loc > size_ / 2)
    {
        temp = tail_;
        while(temp != NULL && loc != size_ - 1)
        {
            temp = temp->prev;
            ++loc;
        }
    }
    else
    {
        temp = head_;
        while(temp != NULL && loc != 0)
        {
            temp = temp->next;
            --loc;
        }
    }
    return temp;
}
```

```cpp
/*
 * remove function. 
 */
void LListInt::remove(int loc)
{
    if(loc < 0 || loc >= size_ || size_ == 0) { return; }

    if(size_ == 1)
    {
        delete head_;
        head_ = NULL;
        tail_ = NULL;
    }
    else if(loc == 0)
    {
        head_ = head_->next;
        delete head_->prev;
        head_->prev = NULL;
    }
    else if(loc == size_ - 1)
    {
        tail_ = tail_->prev;
        delete tail_->next;
        tail_->next = NULL;
    }
    else
    {
        Item *temp = getNodeAt(loc);
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        delete temp;
    }
    --size_;
}
```

```cpp
/*
 * insert function
 */
void LListInt::insert(int loc, const int& val)
{
    if(loc < 0 || loc > size_) { return; }

    if(head_ == NULL)
    {
        head_ = new Item(val, NULL, NULL);
        tail_ = head_;
    }
    else if(loc == 0)
    {
        head_->prev = new Item(val, head_, NULL);
        head_ = head_->prev;
    }
    else if(loc == size_)
    {
        tail_->next = new Item(val, NULL, tail_);
        tail_ = tail_->next;
    }
    else
    {
        Item *temp = getNodeAt(loc);
        Item *newItem = new Item(val, temp, temp->prev);
        newItem->prev->next = newItem;
        temp->prev = newItem;
    }
    ++size_;
}
```

Use the usual Google Test compile process, and then run the test:

```bash
g++ -g -Wall gtest_llistint.cpp your_llistint.cpp -I /usr/local/opt/include/gtest -l gtest -l gtest_main -pthread -o gtest_llistint
```

### Problem 4:
To run this test, you will need to compile the executable with your `LListInt` and `StackInt` implementations. Please copy your `llistint.h` and `stackint.h` files into this directory. 

Many of the tests are intended to check the runtime of your `StackInt` class. To see if your implementation runs in `O(1)`, you can examine the time for each of the tests. Since the input increases by a factor of 10, all of the runtime tests shoudl *roughly* increase by a factor of 10.

Use the usual Google Test compile process, and then run the test:

```bash
g++ -g -Wall gtest_llistint.cpp your_llistint.cpp your_stackint.cpp -I /usr/local/opt/include/gtest -l gtest -l gtest_main -pthread -o gtest_stackint
```
### Problem 5:
The tests for this problem are located in the `arithexpr` folder. Each of the tests has a `.in` file for input and a corresponding solution `.out` file. To check your program, run it with the given input and check it against the output. 