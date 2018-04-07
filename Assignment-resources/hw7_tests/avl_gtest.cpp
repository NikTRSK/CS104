#include "gtest/gtest.h"
#include <functional> 
#include <string>
#include <algorithm>

// Intentionally left blank -- Include the student's AVL header file here.
#include "../hw7_sol/avlbst_copy.h"

typedef AVLTree<std::string, int>::iterator StringIntIterator;
typedef AVLTree<int, double>::iterator IntDoubleIterator;

#define RANDOM_TEST(NUM_ELEMENTS, KEY_TYPE, VALUE_TYPE, CONTAINER, RANDOM_FUNCTION) { \
	bool caughtException = false; \
	int numberOfItemsAdded = 0; \
	try { \
		std::set<KEY_TYPE> encounteredKeys; \
		for(int i = 0; i < NUM_ELEMENTS; ++i) { \
			KEY_TYPE randomKey = RANDOM_FUNCTION; \
			VALUE_TYPE defaultValue; \
			if(encounteredKeys.find(randomKey) == encounteredKeys.end()) { \
				encounteredKeys.emplace(randomKey); \
				std::pair<KEY_TYPE, VALUE_TYPE> myPair(randomKey, defaultValue); \
				CONTAINER.insert(myPair); \
				++numberOfItemsAdded; \
			} \
			else { \
				--i; \
			} \
		} \
		while(!encounteredKeys.empty()) { \
			int index = rand() % encounteredKeys.size(); \
			auto beginSet = encounteredKeys.begin(); \
			std::advance(beginSet, index); \
			KEY_TYPE keyType = *(beginSet); \
			encounteredKeys.erase(keyType); \
			CONTAINER.remove(keyType); \
			auto beginAVLIter = CONTAINER.begin(); \
			auto beginSetIter = encounteredKeys.begin(); \
			int numberOfCheckedItems = 0; \
			while(beginAVLIter != CONTAINER.end()) { \
				EXPECT_EQ(*beginSetIter, beginAVLIter->first); \
				++numberOfCheckedItems; \
				++beginAVLIter; \
				++beginSetIter; \
			} \
			EXPECT_EQ(numberOfCheckedItems, encounteredKeys.size()); \
		} \
	} \
	catch(std::exception& e) { \
		caughtException = true; \
		std::cout << e.what() << std::endl; \
	} \
	EXPECT_FALSE(caughtException); \
	EXPECT_EQ(numberOfItemsAdded, NUM_ELEMENTS); \
} \

std::string GenerateRandomString(int numCharacters)
{
	int characters = 0;
	std::string returnString = "";
	while(characters < numCharacters)
	{
		returnString += static_cast<char>(rand() % 26 + 65);
		++characters;
	}
	return returnString;
}

class AVLTest : public testing::Test
{
	protected:
		AVLTest() { }
		~AVLTest() { }
		virtual void SetUp() { }
		virtual void TearDown() { }

		AVLTree<std::string, int> mStringIntAVL;
		AVLTree<int, double> mIntDoubleAVL;
};

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	srand(57821);

	return RUN_ALL_TESTS();
}

TEST_F(AVLTest, InitiallyEmpty_01)
{
	EXPECT_EQ(mStringIntAVL.begin(), mStringIntAVL.end());
	EXPECT_EQ(mIntDoubleAVL.begin(), mIntDoubleAVL.end());
}

TEST_F(AVLTest, SingleInsert_02)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Aaron", 0));
		mIntDoubleAVL.insert(std::make_pair(1, 100.5));
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());

	EXPECT_EQ(mStringIntAVL.begin()->first, "Aaron");
	EXPECT_EQ(mStringIntAVL.begin()->second, 0);
	EXPECT_EQ(mIntDoubleAVL.begin()->first, 1);
	EXPECT_EQ(mIntDoubleAVL.begin()->second, 100.5);
}

