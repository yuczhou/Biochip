/*
 * GraphNode.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#include "GraphNode.h"

namespace BioChip {

    GraphNode::GraphNode(const std::string name_) : name(name_) {
        // TODO Auto-generated constructor stub
    }

    GraphNode::GraphNode(const char *name_) : name(name_) {
        // TODO Auto-generated constructor stub
    }

    GraphNode::~GraphNode() {
        // TODO Auto-generated destructor stub
    }

    void GraphNode::addChild(NodePointer child) {
        children.add(child);
    }

    void GraphNode::addParent(NodePointer parent) {
        parents.add(parent);
    }

    const GraphNode::NodeList &GraphNode::getChildren() const {
        return children;
    }

    const GraphNode::NodeList &GraphNode::getParents() const {
        return parents;
    }

    const std::string &GraphNode::getName() const {
        return name;
    }

} /* namespace BioChip */
