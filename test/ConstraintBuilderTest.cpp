/*
 * ConstraintBuilderTest.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef CONSTRAINT_BUILDER_TEST
#define CONSTRAINT_BUILDER_TEST

#include "Utility.h"
#include "ConstraintBuilder.h"
#include "gtest/gtest.h"

namespace BioChip {

class ConstraintBuilderTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        module->addShape(Utility::getPointer(new RectangularShape("0", Coord(1, 1, 1))));
        module->addShape(Utility::getPointer(new RectangularShape("1", Coord(1, 1, 2))));
    }

    std::shared_ptr<Grid> grid = Utility::getPointer(new Grid(1, 1, 2));
    ModuleNodePointer module = Utility::getPointer(new RectangularModuleFactory("module"));
    std::shared_ptr<ConstraintBuilder> constraintBuilder;
};

TEST_F(ConstraintBuilderTest, singletonConstraintTest) {
    auto singletonConstraintBuilder = Utility::getPointer(new SingletonConstraintBuilder(module, *grid));
    singletonConstraintBuilder->buildConstraint();

    EXPECT_STREQ("module_0_0_0_0+module_0_0_1_0+module_0_0_0_1=1", singletonConstraintBuilder->getConstraint()->toString().c_str());
}

}

#endif