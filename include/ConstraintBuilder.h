/*
 * ConstraintBuilder.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef CONSTRAINT_BUILDER_H
#define CONSTRAINT_BUILDER_H

#include "Constraint.h"
#include "Qualifier.h"
#include "Iterator.h"
#include "ModuleNode.h"
#include "Grid.h"

namespace BioChip {

typedef Qualifier<Coord> CoordValidator;
typedef std::shared_ptr<CoordValidator> CoordValidatorPointer;

class ConstraintBuilder {
private:
    class GeneralValidator : public CoordValidator {
    private:
        const Coord upperRight;
        const ModuleFactory &moduleNode;
        size_t shape;
    public:
        GeneralValidator(const Coord, const ModuleFactory &, size_t);

        virtual bool operator()(const Coord &) const;
    };

protected:
    const ModuleNodePointer moduleNodePointer;
    const Grid &grid;
protected:
    CoordValidatorPointer getValidator(size_t) const;

    virtual void fixedCoordBuildConstraint(ModulePointer) const = 0;

public:
    ConstraintBuilder(const ModuleNodePointer &, const Grid &);

    void buildConstraint() const;
};

class SingleConstraintGenerator {
protected:
    ConstraintPointer equation;
public:
    SingleConstraintGenerator(ConstraintPointer);

    ConstraintPointer getConstraint() {
        return equation;
    }
};

class SingleEqualityGenerator : public SingleConstraintGenerator {
public:
    SingleEqualityGenerator();
};

class SingleInEqualityGenerator : public SingleConstraintGenerator {
public:
    SingleInEqualityGenerator();
};

class SingletonConstraintBuilder : public ConstraintBuilder, public SingleEqualityGenerator {
protected:
    virtual void fixedCoordBuildConstraint(ModulePointer) const;

public:
    SingletonConstraintBuilder(const ModuleNodePointer &, const Grid &);
};

}
#endif