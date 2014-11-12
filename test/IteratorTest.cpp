/*
 * ContainerTest.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#include "Container.h"
#include "gtest/gtest.h"

namespace BioChip {

class OddQualifier : public Qualifier<int> {
public:
    virtual bool operator()(const int &element) const override {
        return element & 1;
    }
};

class NegativeQualifier : public Qualifier<int> {
public:
    virtual bool operator()(const int &element) const override {
        return element < 0;
    }
};

class IteratorTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        for (int i = 10; i <= 15; ++i) {
            arrayList.add(i);
            linkedList.add(i);
        }
    }

    ArrayList<int> arrayList;
    LinkedList<int> linkedList;
    OddQualifier qualifier;
};

TEST_F(IteratorTest, arrayListConstConditionIterator) {
    const ArrayList<int> &constArrayList = arrayList;
    auto iterator = constArrayList.getIterator(qualifier);

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(11, iterator->next());

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(13, iterator->next());

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(15, iterator->next());

    EXPECT_FALSE(iterator->hasNext());
}

TEST_F(IteratorTest, arrayListConditionIterator) {
    auto iterator = arrayList.getIterator(qualifier);

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(11, iterator->next());

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(13, iterator->next());

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(15, iterator->next());

    EXPECT_FALSE(iterator->hasNext());
}

TEST_F(IteratorTest, linkedListConstConditionIterator) {
    const LinkedList<int> &constArrayList = linkedList;
    auto iterator = constArrayList.getIterator(qualifier);

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(11, iterator->next());

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(13, iterator->next());

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(15, iterator->next());

    EXPECT_FALSE(iterator->hasNext());
}

TEST_F(IteratorTest, linkedListConditionIterator) {
    auto iterator = linkedList.getIterator(qualifier);

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(11, iterator->next());

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(13, iterator->next());

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(15, iterator->next());

    EXPECT_FALSE(iterator->hasNext());
}

TEST_F(IteratorTest, positiveQualifierTest) {
    linkedList.add(-1);
    linkedList.add(2);
    linkedList.add(-2);

    NegativeQualifier negativeQuailfier;
    auto iterator = linkedList.getIterator(negativeQuailfier);

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(-1, iterator->next());

    EXPECT_TRUE(iterator->hasNext());
    EXPECT_EQ(-2, iterator->next());

    EXPECT_FALSE(iterator->hasNext());
}

} /* namespace BioChip */
