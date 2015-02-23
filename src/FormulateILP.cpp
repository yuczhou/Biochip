/*
 * FormulateILP.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef FORMULATE_ILP_CPP
#define FORMULATE_ILP_CPP

#include "Utility.h"
#include "FormulateILP.h"

namespace BioChip {

    FormulateCommand::FormulateCommand(const DirectedAcyclicGraph &graph_, const Grid &grid_)
            : graph(graph_), grid(grid_) {
    }

    std::shared_ptr<LinkedList<ConstraintPointer> > FormulateCommand::formulate() {
        auto equations = Utility::getPointer(new LinkedList<ConstraintPointer>());
        for (auto &moduleNode : graph) {
            std::cout << moduleNode->getName() << std::endl;
            singleFormulate(moduleNode, *equations);
        }
        postFormulate(*equations);
        return equations;
    }

    void FormulateCommand::singleFormulate(const ModuleNodePointer &moduleNode, LinkedList<ConstraintPointer> &equations) {
        auto constraints = createConstraintBuilder(moduleNode, grid)->buildConstraint();
        for (auto &equation : *constraints) {
            if (!equation->isEmpty()) {
                equations.add(equation);
            }
        }
    }

    SingletonConstraintFormulateCommand::SingletonConstraintFormulateCommand(const DirectedAcyclicGraph &graph_, const Grid &grid_)
            : FormulateCommand(graph_, grid_) {
    }

    FormulateCommand::ConstraintBuilderPointer SingletonConstraintFormulateCommand::createConstraintBuilder(const ModuleNodePointer &module, const Grid &grid) {
        return Utility::getPointer(new SingletonConstraintBuilder(module, grid));
    }

    PrecedenceConstraintFormulateCommand::PrecedenceConstraintFormulateCommand(const DirectedAcyclicGraph &graph_, const Grid &grid_)
            : FormulateCommand(graph_, grid_) {
    }

    FormulateCommand::ConstraintBuilderPointer PrecedenceConstraintFormulateCommand::createConstraintBuilder(const ModuleNodePointer &module, const Grid &grid) {
        return Utility::getPointer(new PrecedenceConstraintBuilder(module, grid));
    }

    NonOverlappingConstraintFormulateCommand::NonOverlappingConstraintFormulateCommand(const DirectedAcyclicGraph &graph_, const Grid &grid_)
            : FormulateCommand(graph_, grid_) {
    }

    FormulateCommand::ConstraintBuilderPointer NonOverlappingConstraintFormulateCommand::createConstraintBuilder(const ModuleNodePointer &module, const Grid &grid) {
        return Utility::getPointer(new NonOverlappingConstraintBuilder(module, grid, overlapMap));
    }

    void NonOverlappingConstraintFormulateCommand::postFormulate(LinkedList<ConstraintPointer> &equations) const {
        for (auto const &coordEquation : overlapMap) {
            equations.add(coordEquation.second);
        }
    }

    void ModuleRegister::addModule(const ConstraintPointer &equation) {
        static int count = 1;
        for (auto &module : equation->getModules()) {
            std::string moduleStr = module->toString();
            registeredModules[moduleStr] = module;
            if (moduleIndexMap.find(moduleStr) == moduleIndexMap.end()) {
                moduleIndexMap[moduleStr] = count++;
            }
        }
    }

    std::shared_ptr<LinkedList<ModulePointer> > ModuleRegister::getModules() const {
        auto modules = Utility::getPointer(new LinkedList<ModulePointer>());
        for (auto &module : registeredModules) {
            modules->add(module.second);
        }
        return modules;
    }

    const std::map<std::string, int> &ModuleRegister::getModuleIndexMap() const {
        return moduleIndexMap;
    }

    FormulateILP::FormulateILP(const DirectedAcyclicGraph &graph_, const Grid &grid_)
            : graph(graph_), grid(grid_), equations(Utility::getPointer(new LinkedList<ConstraintPointer>())) {
        initializeConstraints();
    }

    void FormulateILP::initializeConstraints() {
        constraints.add(Utility::getPointer(new SingletonConstraintFormulateCommand(graph, grid)));
        constraints.add(Utility::getPointer(new PrecedenceConstraintFormulateCommand(graph, grid)));
        constraints.add(Utility::getPointer(new NonOverlappingConstraintFormulateCommand(graph, grid)));
    }

    void FormulateILP::formulateILP() {
        for (auto &constraint : constraints) {
            auto singleConstraints = constraint->formulate();
            for (auto &equation : *singleConstraints) {
                equations->add(equation);
                moduleRegister.addModule(equation);
            }
        }
    }

    const LinkedList<ConstraintPointer> &FormulateILP::getEquations() const {
        return *equations;
    }

    const std::shared_ptr<LinkedList<ModulePointer> > FormulateILP::getModules() const {
        return moduleRegister.getModules();
    }

    const std::map<std::string, int> &FormulateILP::getModuleIndexMap() const {
        return moduleRegister.getModuleIndexMap();
    }

}

#endif