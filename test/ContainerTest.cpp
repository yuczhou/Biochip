/*
 * ContainerTest.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#include "Container.h"
#include "gtest/gtest.h"

namespace BioChip {

class ContainerTest: public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 1; i <= 3; ++i) {
			arrayList.add(i);
			linkedList.add(i);
			hashSet.add(i);
		}
	}

	ArrayList<int> arrayList;
	LinkedList<int> linkedList;
	HashSet<int> hashSet;
};

TEST_F(ContainerTest, arrayListIterator) {
	auto iterator = arrayList.getIterator();

	EXPECT_TRUE(iterator->hasNext());
	EXPECT_EQ(1, iterator->next());

	EXPECT_TRUE(iterator->hasNext());
	EXPECT_EQ(2, iterator->next());

	EXPECT_TRUE(iterator->hasNext());
	EXPECT_EQ(3, iterator->next());

	EXPECT_FALSE(iterator->hasNext());
}

TEST_F(ContainerTest, linkedListIterator) {
	auto iterator = linkedList.getIterator();

	EXPECT_TRUE(iterator->hasNext());
	EXPECT_EQ(1, iterator->next());

	EXPECT_TRUE(iterator->hasNext());
	EXPECT_EQ(2, iterator->next());

	EXPECT_TRUE(iterator->hasNext());
	EXPECT_EQ(3, iterator->next());

	EXPECT_FALSE(iterator->hasNext());
}

TEST_F(ContainerTest, defaultIteratorArray) {
	int count = 1;
	for (auto &element : arrayList) {
		EXPECT_EQ(count++, element);
	}
}

TEST_F(ContainerTest, defaultIteratorList) {
	int count = 1;
	for (auto &element : linkedList) {
		EXPECT_EQ(count++, element);
	}
}

} /* namespace BioChip */
