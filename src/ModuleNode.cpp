/*
 * ModuleNode.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef MODULENODE_CPP_
#define MODULENODE_CPP_

#include <Utility.h>
#include "ModuleNode.h"

namespace BioChip {

// Module Factory
ModuleFactory::ModuleFactory(const char *name_) : name(name_) {
}

ModuleFactory::~ModuleFactory() {
}

ModulePointer ModuleFactory::createModule(size_t shapeIndex, Coord lowerLeft) const {
    return Utility::getPointer(new Module(name.c_str(), lowerLeft, this->createShape(shapeIndex)));
}

void ModuleFactory::addShape(ShapePointer shape) {
    this->shapes.add(shape);
}

// Rectangular Module Factory
RectangularModuleFactory::RectangularModuleFactory(const char *name_) : GraphNode(name_), ModuleFactory(name_) {
}

RectangularModuleFactory::~RectangularModuleFactory() {
}

ShapePointer RectangularModuleFactory::createShape(size_t index) const {
    return this->shapes.at(index);
}

}

#endif