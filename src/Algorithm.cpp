/*
 * Algorithm.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef ALGORITHM_CPP
#define ALGORITHM_CPP

#include "Algorithm.h"

namespace BioChip {

    Algorithm::Algorithm(const char *testcase) {
        directedAcyclicGraph = Utility::getPointer(new DirectedAcyclicGraph());
        parser = Utility::getPointer(new Parser(testcase, *directedAcyclicGraph));
        parser->parse();
    }

    void Algorithm::run() {
        grid = Utility::getPointer(new Grid(parser->getGridSize(), Coarsen(parser->getGridSize()).createGranularity()));
        FormulateILP formulateILP(*directedAcyclicGraph, *grid);
        formulateILP.formulateILP();
        LpSolve lp(formulateILP.getEquations(), formulateILP.getModuleIndexMap());
        lp.solve();
    }

}

#endif