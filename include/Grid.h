/*
 * Grid.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef GRID_H_
#define GRID_H_

#include "Container.h"
#include "Coordinate.h"

namespace BioChip {

class Grid : public LinkedList<Coord> {
private:
    Coord dimension;
private:
    void constructGrid();

public:
    Grid(int, int, int);

    Grid(Coord);
};

}

#endif