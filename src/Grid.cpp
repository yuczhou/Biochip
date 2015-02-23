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

    Grid::Grid(int length, int width, int height, Coord granularity) : dimension(Coord(length, width, height)) {
        constructGrid(granularity);
    }

    Grid::Grid(Coord dimension_, Coord granularity) : dimension(std::move(dimension_)) {
        constructGrid(granularity);
    }

    void Grid::constructGrid(const Coord &granularity) {
        for (int row = 0; row < dimension.x; ++row) {
            for (int col = 0; col < dimension.y; ++col) {
                for (int t = 0; t < dimension.z; ++t) {
                    if (Coord(row, col, t) % granularity == Coord::origin) {
                        this->add(Coord(row, col, t));
                    }
                }
            }
        }
    }

    Coord Grid::getUpperRight() const {
        return Coord(dimension.x - 1, dimension.y - 1, dimension.z - 1);
    }

}

#endif