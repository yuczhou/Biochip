/*
 * Grid.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef GRID_CPP_
#define GRID_CPP_

#include "Grid.h"

namespace BioChip {

Grid::Grid(int length, int width, int height) : dimension(Coord(length, width, height)) {
    constructGrid();
}

Grid::Grid(Coord dimension_) : dimension(std::move(dimension_)) {
}

void Grid::constructGrid() {
    for (int row = 0; row < dimension.x; ++row) {
        for (int col = 0; col < dimension.y; ++col) {
            for (int t = 0; t < dimension.z; ++t) {
                this->add(Coord(row, col, t));
            }
        }
    }
}

}

#endif