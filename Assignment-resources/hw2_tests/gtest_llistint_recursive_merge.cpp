/*
	CS 104: Homework 2 Problem 6 
	gtest_llistint_recursive_remove.cpp

	Contains unit tests for checking student's implementations of a recursive
	function that merges two sorted singly linked lists. 
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "gtest/gtest.h"


struct Node
{
	int value; 
	Node *next;
};

/**
* Your implementation goes here.
*/


/**
* A macro defined function to check the ordering of a list. Used to
* make use of the ASSERT/EXPECT macros provided by Google Test so that
* a list can be checked without repeating code. 
*/
#define CHECK_LIST_ORDER(HEAD, NUMBER_OF_ITEMS) { \
	Node *temp = HEAD; \
	int numberOfItems = 0; \
	for(int i = NUMBER_OF_ITEMS; i >= 0; --i) \
	{ \
		if(i == 0) \
		{ \
			EXPECT_TRUE(temp == NULL); \
		} \
		else \
		{ \
			ASSERT_FALSE(temp == NULL); \
			++numberOfItems; \
			if(temp->next != NULL) \
			{ \
				EXPECT_LE(temp->value, temp->next->value); \
			} \
			temp = temp->next; \
		} \
	} \
	EXPECT_EQ(NUMBER_OF_ITEMS, numberOfItems); \
}

/**
* Recursively prints the contents of a list. 
*
* @param head The head of the linked list where printing will start. 
*/ 
void PrintList(Node *head)
{
	if(head != NULL)
	{
		std::cout << head->value << std::endl;
		PrintList(head->next);
	}
}

/**
* Recursively deletes the contents of a list. 
*
* @param head The head of the linked list to be deleted. 
*/
void DeleteList(Node *head)
{
	if(head != NULL)
	{
		DeleteList(head->next);
		delete head;
	}
}

/**
* Recursively constructs a linked list based on the explicit values provided.
* 
* @param numberOfItems The number of items that will be in the linked list.
* @param index The current index that should be considered from items array (start with 0).
* @param items The array of integer items that will be added to the list. 
* @return The head of the newly constructed linked list. 
*/
Node *ConstructList(int numberOfItems, int index, int items[])
{
	if(numberOfItems == 0)
	{
		return NULL;
	}
	else
	{
		Node *temp = new Node;
		temp->value = items[index];
		temp->next = ConstructList(numberOfItems - 1, index + 1, items);
		return temp;
	}
}

/**
* Recursively constructs a linked list with random values based on the parameters. The
* linked list is guaranteed to be in ascending order. 
*
* @param numberOfItems The number of items that will be in the linked list when the function terminates.
* @param startingValue The initial value in the linked list, from which all values will be larger.
* @param maxIncrement The maximum difference in value between adjacent nodes.
* @return The head of the newly constructed linked list. 
*/
Node *ConstructList(int numberOfItems, int startingValue, int maxIncrement)
{
	if(numberOfItems == 0)
	{
		return NULL;
	}
	else
	{
		Node *temp = new Node;
		temp->value = startingValue + rand() % maxIncrement;
		temp->next = ConstructList(numberOfItems - 1, temp->value, maxIncrement);
		return temp;
	}
}

class LListIntRecursion : public testing::Test
{
	protected:
		LListIntRecursion() 
			: mFirstList(NULL)
			, mSecondList(NULL)
			, mResultList(NULL)
		{ 
			srand(time(0));
		}

		~LListIntRecursion() 
		{ 

		}

		virtual void SetUp() 
		{
			mFirstList = NULL;
			mSecondList = NULL;
			mResultList = NULL;
		}

		virtual void TearDown() 
		{ 
			DeleteList(mResultList);
		}