TEST_F(AVLTest, DoubleInsertLeft_03)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Aaron", 0));
		mStringIntAVL.insert(std::make_pair("Aardvark", 2));
		mIntDoubleAVL.insert(std::make_pair(1, 100.5));
		mIntDoubleAVL.insert(std::make_pair(0, 0.04));
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());

	StringIntIterator siIter = mStringIntAVL.begin();
	IntDoubleIterator idIter = mIntDoubleAVL.begin();

	EXPECT_EQ(siIter->first, "Aardvark");
	EXPECT_EQ(siIter->second, 2);
	EXPECT_EQ(idIter->first, 0);
	EXPECT_EQ(idIter->second, 0.04);
	++siIter;
	++idIter;

	ASSERT_NE(siIter, mStringIntAVL.end());
	ASSERT_NE(idIter, mIntDoubleAVL.end());

	EXPECT_EQ(siIter->first, "Aaron");
	EXPECT_EQ(siIter->second, 0);
	EXPECT_EQ(idIter->first, 1);
	EXPECT_EQ(idIter->second, 100.5);
	++siIter;
	++idIter;

	EXPECT_EQ(siIter, mStringIntAVL.end());
	EXPECT_EQ(idIter, mIntDoubleAVL.end());
}

TEST_F(AVLTest, DoubleInsertRight_04)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Aaron", 0));
		mStringIntAVL.insert(std::make_pair("Billy", 2));
		mIntDoubleAVL.insert(std::make_pair(1, 100.5));
		mIntDoubleAVL.insert(std::make_pair(2, 0.04));
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());

	StringIntIterator siIter = mStringIntAVL.begin();
	IntDoubleIterator idIter = mIntDoubleAVL.begin();

	EXPECT_EQ(siIter->first, "Aaron");
	EXPECT_EQ(siIter->second, 0);
	EXPECT_EQ(idIter->first, 1);
	EXPECT_EQ(idIter->second, 100.5);
	++siIter;
	++idIter;

	ASSERT_NE(siIter, mStringIntAVL.end());
	ASSERT_NE(idIter, mIntDoubleAVL.end());

	EXPECT_EQ(siIter->first, "Billy");
	EXPECT_EQ(siIter->second, 2);
	EXPECT_EQ(idIter->first, 2);
	EXPECT_EQ(idIter->second, 0.04);
	++siIter;
	++idIter;

	EXPECT_EQ(siIter, mStringIntAVL.end());
	EXPECT_EQ(idIter, mIntDoubleAVL.end());
}

TEST_F(AVLTest, InsertZigZigLeft_05)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Cathy", 0));
		mStringIntAVL.insert(std::make_pair("Billy", 1));
		mStringIntAVL.insert(std::make_pair("Aaron", 2));
		mIntDoubleAVL.insert(std::make_pair(2, 3.5));
		mIntDoubleAVL.insert(std::make_pair(1, 100.5));
		mIntDoubleAVL.insert(std::make_pair(0, 0.04));
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());

	StringIntIterator siIter = mStringIntAVL.begin();
	IntDoubleIterator idIter = mIntDoubleAVL.begin();

	EXPECT_EQ(siIter->first, "Aaron");
	EXPECT_EQ(siIter->second, 2);
	EXPECT_EQ(idIter->first, 0);
	EXPECT_EQ(idIter->second, 0.04);
	++siIter;
	++idIter;

	ASSERT_NE(siIter, mStringIntAVL.end());
	ASSERT_NE(idIter, mIntDoubleAVL.end());

	EXPECT_EQ(siIter->first, "Billy");
	EXPECT_EQ(siIter->second, 1);
	EXPECT_EQ(idIter->first, 1);
	EXPECT_EQ(idIter->second, 100.5);
	++siIter;
	++idIter;

	EXPECT_EQ(siIter->first, "Cathy");
	EXPECT_EQ(siIter->second, 0);
	EXPECT_EQ(idIter->first, 2);
	EXPECT_EQ(idIter->second, 3.5);
	++siIter;
	++idIter;

	EXPECT_EQ(siIter, mStringIntAVL.end());
	EXPECT_EQ(idIter, mIntDoubleAVL.end());
}

