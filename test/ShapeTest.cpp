/*
 * ShapeTest.cpp
 *
 *  Created on: Oct 29, 2014
 *      Author: yuczhou
 */
#ifndef SHAPE_TEST
#define SHAPE_TEST

#include "Shape.h"
#include "Utility.h"
#include "gtest/gtest.h"

namespace BioChip {

TEST(ShapeTest, constructor) {
    auto shapePointer = Utility::getPointer(new RectangularShape(std::string("name"), Coord(1, 2, 3)));
    EXPECT_EQ(Coord(1, 2, 3), shapePointer->getDimension());
}

TEST(ShapeTest, validity) {
    auto shapePointer = Utility::getPointer(new RectangularShape(std::string("name"), Coord(1, 2, 3)));
    EXPECT_TRUE(shapePointer->isValid(Coord::origin, Coord(1, 2, 3)));
}

TEST(ShapeTest, toString) {
    auto shapePointer = Utility::getPointer(new RectangularShape(std::string("name"), Coord(1, 2, 3)));
    EXPECT_STREQ("name", shapePointer->toString().c_str());
}

}

#endif
