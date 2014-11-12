/*
 * ModuleNode.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef MODULENODE_H_
#define MODULENODE_H_

#include "GraphNode.h"
#include "Module.h"

namespace BioChip {

class ModuleFactory {
private:
    typedef ArrayList<ShapePointer> ShapeList;
    const std::string name;
protected:
    ShapeList shapes;

    virtual ShapePointer createShape(size_t) const = 0;

public:
    ModulePointer createModule(size_t, Coord) const;

    ModuleFactory(const char *);

    virtual ~ModuleFactory();

    void addShape(ShapePointer);

    size_t numOfShapes() const;
};

class RectangularModuleFactory : public GraphNode, public ModuleFactory {
protected:
    virtual ShapePointer createShape(size_t) const;

public:
    RectangularModuleFactory(const char *);

    virtual ~RectangularModuleFactory();
};

typedef std::shared_ptr<ModuleFactory> ModuleNodePointer;

}

#endif