TEST_F(AVLTest, InsertZigZigRight_06)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Aaron", 2));
		mStringIntAVL.insert(std::make_pair("Billy", 1));		
		mStringIntAVL.insert(std::make_pair("Cathy", 0));
		mIntDoubleAVL.insert(std::make_pair(0, 0.04));
		mIntDoubleAVL.insert(std::make_pair(1, 100.5));
		mIntDoubleAVL.insert(std::make_pair(2, 3.5));
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());

	StringIntIterator siIter = mStringIntAVL.begin();
	IntDoubleIterator idIter = mIntDoubleAVL.begin();

	EXPECT_EQ(siIter->first, "Aaron");
	EXPECT_EQ(siIter->second, 2);
	EXPECT_EQ(idIter->first, 0);
	EXPECT_EQ(idIter->second, 0.04);
	++siIter;
	++idIter;

	ASSERT_NE(siIter, mStringIntAVL.end());
	ASSERT_NE(idIter, mIntDoubleAVL.end());

	EXPECT_EQ(siIter->first, "Billy");
	EXPECT_EQ(siIter->second, 1);
	EXPECT_EQ(idIter->first, 1);
	EXPECT_EQ(idIter->second, 100.5);
	++siIter;
	++idIter;

	EXPECT_EQ(siIter->first, "Cathy");
	EXPECT_EQ(siIter->second, 0);
	EXPECT_EQ(idIter->first, 2);
	EXPECT_EQ(idIter->second, 3.5);
	++siIter;
	++idIter;

	EXPECT_EQ(siIter, mStringIntAVL.end());
	EXPECT_EQ(idIter, mIntDoubleAVL.end());
}

TEST_F(AVLTest, InsertZigZagLeft_07)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Cathy", 0));
		mStringIntAVL.insert(std::make_pair("Aaron", 2));
		mStringIntAVL.insert(std::make_pair("Billy", 1));		
		mIntDoubleAVL.insert(std::make_pair(2, 3.5));
		mIntDoubleAVL.insert(std::make_pair(0, 0.04));
		mIntDoubleAVL.insert(std::make_pair(1, 100.5));
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());

	StringIntIterator siIter = mStringIntAVL.begin();
	IntDoubleIterator idIter = mIntDoubleAVL.begin();

	EXPECT_EQ(siIter->first, "Aaron");
	EXPECT_EQ(siIter->second, 2);
	EXPECT_EQ(idIter->first, 0);
	EXPECT_EQ(idIter->second, 0.04);
	++siIter;
	++idIter;

	ASSERT_NE(siIter, mStringIntAVL.end());
	ASSERT_NE(idIter, mIntDoubleAVL.end());

	EXPECT_EQ(siIter->first, "Billy");
	EXPECT_EQ(siIter->second, 1);
	EXPECT_EQ(idIter->first, 1);
	EXPECT_EQ(idIter->second, 100.5);
	++siIter;
	++idIter;

	EXPECT_EQ(siIter->first, "Cathy");
	EXPECT_EQ(siIter->second, 0);
	EXPECT_EQ(idIter->first, 2);
	EXPECT_EQ(idIter->second, 3.5);
	++siIter;
	++idIter;

	EXPECT_EQ(siIter, mStringIntAVL.end());
	EXPECT_EQ(idIter, mIntDoubleAVL.end());
}

TEST_F(AVLTest, InsertZigZagRight_08)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Aaron", 2));
		mStringIntAVL.insert(std::make_pair("Cathy", 0));
		mStringIntAVL.insert(std::make_pair("Billy", 1));		
		mIntDoubleAVL.insert(std::make_pair(0, 0.04));
		mIntDoubleAVL.insert(std::make_pair(2, 3.5));
		mIntDoubleAVL.insert(std::make_pair(1, 100.5));
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());

	StringIntIterator siIter = mStringIntAVL.begin();
	IntDoubleIterator idIter = mIntDoubleAVL.begin();

	EXPECT_EQ(siIter->first, "Aaron");
	EXPECT_EQ(siIter->second, 2);
	EXPECT_EQ(idIter->first, 0);
	EXPECT_EQ(idIter->second, 0.04);
	++siIter;
	++idIter;

	ASSERT_NE(siIter, mStringIntAVL.end());
	ASSERT_NE(idIter, mIntDoubleAVL.end());

	EXPECT_EQ(siIter->first, "Billy");
	EXPECT_EQ(siIter->second, 1);
	EXPECT_EQ(idIter->first, 1);
	EXPECT_EQ(idIter->second, 100.5);
	++siIter;
	++idIter;

	ASSERT_NE(siIter, mStringIntAVL.end());
	ASSERT_NE(idIter, mIntDoubleAVL.end());

	EXPECT_EQ(siIter->first, "Cathy");
	EXPECT_EQ(siIter->second, 0);
	EXPECT_EQ(idIter->first, 2);
	EXPECT_EQ(idIter->second, 3.5);
	++siIter;
	++idIter;

	EXPECT_EQ(siIter, mStringIntAVL.end());
	EXPECT_EQ(idIter, mIntDoubleAVL.end());
}

