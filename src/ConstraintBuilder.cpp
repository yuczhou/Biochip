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

    GeneralValidator::GeneralValidator(const Coord upperRight_, const ModuleFactory &moduleNode_, size_t shape_)
            : upperRight(upperRight_), moduleNode(moduleNode_), shape(shape_) {
    }

    bool GeneralValidator::operator()(const Coord &coord) const {
        return moduleNode.createModule(shape, coord)->isValid(upperRight);
    }

    const std::shared_ptr<LinkedList<ConstraintPointer> > &ConstraintBuilder::buildConstraint() {
        for (size_t shape = 0; shape < moduleNodePointer->numOfShapes(); ++shape) {
            auto validator = getValidator(shape);
            auto gridIterator = grid.getIterator(*validator);
            while (gridIterator->hasNext()) {
                fixedCoordBuildConstraint(moduleNodePointer->createModule(shape, gridIterator->next()));
            }
        }
        postBuildEquations();
        return equations;
    }

    void ConstraintBuilder::postBuildEquations() {
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

    void SingletonConstraintBuilder::postBuildEquations() {
        equations->add(getConstraint());
    }

    void SingletonConstraintBuilder::fixedCoordBuildConstraint(ModulePointer module) {
        equation->addVariable(module);
    }

    PrecedenceConstraintBuilder::PrecedenceConstraintBuilder(const ModuleNodePointer &moduleNode_, const Grid &grid_)
            : ConstraintBuilder(moduleNode_, grid_) {
    }

    PrecedenceConstraintBuilder::FixedNeighborConstraintBuilder::FixedNeighborConstraintBuilder(const ModuleNodePointer &moduleNode_, const Grid &grid_, const ModulePointer &root_)
            : ConstraintBuilder(moduleNode_, grid_), root(root_) {
    }

    void PrecedenceConstraintBuilder::FixedNeighborConstraintBuilder::fixedCoordBuildConstraint(ModulePointer module) {
        equation->addVariable(module);
    }

    CoordValidatorPointer PrecedenceConstraintBuilder::FixedNeighborConstraintBuilder::getValidator(size_t shape) const {
        return Utility::getPointer(new PrecedenceValidator(grid.getUpperRight(), *moduleNodePointer, shape, root));
    }

    PrecedenceConstraintBuilder::FixedNeighborConstraintBuilder::PrecedenceValidator::PrecedenceValidator(const Coord upperRight_, const ModuleFactory &moduleNode_, size_t shape_, const ModulePointer &root_)
            : GeneralValidator(upperRight_, moduleNode_, shape_), root(root_) {
    }

    bool PrecedenceConstraintBuilder::FixedNeighborConstraintBuilder::PrecedenceValidator::operator()(const Coord &coord) const {
        return root->isValid(upperRight) && coord.z <= root->getCompletionTime() + 1 && moduleNode.createModule(shape, coord)->isValid(upperRight);
    }

    void PrecedenceConstraintBuilder::fixedCoordBuildConstraint(ModulePointer module) {
        for (auto childNode : std::dynamic_pointer_cast<GraphNode>(moduleNodePointer)->getChildren()) {
            FixedNeighborConstraintBuilder precedenceConstraint(std::dynamic_pointer_cast<ModuleFactory>(childNode), grid, module);
            precedenceConstraint.buildConstraint();
            auto equation = precedenceConstraint.getConstraint();
            if (!equation->isEmpty()) {
                equation->addVariable(module);
                equations->add(equation);
            }
        }
    }

    NonOverlappingConstraintBuilder::NonOverlappingConstraintBuilder(const ModuleNodePointer &moduleNode_, const Grid &grid_, std::map<Coord, ConstraintPointer> &overlapMap_)
            : ConstraintBuilder(moduleNode_, grid_), overlapMap(overlapMap_) {
    }

    void NonOverlappingConstraintBuilder::fixedCoordBuildConstraint(ModulePointer module) {
        Coord lowerLeft = module->getLowerLeft();
        Coord dimension = module->getShape()->getDimension();
        for (int x = lowerLeft.x; x < lowerLeft.x + dimension.x; ++x) {
            for (int y = lowerLeft.y; y < lowerLeft.y + dimension.y; ++y) {
                for (int t = lowerLeft.z; t < lowerLeft.z + dimension.z; ++t) {
                    Coord coord(x, y, t);
                    if (overlapMap.find(coord) == overlapMap.end()) {
                        overlapMap[coord] = Utility::getPointer(new InEqualityConstraint());
                    }
                    overlapMap[coord]->addVariable(module);
                }
            }
        }
    }

}
#endif