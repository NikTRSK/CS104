/*
	CS 104: Homework 3 Problem 3 
	gtest_llistint.cpp

	Contains unit tests for checking student's implementations of a 
	doubly linked list that tracks integers. This is an extension of
	Problem 7 from Homework 2, which asks students to implement a
	copy constructor, assignment operator, bracket indexer, and 
	plus operator. 
*/

#include <iostream>
#include <cstdlib>
#include "gtest/gtest.h"
#include "llistint.h"

/**
* Recursively constructs a list with the given items.
* 
* @param numberOfItems The number of items that will be in the linked list.
* @param index The current index that should be considered from items array (start with 0).
* @param items The array of integer items that will be added to the list. 
*/
void ConstructList(LListInt& list, int numberOfItems, int items[])
{
	int numberOfInsertedItems(0);
	while(numberOfInsertedItems < numberOfItems)
	{
		list.insert(numberOfInsertedItems, items[numberOfInsertedItems]);
		++numberOfInsertedItems;
	}
}

#define RUN_HW2_TESTS 0

class LListIntTest : public testing::Test
{
	protected:
		LListIntTest() 
		{ 

		}

		~LListIntTest() 
		{ 

		}

		virtual void SetUp() 
		{
			mLListInt = new LListInt();
		}

		virtual void TearDown() 
		{ 
			mLListInt->clear();
			delete mLListInt;
		}

