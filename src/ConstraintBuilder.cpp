/*
 * ConstraintBuilder.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef CONSTRAINT_BUILDER_CPP
#define CONSTRAINT_BUILDER_CPP

#include "Utility.h"
#include "ConstraintBuilder.h"

namespace BioChip {

ConstraintBuilder::ConstraintBuilder(const ModuleNodePointer &moduleNodePointer_, const Grid &grid_)
        : moduleNodePointer(moduleNodePointer_), grid(grid_) {
}

ConstraintBuilder::GeneralValidator::GeneralValidator(const Coord upperRight_, const ModuleFactory &moduleNode_, size_t shape_)
        : upperRight(upperRight_), moduleNode(moduleNode_), shape(shape_) {
}

bool ConstraintBuilder::GeneralValidator::operator()(const Coord &coord) const {
    return moduleNode.createModule(shape, coord)->isValid(upperRight);
}

void ConstraintBuilder::buildConstraint() const {
    for (size_t shape = 0; shape < moduleNodePointer->numOfShapes(); ++shape) {
        auto validator = getValidator(shape);
        auto gridIterator = grid.getIterator(*validator);
        while (gridIterator->hasNext()) {
            fixedCoordBuildConstraint(moduleNodePointer->createModule(shape, gridIterator->next()));
        }
    }
}

CoordValidatorPointer ConstraintBuilder::getValidator(size_t shape) const {
    return Utility::getPointer(new GeneralValidator(grid.getUpperRight(), *moduleNodePointer, shape));
}

SingleConstraintGenerator::SingleConstraintGenerator(ConstraintPointer equation_) : equation(equation_) {
}

SingleEqualityGenerator::SingleEqualityGenerator()
        : SingleConstraintGenerator(Utility::getPointer(new EqualityConstraint())) {
}

SingleInEqualityGenerator::SingleInEqualityGenerator()
        : SingleConstraintGenerator(Utility::getPointer(new InEqualityConstraint())) {
}

SingletonConstraintBuilder::SingletonConstraintBuilder(const ModuleNodePointer &moduleNode_, const Grid &grid_)
        : ConstraintBuilder(moduleNode_, grid_) {
}

void SingletonConstraintBuilder::fixedCoordBuildConstraint(ModulePointer module) const {
    equation->addVariable(module);
}

}
#endif