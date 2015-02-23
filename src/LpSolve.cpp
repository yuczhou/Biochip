/*
 * LpSolve.h
 *
 *  Created on: Feb 18, 2015
 *      Author: yuczhou
 */

#ifndef LP_SOLVE_CPP
#define LP_SOLVE_CPP

#include "Utility.h"
#include "LpSolve.h"

namespace BioChip {

    LpSolve::LpSolve(const LinkedList<ConstraintPointer> &equations_, const std::map<std::string, int> &moduleIndexMap_)
            : equations(equations_), moduleIndexMap(moduleIndexMap_), lp(NULL), colno(NULL), row(NULL) {
        initialize();
    }

    LpSolve::~LpSolve() {
        free(row);
        free(colno);
        delete_lp(lp);
    }

    void LpSolve::initialize() {
        lp = make_lp(0, moduleIndexMap.size());
        colno = (int *) malloc(moduleIndexMap.size() * sizeof(*colno));
        row = (REAL *) malloc(moduleIndexMap.size() * sizeof(*row));
        for (auto const &module : moduleIndexMap) {
            set_col_name(lp, module.second + 1, const_cast<char *>(module.first.c_str()));
        }
        if (lp == NULL || colno == NULL || row == NULL) {
            std::cerr << "Unbale to initialize LP Solve" << std::endl;
            std::abort();
        }
    }

    bool LpSolve::solve() {
        set_add_rowmode(lp, TRUE);
        for (size_t c = 0; c < moduleIndexMap.size(); ++c) {
            colno[c] = c + 1;
            set_binary(lp, c + 1, TRUE);
        }
        for (auto &equation : equations) {
            memset(row, 0, moduleIndexMap.size() * sizeof(*row));
            for (auto const &module : equation->getModules()) {
                row[moduleIndexMap.at(module->toString())] = 1;
            }
            add_constraintex(lp, moduleIndexMap.size(), row, colno, equation->getIsEqualityConstraint() ? EQ : LE, 1);
        }
        set_add_rowmode(lp, FALSE);
        memset(row, 0, moduleIndexMap.size() * sizeof(*row));
        set_obj_fnex(lp, moduleIndexMap.size(), row, colno);

        if (::solve(lp) != OPTIMAL) {
            return false;
        }
        get_variables(lp, row);
        for (size_t j = 0; j < moduleIndexMap.size(); j++)
            printf("%s: %f\n", get_col_name(lp, j + 1), row[j]);
        return true;
    }

    std::shared_ptr<std::unordered_map<std::string, Coord> > LpSolve::getResult() {
        std::shared_ptr<ModulePlacement> modules = Utility::getPointer(new ModulePlacement());
        for (size_t module = 0; module < moduleIndexMap.size(); module++) {
            if (row[module] != 0) {
                insertModule(*modules, get_col_name(lp, module + 1));
            }
        }
        return modules;
    }

    void LpSolve::insertModule(ModulePlacement &modules, const char *rawModuleLoc) {
        auto splitted = Utility::split(rawModuleLoc, "_");
        auto moduleInfo = Utility::toStream(*splitted);
        std::string moduleName;
        *moduleInfo >> moduleName;
        Coord loc;
        *moduleInfo >> loc.x >> loc.y >> loc.z;
        modules[moduleName] = loc;
    }
}
#endif