TEST_F(AVLTest, SingleInsertRemove_09)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Aaron", 0));
		mIntDoubleAVL.insert(std::make_pair(0, 0.4));

		mStringIntAVL.remove("Aaron");
		mIntDoubleAVL.remove(0);
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	EXPECT_EQ(mStringIntAVL.begin(), mStringIntAVL.end());
	EXPECT_EQ(mIntDoubleAVL.begin(), mIntDoubleAVL.end());
}

TEST_F(AVLTest, DoubleInsertLeftRemoveRoot_10)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Betty", 0));
		mStringIntAVL.insert(std::make_pair("Aaron", 1));
		mIntDoubleAVL.insert(std::make_pair(1, 0.4));
		mIntDoubleAVL.insert(std::make_pair(-1, 0.3));

		mStringIntAVL.remove("Betty");
		mIntDoubleAVL.remove(1);
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());
	EXPECT_EQ(mStringIntAVL.begin()->first, "Aaron");
	EXPECT_EQ(mStringIntAVL.begin()->second, 1);
	EXPECT_EQ(mIntDoubleAVL.begin()->first, -1);
	EXPECT_EQ(mIntDoubleAVL.begin()->second, 0.3);
}

TEST_F(AVLTest, DoubleInsertRightRemoveRoot_11)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Aaron", 0));
		mStringIntAVL.insert(std::make_pair("Betty", 1));
		mIntDoubleAVL.insert(std::make_pair(-1, 0.4));
		mIntDoubleAVL.insert(std::make_pair(1, 0.3));

		mStringIntAVL.remove("Aaron");
		mIntDoubleAVL.remove(-1);
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());
	EXPECT_EQ(mStringIntAVL.begin()->first, "Betty");
	EXPECT_EQ(mStringIntAVL.begin()->second, 1);
	EXPECT_EQ(mIntDoubleAVL.begin()->first, 1);
	EXPECT_EQ(mIntDoubleAVL.begin()->second, 0.3);
}

TEST_F(AVLTest, DoubleInsertLeftRemoveLeft_12)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Betty", 0));
		mStringIntAVL.insert(std::make_pair("Aaron", 1));
		mIntDoubleAVL.insert(std::make_pair(1, 0.4));
		mIntDoubleAVL.insert(std::make_pair(-1, 0.3));
		mStringIntAVL.remove("Aaron");
		mIntDoubleAVL.remove(-1);
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());
	EXPECT_EQ(mStringIntAVL.begin()->first, "Betty");
	EXPECT_EQ(mStringIntAVL.begin()->second, 0);
	EXPECT_EQ(mIntDoubleAVL.begin()->first, 1);
	EXPECT_EQ(mIntDoubleAVL.begin()->second, 0.4);
}

TEST_F(AVLTest, DoubleInsertRightRemoveRight_13)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Aaron", 0));
		mStringIntAVL.insert(std::make_pair("Betty", 1));
		mIntDoubleAVL.insert(std::make_pair(-1, 0.4));
		mIntDoubleAVL.insert(std::make_pair(1, 0.3));
		mStringIntAVL.remove("Betty");
		mIntDoubleAVL.remove(1);
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());
	EXPECT_EQ(mStringIntAVL.begin()->first, "Aaron");
	EXPECT_EQ(mStringIntAVL.begin()->second, 0);
	EXPECT_EQ(mIntDoubleAVL.begin()->first, -1);
	EXPECT_EQ(mIntDoubleAVL.begin()->second, 0.4);
}

