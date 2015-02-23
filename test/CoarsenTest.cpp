/*
 * CoarsenTest.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */
#ifndef COARSEN_TEST_CPP
#define COARSEN_TEST_CPP

#include "Coarsen.h"
#include "gtest/gtest.h"

namespace BioChip {

    TEST(CoarsenTest, testCommon) {
        Coarsen coarsen(Coord(5, 5, 120));
        EXPECT_EQ(Coord(1, 1, 12), coarsen.createGranularity());
    }

    TEST(CoarsenTest, testSmallCase) {
        Coarsen coarsen(Coord(3, 3, 120));
        EXPECT_EQ(Coord(1, 1, 12), coarsen.createGranularity());
    }

}

#endif