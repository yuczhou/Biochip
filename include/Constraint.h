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
        bool isEqualityConstraint;
    protected:
        virtual std::string toStringRHS() const = 0;

    public:
        Constraint(bool);

        std::string toString() const;

        void addVariable(ModulePointer module);

        LinkedList<ModulePointer> &getModules();

        const LinkedList<ModulePointer> &getModules() const;

        bool isEmpty() const;

        bool getIsEqualityConstraint() const;
    };

    class EqualityConstraint : public Constraint {
    protected:
        virtual std::string toStringRHS() const;

    public:
        EqualityConstraint();
    };

    class InEqualityConstraint : public Constraint {
    protected:
        virtual std::string toStringRHS() const;

    public:
        InEqualityConstraint();
    };

    typedef std::shared_ptr<Constraint> ConstraintPointer;

}

#endif