/*
 * FormulateILPTest.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */
#ifndef FORMULATE_ILP_TEST
#define FORMULATE_ILP_TEST

#include "Utility.h"
#include "FormulateILP.h"
#include "gtest/gtest.h"

namespace BioChip {

    class FormulateILPTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            ModuleNodePointer module = Utility::getPointer(new RectangularModuleFactory("module1"));
            module->addShape(Utility::getPointer(new RectangularShape("0", Coord(1, 1, 1))));
            module->addShape(Utility::getPointer(new RectangularShape("1", Coord(1, 1, 2))));
            graph->add(module);
        }

        std::shared_ptr<DirectedAcyclicGraph> graph = Utility::getPointer(new DirectedAcyclicGraph());
        std::shared_ptr<Grid> grid = Utility::getPointer(new Grid(1, 1, 2));
    };

    TEST_F(FormulateILPTest, testSingletonConstraint) {
        auto command = Utility::getPointer(new SingletonConstraintFormulateCommand(*graph, *grid));
        auto equations = command->formulate();
        std::set<std::string> equationStrings;
        for (auto equation : *equations) {
            equationStrings.insert(equation->toString());
        }
        EXPECT_EQ(1, equationStrings.size());
        EXPECT_TRUE(equationStrings.find("module1_0_0_0_0+module1_0_0_1_0+module1_0_0_0_1=1") != equationStrings.end());
    }

    TEST_F(FormulateILPTest, testNonOverlappingConstraint) {
        ModuleNodePointer module = Utility::getPointer(new RectangularModuleFactory("module2"));
        module->addShape(Utility::getPointer(new RectangularShape("0", Coord(1, 1, 1))));
        graph->add(module);

        auto command = Utility::getPointer(new NonOverlappingConstraintFormulateCommand(*graph, *grid));
        auto equations = command->formulate();
        std::set<std::string> equationStrings;
        for (auto equation : *equations) {
            equationStrings.insert(equation->toString());
        }
        EXPECT_EQ(2, equationStrings.size());
        EXPECT_TRUE(equationStrings.find("module1_0_0_0_0+module1_0_0_0_1+module2_0_0_0_0<=1") != equationStrings.end());
        EXPECT_TRUE(equationStrings.find("module1_0_0_1_0+module1_0_0_0_1+module2_0_0_1_0<=1") != equationStrings.end());
    }

}

#endif