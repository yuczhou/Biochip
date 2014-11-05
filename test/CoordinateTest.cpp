/*
 * CoordinateTest.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#include "Coordinate.h"
#include "gtest/gtest.h"

namespace BioChip {

TEST(CoordinateTest, constructor) {
    Coord coord(0, 1, 2);

    EXPECT_EQ(0, coord.x);
    EXPECT_EQ(1, coord.y);
    EXPECT_EQ(2, coord.z);
}

TEST(CoordinateTest, equality) {
    EXPECT_EQ(Coord(0, 1, 2), Coord(0, 1, 2));
    EXPECT_NE(Coord(5, 1, 2), Coord(0, 1, 2));
}

TEST(CoordinateTest, comparison) {
    EXPECT_LT(Coord(0, 1, 2), Coord(0, 1, 3));
    EXPECT_LT(Coord(0, 1, 2), Coord(1, 1, 3));
    EXPECT_LT(Coord(0, 1, 2), Coord(0, 2, 3));

    EXPECT_GT(Coord(1, 1, 2), Coord(0, 1, 3));
    EXPECT_GT(Coord(0, 1, 2), Coord(0, 0, 3));
    EXPECT_GT(Coord(0, 1, 2), Coord(0, 1, 1));
}

}
