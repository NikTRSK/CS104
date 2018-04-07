/*
	CS 104: Homework 3 Problem 4 
	gtest_stackint.cpp

	Contains unit tests for checking students implementation of a stack
	that stores integers, which is created using a has-a relationship
	utilizing their llistint class. 
*/

#include <iostream>
#include <cstdlib>
#include "gtest/gtest.h"
#include "stackint.h"

/**
* A macro used for testing the order of elements within a stack. Gives
* access to member data as well as test macros needed for testing. Inserts
* the given number of elements into the stack and then removes elements
* from the stack until empty, checking the elements while removing. A 
* final check is done to make sure the stack is empty at the end. 
*/
#define STRESS_CHECK_ORDER(NUMBER_OF_ELEMENTS) { \
	int numberOfElementsInserted = 0; \
	for(; numberOfElementsInserted < NUMBER_OF_ELEMENTS;) { \
		mStackInt->push(numberOfElementsInserted); \
		++numberOfElementsInserted; \
	} \
	int topElement; \
	while(!mStackInt->empty()) { \
		topElement = mStackInt->top(); \
		EXPECT_EQ(topElement, --numberOfElementsInserted); \
		mStackInt->pop(); \
	} \
	EXPECT_EQ(numberOfElementsInserted, 0); \
}

class StackIntTest : public testing::Test
{
	protected:
		StackIntTest() 
		{ 

		}

		~StackIntTest() 
		{ 

		}

		virtual void SetUp() 
		{
			mStackInt = new StackInt();
		}

		virtual void TearDown() 
		{ 
			delete mStackInt;
		}

		StackInt *mStackInt;
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

TEST_F(StackIntTest, InitiallyEmpty)
{
	EXPECT_TRUE(mStackInt->empty());
}

TEST_F(StackIntTest, InsertOneElementNotEmpty)
{
	mStackInt->push(0);
	EXPECT_FALSE(mStackInt->empty());
}

TEST_F(StackIntTest, InsertOneElementGetTop)
{
	mStackInt->push(10);
	EXPECT_EQ(mStackInt->top(), 10);
}

TEST_F(StackIntTest, InsertOneElementPopEmpty)
{
	mStackInt->push(15);
	mStackInt->pop();
	EXPECT_TRUE(mStackInt->empty());
}

TEST_F(StackIntTest, Insert10Elements)
{
	STRESS_CHECK_ORDER(10);
}

TEST_F(StackIntTest, Insert100Elements)
{
	STRESS_CHECK_ORDER(100);
}

TEST_F(StackIntTest, Insert1000Elements)
{
	STRESS_CHECK_ORDER(1000);
}

TEST_F(StackIntTest, Insert10000Elements)
{
	STRESS_CHECK_ORDER(10000);
}

TEST_F(StackIntTest, Insert100000Elements)
{
	STRESS_CHECK_ORDER(100000);
}

TEST_F(StackIntTest, Insert1000000Elements)
{
	STRESS_CHECK_ORDER(1000000);
}