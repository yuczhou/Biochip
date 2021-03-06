/*
 * LpSolve.h
 *
 *  Created on: Feb 9, 2015
 *      Author: yuczhou
 */

#ifndef LP_SOLVE_H
#define LP_SOLVE_H

#include "lp_lib.h"
#include "Constraint.h"

namespace BioChip {

    struct SingleModulePlacement {
    public:
        const Coord placement;
        const int shape;
    public:
        SingleModulePlacement(const Coord &, const int);
    };

    typedef std::unordered_map<std::string, SingleModulePlacement> ModulePlacement;

    class LpSolve {
    private:
        const LinkedList<ConstraintPointer> &equations;
        const std::map<std::string, int> &moduleIndexMap;
        lprec *lp;
        int *colno;
        REAL *row;
    private:
        void initialize();

        void insertModule(ModulePlacement &, const char *);

    public:
        LpSolve(const LinkedList<ConstraintPointer> &, const std::map<std::string, int> &);

        ~LpSolve();

        bool solve();

        std::shared_ptr<ModulePlacement> getPlacement();
    };
}

#endif