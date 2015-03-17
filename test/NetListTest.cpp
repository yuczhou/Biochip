/*
 * NetTest.cpp
 *
 *  Created on: Mar 17, 2014
 *      Author: yuczhou
 */
#ifndef NET_TEST
#define NET_TEST

#include "Net.h"
#include "Utility.h"
#include "gtest/gtest.h"

namespace BioChip {

    class NetListTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            ModuleNodePointer module1 = Utility::getPointer(new RectangularModuleFactory("module1"));
            module1->addShape(Utility::getPointer(new RectangularShape("0", Coord(1, 1, 1))));
            module1->addShape(Utility::getPointer(new RectangularShape("1", Coord(1, 1, 2))));
            graph.add(module1);
            ModuleNodePointer module2 = Utility::getPointer(new RectangularModuleFactory("module2"));
            module2->addShape(Utility::getPointer(new RectangularShape("0", Coord(1, 1, 1))));
            graph.add(module2);
            ModuleNodePointer module3 = Utility::getPointer(new RectangularModuleFactory("module3"));
            module3->addShape(Utility::getPointer(new RectangularShape("0", Coord(1, 1, 3))));
            module3->addShape(Utility::getPointer(new RectangularShape("1", Coord(1, 2, 3))));
            module3->addShape(Utility::getPointer(new RectangularShape("2", Coord(2, 2, 3))));
            graph.add(module3);
            ModuleNodePointer module4 = Utility::getPointer(new RectangularModuleFactory("module4"));
            module4->addShape(Utility::getPointer(new RectangularShape("0", Coord(1, 1, 4))));
            graph.add(module4);

            auto node1 = std::dynamic_pointer_cast<GraphNode>(module1);
            auto node2 = std::dynamic_pointer_cast<GraphNode>(module2);
            auto node3 = std::dynamic_pointer_cast<GraphNode>(module3);
            auto node4 = std::dynamic_pointer_cast<GraphNode>(module4);

            node1->addChild(node3);
            node2->addChild(node3);
            node3->addParent(node1);
            node3->addParent(node2);
            node3->addChild(node4);
            node4->addParent(node3);

            Coord coord;
            int shape = 0;
            placementMap->insert(std::make_pair(node1->getName(), SingleModulePlacement(coord, shape)));
            coord = Coord(1, 1, 0);
            placementMap->insert(std::make_pair(node2->getName(), SingleModulePlacement(coord, shape)));
            coord = Coord(1, 1, 2);
            shape = 2;
            placementMap->insert(std::make_pair(node3->getName(), SingleModulePlacement(coord, shape)));
            coord = Coord(2, 2, 5);
            shape = 0;
            placementMap->insert(std::make_pair(node4->getName(), SingleModulePlacement(coord, shape)));

        }

        DirectedAcyclicGraph graph;
        ptr(ModulePlacement) placementMap = Utility::getPointer(new ModulePlacement());
    };

    TEST_F(NetListTest, createNetListTest) {
        auto netList = NetListFactory::getInstance().createNetList(graph, placementMap);
        EXPECT_EQ(2, netList->getNetList().size());
        EXPECT_EQ(3, netList->getNetList().at(0)->getNumberOfPins());
        EXPECT_EQ(2, netList->getNetList().at(1)->getNumberOfPins());
    }

}

#endif