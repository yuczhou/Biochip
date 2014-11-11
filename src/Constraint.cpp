/*
 * Constraint.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef CONSTRAINT_CPP
#define CONSTRAINT_CPP

#include "Constraint.h"

namespace BioChip {

std::string Constraint::toString() const {
    std::string ret;
    for (auto modulePointer : modules) {
        ret += modulePointer->toString() + "+";
    }
    ret.pop_back();
    return ret + toStringRHS();
}

void Constraint::addVariable(ModulePointer module) {
    modules.add(module);
}

std::string EqualityConstraint::toStringRHS() const {
    return "=1";
}

std::string InEqualityConstraint::toStringRHS() const {
    return "<=1";
}

}

#endif