TEST_F(AVLTest, TrippleInsertRemoveRoot_14)
{
	bool caughtException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Betty", 0));
		mStringIntAVL.insert(std::make_pair("Aaron", 1));
		mStringIntAVL.insert(std::make_pair("Carla", 2));
		mIntDoubleAVL.insert(std::make_pair(0, 0.4));
		mIntDoubleAVL.insert(std::make_pair(-1, 0.3));
		mIntDoubleAVL.insert(std::make_pair(1, 11.12));
		mStringIntAVL.remove("Betty");
		mIntDoubleAVL.remove(0);
	}
	catch(std::exception& e)
	{
		caughtException = true;
	}

	ASSERT_FALSE(caughtException);

	StringIntIterator siIter = mStringIntAVL.begin();
	IntDoubleIterator idIter = mIntDoubleAVL.begin();

	EXPECT_EQ(siIter->first, "Aaron");
	EXPECT_EQ(siIter->second, 1);
	EXPECT_EQ(idIter->first, -1);
	EXPECT_EQ(idIter->second, 0.3);
	++siIter;
	++idIter;

	ASSERT_NE(siIter, mStringIntAVL.end());
	ASSERT_NE(idIter, mIntDoubleAVL.end());

	EXPECT_EQ(siIter->first, "Carla");
	EXPECT_EQ(siIter->second, 2);
	EXPECT_EQ(idIter->first, 1);
	EXPECT_EQ(idIter->second, 11.12);
	++siIter;
	++idIter;

	EXPECT_EQ(siIter, mStringIntAVL.end());
	EXPECT_EQ(idIter, mIntDoubleAVL.end());
}

TEST_F(AVLTest, SingleInsertInvalidRemove_15)
{
	bool caughtStringException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Aaron", 0));
		mStringIntAVL.remove("Betty");
	}
	catch(std::exception& e)
	{
		caughtStringException = true;
	}

	bool caughtIntException = false;
	try
	{
		mIntDoubleAVL.insert(std::make_pair(1, 100.5));
		mIntDoubleAVL.remove(20);
	}
	catch(std::exception& e)
	{
		caughtIntException = true;
	}

	ASSERT_TRUE(caughtIntException);
	ASSERT_TRUE(caughtStringException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());

	EXPECT_EQ(mStringIntAVL.begin()->first, "Aaron");
	EXPECT_EQ(mStringIntAVL.begin()->second, 0);
	EXPECT_EQ(mIntDoubleAVL.begin()->first, 1);
	EXPECT_EQ(mIntDoubleAVL.begin()->second, 100.5);
}

TEST_F(AVLTest, SingleInsertDuplicateInsert_16)
{
	bool caughtStringException = false;
	try
	{
		mStringIntAVL.insert(std::make_pair("Aaron", 0));
		mStringIntAVL.insert(std::make_pair("Aaron", 10));
	}
	catch(std::exception& e)
	{
		caughtStringException = true;
	}

	bool caughtIntException = false;
	try
	{
		mIntDoubleAVL.insert(std::make_pair(1, 100.5));
		mIntDoubleAVL.insert(std::make_pair(1, 200.5));
	}
	catch(std::exception& e)
	{
		caughtIntException = true;
	}

	ASSERT_TRUE(caughtIntException);
	ASSERT_TRUE(caughtStringException);

	ASSERT_NE(mStringIntAVL.begin(), mStringIntAVL.end());
	ASSERT_NE(mIntDoubleAVL.begin(), mIntDoubleAVL.end());

	EXPECT_EQ(mStringIntAVL.begin()->first, "Aaron");
	EXPECT_EQ(mStringIntAVL.begin()->second, 0);
	EXPECT_EQ(mIntDoubleAVL.begin()->first, 1);
	EXPECT_EQ(mIntDoubleAVL.begin()->second, 100.5);
}

TEST_F(AVLTest, RandomInsertRemove10Elements_17)
{
	RANDOM_TEST(10, std::string, int, mStringIntAVL, GenerateRandomString(20));
}

TEST_F(AVLTest, RandomInsertRemove100Elements_18)
{
	RANDOM_TEST(100, std::string, int, mStringIntAVL, GenerateRandomString(20));
}

TEST_F(AVLTest, RandomInsertRemove1000Elements_19)
{
	RANDOM_TEST(1000, std::string, int, mStringIntAVL, GenerateRandomString(20));
}
