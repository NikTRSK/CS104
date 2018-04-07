#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

// Intentionally left blank -- Include the student's heap header file here.
#include "../hw6_sol/heap.h"

#define RANDOM_HEAP_ARY 0
#define RUN_LARGE_TESTS 1

const int MAX_HEAP_ARY = 26;
const int DEFAULT_HEAP_ARY = 2;

template<typename T>
struct MyComp
{
	bool operator()(const std::pair<T, int>& lhs, const std::pair<T, int>& rhs)
	{
		return lhs.second < rhs.second;
	}
};

#define RANDOM_TEST(NUM_ELEMENTS, TYPE, CONTAINER, RANDOM_FUNCTION) { \
	bool caughtException = false; \
	int numberOfItemsAdded = 0; \
	try { \
		std::vector<std::pair<TYPE, int> > randomElements; \
		std::set<int> encounteredPriorities; \
		for(int i = 0; i < NUM_ELEMENTS; ++i) { \
			TYPE random = RANDOM_FUNCTION; \
			int randomPriority = rand(); \
			if(encounteredPriorities.find(randomPriority) == encounteredPriorities.end()) { \
				encounteredPriorities.insert(randomPriority); \
				randomElements.push_back(std::pair<TYPE, int>(random, randomPriority)); \
				CONTAINER.add(random, randomPriority); \
				++numberOfItemsAdded; \
			} \
			else { \
				--i; \
			} \
		} \
		MyComp<TYPE> myComp; \
		std::sort(randomElements.begin(), randomElements.end(), myComp); \
		TYPE peekValue; \
		int currentItem = 0; \
		while(!CONTAINER.isEmpty()) { \
			peekValue = CONTAINER.peek(); \
			EXPECT_EQ(peekValue, randomElements.at(currentItem++).first); \
			CONTAINER.remove(); \
		} \
	} \
	catch(std::exception& e) { \
		caughtException = true; \
	} \
	EXPECT_FALSE(caughtException); \
	EXPECT_EQ(numberOfItemsAdded, NUM_ELEMENTS); \
	EXPECT_TRUE(CONTAINER.isEmpty()); \
}

std::string GenerateRandomString(int numCharacters)
{
	int characters = 0;
	std::string returnString = "";
	while(characters < numCharacters)
	{
		returnString += static_cast<char>(rand() % 32 + 32);
		++characters;
	}
	return returnString;
}

class HeapTest : public testing::Test
{
	protected:
		#if RANDOM_HEAP_ARY
		HeapTest() 
			: D_ARY(rand() % MAX_HEAP_ARY + 2)
			, mMinHeapString(D_ARY) 
			, mMinHeapInt(D_ARY)
		{ 
			std::cout << "Running heap test with " << D_ARY << "-ary heap" << std::endl;
		}
		#else
		HeapTest() 
			: D_ARY(DEFAULT_HEAP_ARY)
			, mMinHeapString(D_ARY)
			, mMinHeapInt(D_ARY) 
		{ 

		}
		#endif

		~HeapTest() { }
		virtual void SetUp() { }
		virtual void TearDown() { }

		int D_ARY;
		MinHeap<std::string> mMinHeapString;
		MinHeap<int> mMinHeapInt;
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	srand(57821);

	return RUN_ALL_TESTS();
}

TEST_F(HeapTest, InitiallyEmpty_01)
{
	EXPECT_TRUE(mMinHeapString.isEmpty());
	EXPECT_TRUE(mMinHeapInt.isEmpty());
}

TEST_F(HeapTest, AddSingleItem_02)
{
	bool caughtException = false;
	try
	{
		mMinHeapString.add("test", 20);
		mMinHeapInt.add(10, 10);
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}
	EXPECT_FALSE(caughtException);
}

TEST_F(HeapTest, AddSingleItemPeek_03)
{
	bool caughtException = false;
	std::string stringPeekValue = "";
	int intPeekValue = 0;
	try
	{
		mMinHeapString.add("test", 20);
		mMinHeapInt.add(100, 20);
		stringPeekValue = mMinHeapString.peek();
		intPeekValue = mMinHeapInt.peek();
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}
	EXPECT_FALSE(caughtException);
	EXPECT_EQ(stringPeekValue, "test");
	EXPECT_EQ(intPeekValue, 100);
}

TEST_F(HeapTest, AddSingleItemRemoveCheckEmpty_04)
{
	bool caughtException = false;
	try
	{
		mMinHeapString.add("test", 20);
		mMinHeapInt.add(100, 20);
		mMinHeapString.remove();
		mMinHeapInt.remove();
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}
	EXPECT_FALSE(caughtException);
	EXPECT_TRUE(mMinHeapString.isEmpty());
	EXPECT_TRUE(mMinHeapInt.isEmpty());
}

