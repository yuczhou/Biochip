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

typedef LinkedList<Coord> CoordLinkedList;
typedef AbstractIterator<Coord, std::list<Coord> > CoordIterator;

class Grid : public CoordLinkedList {
private:
    Coord dimension;
private:
    void constructGrid();

public:
    Grid(int, int, int);

    Grid(Coord);

    Coord getUpperRight() const;
};

}

#endif