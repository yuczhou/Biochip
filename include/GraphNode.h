/*
 * GraphNode.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include "Container.h"

namespace BioChip {

class GraphNode {
private:
    typedef std::shared_ptr<GraphNode> NodePointer;
    typedef LinkedList<NodePointer> NodeList;
    NodeList parents;
    NodeList children;
    const std::string name;
public:
    GraphNode(std::string);

    GraphNode(const char *);

    virtual ~GraphNode();

    void addChild(NodePointer);

    void addParent(NodePointer);

    const NodeList &getChildren() const;

    const NodeList &getParents() const;

    const std::string &getName() const;
};

} /* namespace BioChip */

#endif /* GRAPHNODE_H_ */
