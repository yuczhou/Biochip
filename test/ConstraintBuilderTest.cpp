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
        std::shared_ptr<RectangularModuleFactory> module = Utility::getPointer(new RectangularModuleFactory("module"));
        std::shared_ptr<ConstraintBuilder> constraintBuilder;
    };

    TEST_F(ConstraintBuilderTest, singletonConstraintTest) {
        auto singletonConstraintBuilder = Utility::getPointer(new SingletonConstraintBuilder(module, *grid));
        singletonConstraintBuilder->buildConstraint();
        EXPECT_TRUE(singletonConstraintBuilder->getConstraint()->getIsEqualityConstraint());
        EXPECT_STREQ("module_0_0_0_0+module_0_0_1_0+module_0_0_0_1=1", singletonConstraintBuilder->getConstraint()->toString().c_str());
    }

    TEST_F(ConstraintBuilderTest, precedenceConstraintTest) {
        std::shared_ptr<RectangularModuleFactory> childOne = Utility::getPointer(new RectangularModuleFactory("childOne"));
        childOne->addShape(Utility::getPointer(new RectangularShape("0", Coord(1, 1, 1))));

        std::shared_ptr<RectangularModuleFactory> childTwo = Utility::getPointer(new RectangularModuleFactory("childTwo"));
        childTwo->addShape(Utility::getPointer(new RectangularShape("0", Coord(1, 1, 1))));

        module->addChild(childOne);
        module->addChild(childTwo);
        auto precedenceConstraintBuilder = Utility::getPointer(new PrecedenceConstraintBuilder(module, *grid));
        auto constraints = precedenceConstraintBuilder->buildConstraint();

        std::set<std::string> equations;
        for (auto constraint : *constraints) {
            EXPECT_FALSE(constraint->getIsEqualityConstraint());
            equations.insert(constraint->toString());
        }

        EXPECT_EQ(6, equations.size());
        EXPECT_TRUE(equations.find("childOne_0_0_0_0+childOne_0_0_1_0+module_0_0_0_0<=1") != equations.end());
        EXPECT_TRUE(equations.find("childTwo_0_0_0_0+childTwo_0_0_1_0+module_0_0_0_0<=1") != equations.end());
        EXPECT_TRUE(equations.find("childOne_0_0_0_0+childOne_0_0_1_0+module_0_0_1_0<=1") != equations.end());
        EXPECT_TRUE(equations.find("childTwo_0_0_0_0+childTwo_0_0_1_0+module_0_0_1_0<=1") != equations.end());
        EXPECT_TRUE(equations.find("childOne_0_0_0_0+childOne_0_0_1_0+module_0_0_0_1<=1") != equations.end());
        EXPECT_TRUE(equations.find("childTwo_0_0_0_0+childTwo_0_0_1_0+module_0_0_0_1<=1") != equations.end());
    }

}

#endif