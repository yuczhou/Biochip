/*
 * FormulateILP.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef FORMULATE_ILP_H
#define FORMULATE_ILP_H

#include "ConstraintBuilder.h"

namespace BioChip {

    class FormulateCommand {
    protected:
        typedef std::shared_ptr<ConstraintBuilder> ConstraintBuilderPointer;

        const DirectedAcyclicGraph &graph;
        const Grid &grid;
    protected:
        void singleFormulate(const ModuleNodePointer &, LinkedList<ConstraintPointer> &);

        virtual void postFormulate(LinkedList<ConstraintPointer> &) const {
        }

        virtual ConstraintBuilderPointer createConstraintBuilder(const ModuleNodePointer &, const Grid &) = 0;

    public:
        FormulateCommand(const DirectedAcyclicGraph &, const Grid &);

        std::shared_ptr<LinkedList<ConstraintPointer> > formulate();
    };

    class SingletonConstraintFormulateCommand : public FormulateCommand {
    protected:
        virtual ConstraintBuilderPointer createConstraintBuilder(const ModuleNodePointer &, const Grid &);

    public:
        SingletonConstraintFormulateCommand(const DirectedAcyclicGraph &, const Grid &);
    };

    class PrecedenceConstraintFormulateCommand : public FormulateCommand {
    protected:
        virtual ConstraintBuilderPointer createConstraintBuilder(const ModuleNodePointer &, const Grid &);

    public:
        PrecedenceConstraintFormulateCommand(const DirectedAcyclicGraph &, const Grid &);
    };

    class NonOverlappingConstraintFormulateCommand : public FormulateCommand {
    private:
        std::map<Coord, ConstraintPointer> overlapMap;
    protected:
        virtual ConstraintBuilderPointer createConstraintBuilder(const ModuleNodePointer &, const Grid &);

        virtual void postFormulate(LinkedList<ConstraintPointer> &) const;

    public:
        NonOverlappingConstraintFormulateCommand(const DirectedAcyclicGraph &, const Grid &);
    };

    class ModuleRegister {
    private:
        std::map<std::string, ModulePointer> registeredModules;
        std::map<std::string, int> moduleIndexMap;
    public:
        void addModule(const ConstraintPointer &);

        std::shared_ptr<LinkedList<ModulePointer> > getModules() const;

        const std::map<std::string, int> &getModuleIndexMap() const;
    };

    typedef std::shared_ptr<FormulateCommand> FormulateCommandPointer;

    class FormulateILP {
    private:
        const DirectedAcyclicGraph &graph;
        const Grid &grid;
        LinkedList<FormulateCommandPointer> constraints;
        std::shared_ptr<LinkedList<ConstraintPointer> > equations;
        ModuleRegister moduleRegister;
    private:
        void initializeConstraints();

    public:
        FormulateILP(const DirectedAcyclicGraph &, const Grid &);

        void formulateILP();

        const LinkedList<ConstraintPointer> &getEquations() const;

        const std::shared_ptr<LinkedList<ModulePointer> > getModules() const;

        const std::map<std::string, int> &getModuleIndexMap() const;
    };

}

#endif