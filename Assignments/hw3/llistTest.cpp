#include "llistint.h"
#include "gtest/gtest.h"

class LinkedListTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	LinkedListTest() {
		// You can do set-up work for each test here.
	}

	virtual ~LinkedListTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).

    // fill out list
		for(int i = 0; i < 25; i++)
      list.insert(i, i);
    // fill out small
    for(int i = 0; i < 10; i++)
      small.insert(i, 100 + i);
    // fill out large
    for(int i = 0; i < 100; i++)
      large.insert(i, 1000 + i);
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
  LListInt list;
  LListInt small;
  LListInt large;
  LListInt empty;
};

TEST_F(LinkedListTest, CopyConstructorNominal) {
  LListInt copiedList(list);

  // check sizes
  EXPECT_EQ(list.size(), copiedList.size());
  // make sure it's not a shallow copy (chk for different addresses)
  EXPECT_NE(&list, &copiedList);
  // check if all items equal
  for (int i = 0; i < list.size(); i++)
  	EXPECT_EQ(list.get(i), copiedList.get(i));

  // additional check. set the same location of the two lists to different value
  list.set(5, 155); copiedList.set(5, 259);
  EXPECT_NE(list.get(5), copiedList.get(5));
}

TEST_F(LinkedListTest, OperatorEqualsNominal) {
	// Try to assign to self
	list = list;
	EXPECT_EQ(list.size(), 25);
  // Assign 10 items to 25 items
  list = small;
  EXPECT_EQ(list.size(), small.size());
  // Check if lists are different
  EXPECT_NE(&list, &small);

  // Assign 100 items to 10 items
  list = large;
  EXPECT_EQ(list.size(), large.size());
  // Check if lists are different
  EXPECT_NE(&list, &large);
  EXPECT_NE(&small, &large);
}

TEST_F(LinkedListTest, OperatorPlusNominal) {
	// Try to add self with another
	list = list + small;
	EXPECT_EQ(list.size(), 35);
	// check if other list is still the same
	EXPECT_EQ(small.size(), 10);
	list = list + list;
	EXPECT_EQ(list.size(), 70);
	list = small + large;
	EXPECT_EQ(list.size(), 110);
	list = large + large;
	EXPECT_EQ(list.size(), 200);
}

TEST_F(LinkedListTest, OperatorAccessNominal) {
	// Out of bounds
	EXPECT_ANY_THROW(list[-1]);
	EXPECT_ANY_THROW(list[list.size()+5]);

	// check for correct return value
	EXPECT_EQ(list[2], list.get(2));
}