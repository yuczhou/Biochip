/*
 * ModuleNodeTest.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */
#ifndef PARSER_TEST
#define PARSER_TEST

#include "Parser.h"
#include "gtest/gtest.h"

namespace BioChip {

    class ParserTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            // TODO: refactor this hard coding file path thing
            // http://stackoverflow.com/questions/7900661/how-to-read-a-cmake-variable-in-c-source-code
            parser = Utility::getPointer(new Parser("/home/yuczhou/projects/Biochip/test/testcase.txt", graph));
        }

        DirectedAcyclicGraph graph;
        LinkedList<ModuleNodePointer> modules;
        std::shared_ptr<Parser> parser;
    };

    TEST_F(ParserTest, testGridSize) {
        parser->parse();
        EXPECT_EQ(Coord(5, 5, 120), parser->getGridSize());
    }

    TEST_F(ParserTest, testModuleGeneration) {
        parser->parse();
        EXPECT_EQ(36, graph.size());

        std::set<Coord> plasmaSample01;
        std::set<Coord> plasmaMix01;
        for (auto moduleFactory : graph) {
            for (size_t shape = 0; shape < moduleFactory->numOfShapes(); ++shape) {
                auto fixedModule = moduleFactory->createModule(shape, Coord::origin);
                if (fixedModule->getName() == "PlasmaSample01") {
                    plasmaSample01.insert(fixedModule->getShape()->getDimension());
                }
                if (fixedModule->getName() == "PlasmaMix01") {
                    plasmaMix01.insert(fixedModule->getShape()->getDimension());
                }
            }
        }
        EXPECT_TRUE(plasmaSample01.find(Coord(0, 0, 2)) != plasmaSample01.end());
        EXPECT_EQ(1, plasmaSample01.size());

        EXPECT_TRUE(plasmaMix01.find(Coord(2, 2, 10)) != plasmaMix01.end());
        EXPECT_TRUE(plasmaMix01.find(Coord(1, 4, 5)) != plasmaMix01.end());
        EXPECT_TRUE(plasmaMix01.find(Coord(2, 4, 3)) != plasmaMix01.end());
        EXPECT_TRUE(plasmaMix01.find(Coord(2, 3, 6)) != plasmaMix01.end());
        EXPECT_EQ(4, plasmaMix01.size());
    }

    TEST_F(ParserTest, testModulePrecedence) {
        parser->parse();

        std::set<std::string> children;
        std::set<std::string> parents;
        for (auto moduleFactory : graph) {
            auto fixedModule = std::dynamic_pointer_cast<GraphNode>(moduleFactory);
            if (fixedModule->getName() != "PlasmaMix01") {
                continue;
            }
            for (auto child : fixedModule->getChildren()) {
                children.insert(child->getName());
            }
            for (auto parent : fixedModule->getParents()) {
                parents.insert(parent->getName());
            }
        }

        EXPECT_TRUE(parents.find("PlasmaSample01") != parents.end());
        EXPECT_TRUE(parents.find("GlucoseReagent01") != parents.end());
        EXPECT_TRUE(children.find("OptGlucose01") != children.end());
        EXPECT_EQ(2, parents.size());
        EXPECT_EQ(1, children.size());
    }

}

#endif