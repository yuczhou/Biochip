/*
 * ModuleNodeTest.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */
#ifndef MODULE_NODE_TEST
#define MODULE_NODE_TEST

#include "ModuleNode.h"
#include "Utility.h"
#include "gtest/gtest.h"

namespace BioChip {

TEST(ModuleNodeTest, createModule) {
    auto moduleFactory = Utility::getPointer(new RectangularModuleFactory("test_factory"));
    moduleFactory->addShape(Utility::getPointer(new RectangularShape(std::string("shape1"), Coord(1, 2, 3))));
    moduleFactory->addShape(Utility::getPointer(new RectangularShape(std::string("shape2"), Coord(2, 3, 4))));

    auto firstModule = moduleFactory->createModule(0, Coord::origin);
    EXPECT_STREQ("test_factory", firstModule->getName().c_str());
    EXPECT_EQ(Coord(1, 2, 3), firstModule->getShape()->getDimension());
    EXPECT_EQ(Coord::origin, firstModule->getLowerLeft());
    EXPECT_STREQ("test_factory_0_0_0_shape1", firstModule->toString().c_str());

    auto secondModule = moduleFactory->createModule(1, Coord(1, 1, 1));
    EXPECT_STREQ("test_factory", secondModule->getName().c_str());
    EXPECT_EQ(Coord(2, 3, 4), secondModule->getShape()->getDimension());
    EXPECT_EQ(Coord(1, 1, 1), secondModule->getLowerLeft());
    EXPECT_STREQ("test_factory_1_1_1_shape2", secondModule->toString().c_str());
}

} /* namespace BioChip */

#endif
