/*
 * ConstraintTest.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */
#ifndef CONSTRAINT_TEST_CPP
#define CONSTRAINT_TEST_CPP

#include "Constraint.h"
#include "ModuleNode.h"
#include "Utility.h"
#include "gtest/gtest.h"

namespace BioChip {

    class EqualityTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            moduleFactory->addShape(Utility::getPointer(new RectangularShape(std::string("shape1"), Coord(1, 2, 3))));
            moduleFactory->addShape(Utility::getPointer(new RectangularShape(std::string("shape2"), Coord(2, 3, 4))));
        }

        std::shared_ptr<ModuleFactory> moduleFactory = Utility::getPointer(new RectangularModuleFactory("test_factory"));
    };

    TEST_F(EqualityTest, equalityToStringTest) {
        EqualityConstraint equation;
        equation.addVariable(moduleFactory->createModule(0, Coord::origin));
        equation.addVariable(moduleFactory->createModule(1, Coord(1, 1, 1)));

        EXPECT_STREQ("test_factory_0_0_0_shape1+test_factory_1_1_1_shape2=1", equation.toString().c_str());
    }

    TEST_F(EqualityTest, inequalityToStringTest) {
        InEqualityConstraint equation;
        equation.addVariable(moduleFactory->createModule(0, Coord::origin));
        equation.addVariable(moduleFactory->createModule(1, Coord(1, 1, 1)));

        EXPECT_STREQ("test_factory_0_0_0_shape1+test_factory_1_1_1_shape2<=1", equation.toString().c_str());
    }
}

#endif