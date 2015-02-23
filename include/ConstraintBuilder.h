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
#include "Utility.h"

namespace BioChip {

    typedef Qualifier<Coord> CoordValidator;
    typedef std::shared_ptr<CoordValidator> CoordValidatorPointer;

    class GeneralValidator : public CoordValidator {
    protected:
        const Coord upperRight;
        const ModuleFactory &moduleNode;
        size_t shape;
    public:
        GeneralValidator(const Coord, const ModuleFactory &, size_t);

        virtual bool operator()(const Coord &) const;
    };

    class ConstraintBuilder {
    protected:
        const ModuleNodePointer moduleNodePointer;
        const Grid &grid;
        std::shared_ptr<LinkedList<ConstraintPointer> > equations = Utility::getPointer(new LinkedList<ConstraintPointer>());
    protected:
        virtual CoordValidatorPointer getValidator(size_t) const;

        virtual void fixedCoordBuildConstraint(ModulePointer) = 0;

        virtual void postBuildEquations();

    public:
        ConstraintBuilder(const ModuleNodePointer &, const Grid &);

        const std::shared_ptr<LinkedList<ConstraintPointer> > &buildConstraint();
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
        virtual void fixedCoordBuildConstraint(ModulePointer);

        virtual void postBuildEquations();

    public:
        SingletonConstraintBuilder(const ModuleNodePointer &, const Grid &);
    };

    class PrecedenceConstraintBuilder : public ConstraintBuilder {
    private:
        class FixedNeighborConstraintBuilder : public ConstraintBuilder, public SingleInEqualityGenerator {
        private:
            class PrecedenceValidator : public GeneralValidator {
            private:
                const ModulePointer &root;
            public:
                PrecedenceValidator(const Coord, const ModuleFactory &, size_t, const ModulePointer &);

                virtual bool operator()(const Coord &) const;
            };

            const ModulePointer &root;
        protected:
            virtual void fixedCoordBuildConstraint(ModulePointer);

            virtual CoordValidatorPointer getValidator(size_t) const;

        public:
            FixedNeighborConstraintBuilder(const ModuleNodePointer &, const Grid &, const ModulePointer &);
        };

    protected:
        virtual void fixedCoordBuildConstraint(ModulePointer);

    public:
        PrecedenceConstraintBuilder(const ModuleNodePointer &, const Grid &);
    };

    class NonOverlappingConstraintBuilder : public ConstraintBuilder {
    private:
        std::map<Coord, ConstraintPointer> &overlapMap;
    protected:
        virtual void fixedCoordBuildConstraint(ModulePointer);

    public:
        NonOverlappingConstraintBuilder(const ModuleNodePointer &, const Grid &, std::map<Coord, ConstraintPointer> &);
    };

}
#endif