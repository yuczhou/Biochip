/*
 * Coarsen.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef COARSEN_CPP
#define COARSEN_CPP

#include "Coarsen.h"

namespace BioChip {

    Coarsen::Coarsen(const Coord &gridDimension_) : gridDimension(gridDimension_) {
    }

    Coord Coarsen::createGranularity() const {
        return std::move(Coord(1, 1, 1).max(gridDimension / Coord(GRID_MAX_X, GRID_MAX_Y, GRID_MAX_Z)));
    }

}
#endif