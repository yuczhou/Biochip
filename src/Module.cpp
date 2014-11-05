/*
 * Module.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */
#ifndef MODULE_CPP
#define MODULE_CPP

#include "Module.h"

namespace BioChip {

Module::Module(char const *name_, Coord lowerLeft_, ShapePointer shape_)
        : name(name_), lowerLeft(lowerLeft_), shape(shape_) {
}

} /* namespace BioChip */

#endif
