/*
 * ILPSolveTest.cpp
 *
 *  Created on: Feb 21, 2014
 *      Author: yuczhou
 */
#ifndef ILP_SOLVE_TEST
#define ILP_SOLVE_TEST

#include "Utility.h"
#include "LpSolve.h"
#include "Algorithm.h"
#include "gtest/gtest.h"

namespace BioChip {

    class ILPSolveTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            ModuleNodePointer module1 = Utility::getPointer(new RectangularModuleFactory("module1"));
            module1->addShape(Utility::getPointer(new RectangularShape("0", Coord(1, 1, 1))));
            module1->addShape(Utility::getPointer(new RectangularShape("1", Coord(1, 1, 2))));
            graph->add(module1);
            ModuleNodePointer module2 = Utility::getPointer(new RectangularModuleFactory("module2"));
            module2->addShape(Utility::getPointer(new RectangularShape("0", Coord(1, 1, 1))));
            graph->add(module2);

            auto nonOverlap = Utility::getPointer(new NonOverlappingConstraintFormulateCommand(*graph, *grid));
            nonOverlapEquations = nonOverlap->formulate();
            auto single = Utility::getPointer(new SingletonConstraintFormulateCommand(*graph, *grid));
            singleEquations = single->formulate();
        }

        std::shared_ptr<DirectedAcyclicGraph> graph = Utility::getPointer(new DirectedAcyclicGraph());
        std::shared_ptr<Grid> grid = Utility::getPointer(new Grid(1, 1, 2));
        std::shared_ptr<LinkedList<ConstraintPointer> > nonOverlapEquations;
        std::shared_ptr<LinkedList<ConstraintPointer> > singleEquations;
    };

    TEST_F(ILPSolveTest, solvableTest) {
        auto equations = Utility::getPointer(new LinkedList<ConstraintPointer>());
        equations->addAll(*nonOverlapEquations);
        equations->addAll(*singleEquations);
        std::map<std::string, int> moduleIndexMap;
        int count = 0;
        for (auto const& equation : *equations) {
            for (auto const& module : equation->getModules()) {
                if (moduleIndexMap.find(module->toString()) == moduleIndexMap.end()) {
                    moduleIndexMap[module->toString()] = count++;
                }
            }
        }
        LpSolve lp(*equations, moduleIndexMap);
        EXPECT_TRUE(lp.solve());

        auto placement = lp.getPlacement();
        EXPECT_TRUE(placement->find("module1") != placement->end());
        EXPECT_TRUE(placement->find("module2") != placement->end());
        EXPECT_EQ(0, placement->at("module1").shape);
        EXPECT_EQ(0, placement->at("module2").shape);
    }

}

#endif