TEST_F(HeapTest, AddTwoItemsInOrderPeek_05)
{
	bool caughtException = false;
	std::string stringPeekValue = "";
	int intPeekValue = 0;
	try
	{
		mMinHeapString.add("Gandalf", 10);
		mMinHeapString.add("Sauron", 20);
		mMinHeapInt.add(100, 10);
		mMinHeapInt.add(200, 20);
		stringPeekValue = mMinHeapString.peek();
		intPeekValue = mMinHeapInt.peek();
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(stringPeekValue, "Gandalf");
	EXPECT_EQ(intPeekValue, 100);
}

TEST_F(HeapTest, AddTwoItemsOutOfOrderPeek_06)
{
	bool caughtException = false;
	std::string stringPeekValue = "";
	int intPeekValue = 0;
	try
	{
		mMinHeapString.add("Sauron", 20);
		mMinHeapString.add("Gandalf", 10);
		mMinHeapInt.add(100, 20);
		mMinHeapInt.add(200, 10);
		stringPeekValue = mMinHeapString.peek();
		intPeekValue = mMinHeapInt.peek();
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(stringPeekValue, "Gandalf");
	EXPECT_EQ(intPeekValue, 200);
}

TEST_F(HeapTest, AddThreeItemsOutOfOrderPeek_07)
{
	bool caughtException = false;
	std::string stringPeekValue = "";
	std::vector<int> intValues;
	try
	{
		mMinHeapString.add("z", 26);
		mMinHeapString.add("a", 1);
		mMinHeapString.add("m", 13);
		mMinHeapInt.add(-100, -100);
		mMinHeapInt.add(-27, -27);
		mMinHeapInt.add(54, 54);

		while(!mMinHeapString.isEmpty())
		{
			stringPeekValue += mMinHeapString.peek();
			mMinHeapString.remove();
		}

		while(!mMinHeapInt.isEmpty())
		{
			intValues.push_back(mMinHeapInt.peek());
			mMinHeapInt.remove();
		}
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(stringPeekValue, "amz");
	EXPECT_EQ(intValues.size(), 3);
	EXPECT_EQ(intValues[0], -100);
	EXPECT_EQ(intValues[1], -27);
	EXPECT_EQ(intValues[2], 54);
}

TEST_F(HeapTest, AddEightItemsOutOfOrderPeek_08)
{
	bool caughtException = false;
	std::string stringPeekValue = "";
	std::vector<int> intValues;
	try
	{
		mMinHeapString.add("t", 20);
		mMinHeapString.add("r", 18);
		mMinHeapString.add("o", 15);
		mMinHeapString.add("p", 16);
		mMinHeapString.add("i", 9);
		mMinHeapString.add("c", 2);
		mMinHeapString.add("a", 1);
		mMinHeapString.add("l", 12);

		mMinHeapInt.add(21, 21);
		mMinHeapInt.add(13, 13);
		mMinHeapInt.add(8, 8);
		mMinHeapInt.add(5, 5);
		mMinHeapInt.add(3, 3);
		mMinHeapInt.add(2, 2);
		mMinHeapInt.add(1, 1);
		mMinHeapInt.add(1, 1);

		while(!mMinHeapString.isEmpty())
		{
			stringPeekValue += mMinHeapString.peek();
			mMinHeapString.remove();
		}

		while(!mMinHeapInt.isEmpty())
		{
			intValues.push_back(mMinHeapInt.peek());
			mMinHeapInt.remove();
		}
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	EXPECT_FALSE(caughtException);
	EXPECT_EQ(stringPeekValue, "aciloprt");
	EXPECT_EQ(intValues.size(), 8);
	EXPECT_EQ(intValues[0], 1);
	EXPECT_EQ(intValues[1], 1);
	EXPECT_EQ(intValues[2], 2);
	EXPECT_EQ(intValues[3], 3);
	EXPECT_EQ(intValues[4], 5);
	EXPECT_EQ(intValues[5], 8);
	EXPECT_EQ(intValues[6], 13);
	EXPECT_EQ(intValues[7], 21);

}

TEST_F(HeapTest, Add10ItemsRemoveUntilEmpty_09)
{
	RANDOM_TEST(10, int, mMinHeapInt, rand())
	RANDOM_TEST(10, std::string, mMinHeapString, GenerateRandomString(10))
}

TEST_F(HeapTest, Add100ItemsRemoveUntilEmpty_10)
{
	RANDOM_TEST(100, int, mMinHeapInt, rand())
	RANDOM_TEST(100, std::string, mMinHeapString, GenerateRandomString(10))
}

TEST_F(HeapTest, Add1000ItemsRemoveUntilEmpty_11)
{
	RANDOM_TEST(1000, int, mMinHeapInt, rand())
	RANDOM_TEST(1000, std::string, mMinHeapString, GenerateRandomString(10))
}

TEST_F(HeapTest, Add10000ItemsRemoveUntilEmpty_12)
{
	RANDOM_TEST(10000, int, mMinHeapInt, rand())
	RANDOM_TEST(10000, std::string, mMinHeapString, GenerateRandomString(10))
}

TEST_F(HeapTest, Add100000ItemsRemoveUntilEmpty_13)
{
	RANDOM_TEST(100000, int, mMinHeapInt, rand())
	RANDOM_TEST(100000, std::string, mMinHeapString, GenerateRandomString(10))
}

#if RUN_LARGE_TESTS

TEST_F(HeapTest, Add100000ItemsRemoveUntilEmpty_14)
{
	RANDOM_TEST(1000000, int, mMinHeapInt, rand())
	RANDOM_TEST(1000000, std::string, mMinHeapString, GenerateRandomString(10))
}

#endif