		LListInt *mLListInt;
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

TEST_F(LListIntTest, CopyConstructorEmptyLists_EmptySize)
{
	LListInt copiedList(*mLListInt);

	EXPECT_TRUE(copiedList.empty());
	EXPECT_EQ(copiedList.size(), 0);
}

TEST_F(LListIntTest, CopyConstructorOneItem_EmptySize)
{
	mLListInt->insert(0, 10);
	LListInt copiedList(*mLListInt);
	EXPECT_FALSE(copiedList.empty());
	EXPECT_EQ(copiedList.size(), 1);
}

TEST_F(LListIntTest, CopyConstructorOneItem_CheckElement)
{
	mLListInt->insert(0, 10);
	LListInt copiedList(*mLListInt);
	EXPECT_EQ(copiedList.get(0), 10);
}

TEST_F(LListIntTest, CopyConstructorOneItem_PostSet)
{
	mLListInt->insert(0, 10);
	LListInt copiedList(*mLListInt);
	copiedList.set(0, 20);
	EXPECT_EQ(copiedList.get(0), 20);
	EXPECT_EQ(mLListInt->get(0), 10);
}

TEST_F(LListIntTest, CopyConstructorOneItem_PostRemove)
{
	mLListInt->insert(0, 10);
	LListInt copiedList(*mLListInt);
	copiedList.remove(0);
	EXPECT_TRUE(copiedList.empty());
	EXPECT_FALSE(mLListInt->empty());
}

TEST_F(LListIntTest, CopyConstructorOneItem_PostInsert)
{
	mLListInt->insert(0, 10);
	LListInt copiedList(*mLListInt);
	copiedList.insert(1, 20);
	EXPECT_EQ(copiedList.size(), 2);
	EXPECT_EQ(mLListInt->size(), 1);
}

TEST_F(LListIntTest, CopyConstructorTenItems_CheckOrder)
{
	for(int i = 0; i < 10; ++i)
	{
		mLListInt->insert(i, i);
	}
	LListInt copiedList(*mLListInt); 
	for(int i = 0; i < 10; ++i)
	{
		EXPECT_EQ(mLListInt->get(i), i);
	}
}

TEST_F(LListIntTest, AssignmentOperatorEmptyLists_EmptySize)
{
	LListInt assignedList;
	assignedList = *mLListInt;
	EXPECT_EQ(assignedList.size(), 0);
	EXPECT_TRUE(assignedList.empty());
}

TEST_F(LListIntTest, AssignmentOperatorOneItem_EmptySize)
{
	mLListInt->insert(0, 10);
	LListInt assignedList;
	assignedList = *mLListInt;
	EXPECT_FALSE(assignedList.empty());
	EXPECT_EQ(assignedList.size(), 1);
}

TEST_F(LListIntTest, AssignmentOperatorOneItem_CheckElement)
{
	mLListInt->insert(0, 10);
	LListInt assignedList;
	assignedList = *mLListInt;	
	EXPECT_EQ(assignedList.get(0), 10);
}

TEST_F(LListIntTest, AssignmentOperatorOneItem_PostSet)
{
	mLListInt->insert(0, 10);
	LListInt assignedList;
	assignedList = *mLListInt;
	assignedList.set(0, 20);
	EXPECT_EQ(assignedList.get(0), 20);
	EXPECT_EQ(mLListInt->get(0), 10);
}

TEST_F(LListIntTest, AssignmentOperatorOneItem_PostRemove)
{
	mLListInt->insert(0, 10);
	LListInt assignedList;
	assignedList = *mLListInt;
	assignedList.remove(0);
	EXPECT_TRUE(assignedList.empty());
	EXPECT_FALSE(mLListInt->empty());
}

TEST_F(LListIntTest, AssignmentOperatorOneItem_PostInsert)
{
	mLListInt->insert(0, 10);
	LListInt assignedList;
	assignedList = *mLListInt;
	assignedList.insert(1, 20);
	EXPECT_EQ(assignedList.size(), 2);
	EXPECT_EQ(mLListInt->size(), 1);
}

TEST_F(LListIntTest, AssignmentOperatorTenItems_CheckOrder)
{
	for(int i = 0; i < 10; ++i)
	{
		mLListInt->insert(i, i);
	}
	LListInt assignedList;
	assignedList = *mLListInt;
	for(int i = 0; i < 10; ++i)
	{
		EXPECT_EQ(mLListInt->get(i), i);
	}
}

TEST_F(LListIntTest, AssignemtOperatorTenItems_LargerToSmaller)
{
	int elements[] = { 1, 2, 3, 4, 5 };
	LListInt smallerList;
	ConstructList(smallerList, 5, elements);
	for(int i = 0; i < 10; ++i)
	{
		mLListInt->insert(i, i);
	}
	smallerList = *mLListInt;
	EXPECT_EQ(smallerList.size(), 10);
	for(int i = 0; i < smallerList.size(); ++i)
	{
		EXPECT_EQ(smallerList.get(i), i);
	}
}

TEST_F(LListIntTest, AssignmentOperatorTenItems_SmallerToLarger)
{
	int elements[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	LListInt smallerList;
	ConstructList(smallerList, 10, elements);
	for(int i = 0; i < 5; ++i)
	{
		mLListInt->insert(i, i);
	}
	smallerList = *mLListInt;
	EXPECT_EQ(smallerList.size(), 5);
	for(int i = 0; i < smallerList.size(); ++i)
	{
		EXPECT_EQ(smallerList.get(i), i);
	}
}

TEST_F(LListIntTest, AssignmentOperatorSelfAssignmentOneItem)
{
	mLListInt->insert(0, 10);
	*mLListInt = *mLListInt;
	EXPECT_FALSE(mLListInt->empty());
	EXPECT_EQ(mLListInt->get(0), 10);
}

TEST_F(LListIntTest, AssignmentOperatorSelfAssignmentTenItems)
{
	for(int i = 0; i < 10; ++i)
	{
		mLListInt->insert(i, i);
	}
	*mLListInt = *mLListInt;
	EXPECT_FALSE(mLListInt->empty());
	for(int i = 0; i < 10; ++i)
	{
		EXPECT_EQ(mLListInt->get(i), i);
	}
}

TEST_F(LListIntTest, AssignmentOperatorCascadingAssignments)
{
	for(int i = 0; i < 10; ++i)
	{
		mLListInt->insert(i, i);
	}
	LListInt list1, list2;
	list1 = list2 = *mLListInt;
	EXPECT_FALSE(list1.empty());
	EXPECT_FALSE(list2.empty());
	EXPECT_EQ(list1.size(), 10);
	EXPECT_EQ(list2.size(), 10);
	for(int i = 0; i < 10; ++i)
	{
		EXPECT_EQ(list1.get(i), i);
		EXPECT_EQ(list2.get(i), i);
	}
}

TEST_F(LListIntTest, AssignmentOperatorCascadingAssignments_PostModification)
{
	for(int i = 0; i < 10; ++i)
	{
		mLListInt->insert(i, i);
	}
	LListInt list1, list2;
	list1 = list2 = *mLListInt;
	EXPECT_FALSE(list1.empty());
	EXPECT_FALSE(list2.empty());
	EXPECT_EQ(list1.size(), 10);
	EXPECT_EQ(list2.size(), 10);
	list1.insert(10, 10);
	list2.remove(9);
	EXPECT_EQ(list1.size(), 11);
	EXPECT_EQ(list2.size(), 9);
	EXPECT_EQ(mLListInt->size(), 10);
	for(int i = 0; i < 9; ++i)
	{
		EXPECT_EQ(list1.get(i), i);
		EXPECT_EQ(list2.get(i), i);
	}
	EXPECT_EQ(list1.get(10), 10);
}

TEST_F(LListIntTest, AccessOperatorOneItem)
{
	mLListInt->insert(0, 11);
	EXPECT_EQ((*mLListInt)[0], 11);
}

TEST_F(LListIntTest, AccessOperatorTenItems)
{
	for(int i = 0; i < 10; ++i)
	{
		mLListInt->insert(i, i);
	}
	for(int i = 0; i < 10; ++i)
	{
		EXPECT_EQ((*mLListInt)[i], i);
	}
}

TEST_F(LListIntTest, ConcatenateOperatorEmptyLists)
{
	LListInt otherList;
	LListInt concatenatedList = *mLListInt + otherList;
	EXPECT_TRUE(concatenatedList.empty());
	EXPECT_EQ(concatenatedList.size(), 0);
}

TEST_F(LListIntTest, ConcatenateOperatorEmptyPlusOneItem)
{
	LListInt otherList;
	otherList.insert(0, 10);
	LListInt concatenatedList = *mLListInt + otherList;
	EXPECT_FALSE(concatenatedList.empty());
	EXPECT_EQ(concatenatedList.size(), 1);
	EXPECT_EQ(concatenatedList.get(0), 10);
	EXPECT_EQ(otherList.size(), 1);
	EXPECT_EQ(otherList.get(0), 10);
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, ConcatenateOperatorOneItemPlusEmpty)
{
	LListInt otherList;
	mLListInt->insert(0, 10);
	LListInt concatenatedList = *mLListInt + otherList;
	EXPECT_FALSE(concatenatedList.empty());
	EXPECT_EQ(concatenatedList.size(), 1);
	EXPECT_EQ(concatenatedList.get(0), 10);
	EXPECT_EQ(otherList.size(), 0);
	EXPECT_EQ(mLListInt->size(), 1);
	EXPECT_EQ(mLListInt->get(0), 10);
}

TEST_F(LListIntTest, ConcatenateOperatorTenItemsPlusTenItems)
{
	int elements1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int elements2[] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	LListInt otherList;
	ConstructList(otherList, 10, elements2);
	ConstructList(*mLListInt, 10, elements1);
	LListInt concatenatedList = *mLListInt + otherList;

	EXPECT_EQ(otherList.size(), 10);
	for(int i = 0; i < otherList.size(); ++i)
	{
		EXPECT_EQ(otherList.get(i), i + 11);
	}

	EXPECT_EQ(mLListInt->size(), 10);
	for(int i = 0; i < mLListInt->size(); ++i)
	{
		EXPECT_EQ(mLListInt->get(i), i + 1);
	}

	EXPECT_EQ(concatenatedList.size(), 20);
	for(int i = 0; i < concatenatedList.size(); ++i)
	{
		EXPECT_EQ(concatenatedList.get(i), i + 1);
	}
}

#if RUN_HW2_TESTS

TEST_F(LListIntTest, InitiallyEmpty_01)
{
	EXPECT_TRUE(mLListInt->empty());
}

TEST_F(LListIntTest, InitiallySizeZero_02)
{
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, EmptyInsertLess_03)
{
	mLListInt->insert(-1, 10);
	EXPECT_TRUE(mLListInt->empty());
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, EmptyInsertGreater_04)
{
	mLListInt->insert(1, 10);
	EXPECT_TRUE(mLListInt->empty());
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, EmptyRemoveLess_05)
{
	mLListInt->remove(-1);
	EXPECT_TRUE(mLListInt->empty());
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, EmptyRemoveGreater_06)
{
	mLListInt->remove(1);
	EXPECT_TRUE(mLListInt->empty());
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, SingleInsertNotEmpty_07)
{
	mLListInt->insert(0, 10);
	EXPECT_FALSE(mLListInt->empty());
}

TEST_F(LListIntTest, SingleInsertSize_08)
{
	mLListInt->insert(0, 10);
	EXPECT_EQ(mLListInt->size(), 1);
}

TEST_F(LListIntTest, SingleInsertThenRemoveEmpty_09)
{
	mLListInt->insert(0, 10);
	mLListInt->remove(0);
	EXPECT_TRUE(mLListInt->empty());
}

TEST_F(LListIntTest, SingleInsertThenRemoveSize_10)
{
	mLListInt->insert(0, 10);
	mLListInt->remove(0);
	EXPECT_EQ(mLListInt->size(), 0);
}

TEST_F(LListIntTest, MultipleInsertHeadCheckOrder_11)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListInt->insert(0, i);
		EXPECT_EQ(mLListInt->size(), i + 1);
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_EQ(mLListInt->get(i), NUMBER_OF_ELEMENTS - i - 1);
	}
}

