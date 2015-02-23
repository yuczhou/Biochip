/*
 * Algorithm.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "FormulateILP.h"
#include "Parser.h"
#include "ConstraintWriter.h"
#include "Coarsen.h"
#include "LpSolve.h"

namespace BioChip {

    class Algorithm {
    private:
        std::shared_ptr<DirectedAcyclicGraph> directedAcyclicGraph;
        std::shared_ptr<Grid> grid;
        std::shared_ptr<Parser> parser;
    public:
        Algorithm(const char *);

        void run();
    };

}
#endif