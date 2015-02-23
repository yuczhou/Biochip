/*
 * ContainerTest.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#include "GraphNode.h"
#include "Utility.h"
#include "gtest/gtest.h"

namespace BioChip {

    TEST(GraphNodeTest, constructor) {
        GraphNode node("node_test");
        EXPECT_STREQ("node_test", node.getName().c_str());
    }

    TEST(GraphNodeTest, addParent) {
        GraphNode node(std::string("node_test"));

        auto parent = Utility::getPointer(new GraphNode("parent1"));
        node.addParent(parent);
        EXPECT_TRUE(node.getParents().contains(parent));
    }

    TEST(GraphNodeTest, addChild) {
        GraphNode node(std::string("node_test"));

        auto child1 = Utility::getPointer(new GraphNode("child1"));
        auto child2 = Utility::getPointer(new GraphNode("child2"));
        node.addChild(child1);
        node.addChild(child2);
        EXPECT_TRUE(node.getChildren().contains(child1));
        EXPECT_TRUE(node.getChildren().contains(child2));
    }

} /* namespace BioChip */