TEST_F(LListIntTest, MultipleInsertTailCheckOrder_12)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListInt->insert(mLListInt->size(), i);
		EXPECT_EQ(mLListInt->size(), i + 1);
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_EQ(mLListInt->get(i), i);
	}
}

TEST_F(LListIntTest, MultipleInsertMiddleCheckOrder_13)
{
	const int NUMBER_OF_ELEMENTS = 10;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListInt->insert(mLListInt->size() / 2, i);
		EXPECT_EQ(mLListInt->size(), i + 1);
	}

	EXPECT_EQ(mLListInt->get(0), 1);
	EXPECT_EQ(mLListInt->get(1), 3);
	EXPECT_EQ(mLListInt->get(2), 5);
	EXPECT_EQ(mLListInt->get(3), 7);
	EXPECT_EQ(mLListInt->get(4), 9);
	EXPECT_EQ(mLListInt->get(5), 8);
	EXPECT_EQ(mLListInt->get(6), 6);
	EXPECT_EQ(mLListInt->get(7), 4);
	EXPECT_EQ(mLListInt->get(8), 2);
	EXPECT_EQ(mLListInt->get(9), 0);
}

TEST_F(LListIntTest, MultipleInsertRandomThenRemoveRandom_14)
{
	const int NUMBER_OF_ELEMENTS = 10;

	mLListInt->insert(0, 0);

	for(int i = 1; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListInt->insert(rand() % mLListInt->size(), i);
		EXPECT_EQ(mLListInt->size(), i + 1);
	}

	int size = mLListInt->size();
	while(mLListInt->size() != 1)
	{
		mLListInt->remove(rand() % (mLListInt->size() - 1));
		EXPECT_EQ(mLListInt->size(), --size);
	}
}

TEST_F(LListIntTest, LargeInputStressTest_15)
{
	const int NUMBER_OF_ELEMENTS = 10000;

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		mLListInt->insert(0, i);
	}

	for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
	{
		EXPECT_EQ(mLListInt->get(0), NUMBER_OF_ELEMENTS - i - 1);
		mLListInt->remove(0);
		EXPECT_EQ(mLListInt->size(), NUMBER_OF_ELEMENTS - i - 1);
	}
}

#endif