		Node *mFirstList;
		Node *mSecondList;
		Node *mResultList;
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

TEST_F(LListIntRecursion, EmptyMerge)
{
	mResultList = merge(mFirstList, mSecondList);

	EXPECT_TRUE(mResultList == NULL);
}

TEST_F(LListIntRecursion, OneItemList1_EmptyList2)
{
	mFirstList = new Node;
	mFirstList->value = 10;
	mFirstList->next = NULL;

	mResultList = merge(mFirstList, mSecondList);

	ASSERT_FALSE(mResultList == NULL);
	EXPECT_EQ(mResultList->value, 10);
	EXPECT_TRUE(mResultList->next == NULL);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, EmptyList1_OneItemList2)
{
	mSecondList = new Node;
	mSecondList->value = 10;
	mSecondList->next = NULL;

	mResultList = merge(mFirstList, mSecondList);

	ASSERT_FALSE(mResultList == NULL);
	EXPECT_EQ(mResultList->value, 10);
	EXPECT_TRUE(mResultList->next == NULL);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, OneItemEachList_1_2)
{
	mFirstList = new Node;
	mFirstList->value = 1;
	mFirstList->next = NULL;

	mSecondList = new Node;
	mSecondList->value = 2;
	mSecondList->next = NULL;

	mResultList = merge(mFirstList, mSecondList);

	ASSERT_FALSE(mResultList == NULL);
	EXPECT_EQ(mResultList->value, 1);
	ASSERT_FALSE(mResultList->next == NULL);
	EXPECT_EQ(mResultList->next->value, 2);
	EXPECT_TRUE(mResultList->next->next == NULL);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, OneItemEachList_2_1)
{
	mFirstList = new Node;
	mFirstList->value = 2;
	mFirstList->next = NULL;

	mSecondList = new Node;
	mSecondList->value = 1;
	mSecondList->next = NULL;

	mResultList = merge(mFirstList, mSecondList);

	ASSERT_FALSE(mResultList == NULL);
	EXPECT_EQ(mResultList->value, 1);
	ASSERT_FALSE(mResultList->next == NULL);
	EXPECT_EQ(mResultList->next->value, 2);
	EXPECT_TRUE(mResultList->next->next == NULL);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, TwoItemsEachList_12_34)
{
	int list1Contents[] = { 1, 2 };
	int list2Contents[] = { 3, 4 };
	mFirstList = ConstructList(2, 0, list1Contents);
	mSecondList = ConstructList(2, 0, list2Contents);

	mResultList = merge(mFirstList, mSecondList);

	CHECK_LIST_ORDER(mResultList, 4);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, TwoItemsEachList_13_24)
{
	int list1Contents[] = { 1, 3 };
	int list2Contents[] = { 2, 4 };
	mFirstList = ConstructList(2, 0, list1Contents);
	mSecondList = ConstructList(2, 0, list2Contents);

	mResultList = merge(mFirstList, mSecondList);

	CHECK_LIST_ORDER(mResultList, 4);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, TwoItemsEachList_14_23)
{
	int list1Contents[] = { 1, 4 };
	int list2Contents[] = { 2, 3 };
	mFirstList = ConstructList(2, 0, list1Contents);
	mSecondList = ConstructList(2, 0, list2Contents);

	mResultList = merge(mFirstList, mSecondList);

	CHECK_LIST_ORDER(mResultList, 4);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, TwoItemsEachList_23_14)
{
	int list1Contents[] = { 2, 3 };
	int list2Contents[] = { 1, 4 };
	mFirstList = ConstructList(2, 0, list1Contents);
	mSecondList = ConstructList(2, 0, list2Contents);

	mResultList = merge(mFirstList, mSecondList);

	CHECK_LIST_ORDER(mResultList, 4);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, TwoItemsEachList_24_13)
{
	int list1Contents[] = { 2, 4 };
	int list2Contents[] = { 1, 3 };
	mFirstList = ConstructList(2, 0, list1Contents);
	mSecondList = ConstructList(2, 0, list2Contents);

	mResultList = merge(mFirstList, mSecondList);

	CHECK_LIST_ORDER(mResultList, 4);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, TwoItemsEachList_34_12)
{
	int list1Contents[] = { 3, 4 };
	int list2Contents[] = { 1, 2 };
	mFirstList = ConstructList(2, 0, list1Contents);
	mSecondList = ConstructList(2, 0, list2Contents);

	mResultList = merge(mFirstList, mSecondList);

	CHECK_LIST_ORDER(mResultList, 4);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, RepeatItems_122_334)
{
	int list1Contents[] = { 1, 2, 2 };
	int list2Contents[] = { 3, 3, 4 };
	mFirstList = ConstructList(3, 0, list1Contents);
	mSecondList = ConstructList(3, 0, list2Contents);

	mResultList = merge(mFirstList, mSecondList);

	CHECK_LIST_ORDER(mResultList, 6);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, RepeatItems_122_233)
{
	int list1Contents[] = { 1, 2, 2 };
	int list2Contents[] = { 2, 3, 3 };
	mFirstList = ConstructList(3, 0, list1Contents);
	mSecondList = ConstructList(3, 0, list2Contents);

	mResultList = merge(mFirstList, mSecondList);

	CHECK_LIST_ORDER(mResultList, 6);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, RandomListCreation_10ItemsEach)
{
	mFirstList = ConstructList(10, 0, 100);
	mSecondList = ConstructList(10, 10000, 10);

	mResultList = merge(mFirstList, mSecondList);

	CHECK_LIST_ORDER(mResultList, 20);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, RandomListCreation_FirstList200_SecondList500)
{
	mFirstList = ConstructList(200, 0, 100);
	mSecondList = ConstructList(500, 0, 10);

	mResultList = merge(mFirstList, mSecondList);

	CHECK_LIST_ORDER(mResultList, 700);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}

TEST_F(LListIntRecursion, RandomListCreation_1000ItemsEach)
{
	mFirstList = ConstructList(1000, 0, 100);
	mSecondList = ConstructList(1000, 0, 10);

	mResultList = merge(mFirstList, mSecondList);

	CHECK_LIST_ORDER(mResultList, 2000);

	EXPECT_TRUE(mFirstList == NULL);
	EXPECT_TRUE(mSecondList == NULL);
}