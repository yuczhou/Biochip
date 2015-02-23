/*
 * Coarsen.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef COARSEN_H
#define COARSEN_H

#include "Coordinate.h"
#include "Global.h"

#define GRID_MAX_X 4
#define GRID_MAX_Y 4
#define GRID_MAX_Z 10

namespace BioChip {

    class Coarsen {
    protected:
        const Coord &gridDimension;
    public:
        Coarsen(const Coord &);

        Coord createGranularity() const;
    };

}
#endif