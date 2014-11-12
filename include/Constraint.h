/*
 * Constraint.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "Module.h"
#include "Container.h"

namespace BioChip {

class Constraint {
private:
    LinkedList<ModulePointer> modules;
protected:
    virtual std::string toStringRHS() const = 0;

public:
    std::string toString() const;

    void addVariable(ModulePointer module);
};

class EqualityConstraint : public Constraint {
protected:
    virtual std::string toStringRHS() const;
};

class InEqualityConstraint : public Constraint {
protected:
    virtual std::string toStringRHS() const;
};

typedef std::shared_ptr<Constraint> ConstraintPointer;

}

#endif