#include "gtest/gtest.h"

#include <iostream>
#include <sstream>
#include <queue> 
#include <vector>
#include <algorithm>

class STLTest : public testing::Test {
protected:
	STLTest() {
	}

	virtual ~STLTest() {
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(STLTest, PriorityQueue) {
	// EDIT HERE
	std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int> >, /* YOUR COMPARATOR */> pq;

	// DO NOT TOUCH BEYOND HERE
	pq.push(std::make_pair(100,212));
	pq.push(std::make_pair(30,2));
	pq.push(std::make_pair(40,222));
	pq.push(std::make_pair(15,26));
	pq.push(std::make_pair(10,62));
	pq.push(std::make_pair(1,42));
	pq.push(std::make_pair(41,12));
	pq.push(std::make_pair(33,23));
	pq.push(std::make_pair(14,24));
	pq.push(std::make_pair(58,22));
	pq.push(std::make_pair(30,21));

	int prev = 0;
	while(!pq.empty()) {
		EXPECT_TRUE(prev < pq.top().second);
		prev = pq.top().second;
		pq.pop();
	}
}

TEST_F(STLTest, Algorithm) {
	// DO NOT TOUCH
	std::vector<int> vec;
	for (int i = 0; i < 50; i++) {
		vec.push_back(i);
	}

	// EDIT HERE
	// remove() one-liner

	// DO NOT TOUCH BEYOND HERE
	for (unsigned int i = 0; i < vec.size(); i++) {
		EXPECT_TRUE(vec[i] % 3);
		EXPECT_TRUE(vec[i] % 5);
	}
}

TEST_F(STLTest, Reverse) {
	// DO NOT TOUCH
	std::vector<int> vec;
	for (int i = 0; i < 50; i++) {
		vec.push_back(i);
	}

	// EDIT HERE
	std::vector<int> rvec; 

	// DO NOT TOUCH BEYOND HERE
	for (int i = 0; i < 50; i++) {
		EXPECT_EQ(49 - i, rvec[i]);
		EXPECT_EQ(i, vec[i]);
	}
}