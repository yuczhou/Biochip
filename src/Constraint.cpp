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

    LinkedList<ModulePointer> &Constraint::getModules() {
        return modules;
    }

    const LinkedList<ModulePointer> &Constraint::getModules() const {
        return modules;
    }

    Constraint::Constraint(bool isEqualityConstraint_) : isEqualityConstraint(isEqualityConstraint_) {
    }

    std::string Constraint::toString() const {
        if (modules.size() == 0) {
            return "";
        }
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

    bool Constraint::isEmpty() const {
        return modules.size() == 0;
    }

    bool Constraint::getIsEqualityConstraint() const {
        return isEqualityConstraint;
    }

    EqualityConstraint::EqualityConstraint() : Constraint(true) {
    }

    InEqualityConstraint::InEqualityConstraint() : Constraint(false) {
    }

    std::string EqualityConstraint::toStringRHS() const {
        return "=1";
    }

    std::string InEqualityConstraint::toStringRHS() const {
        return "<=1";
    }

}

#endif