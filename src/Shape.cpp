/*
 * Shape.cpp
 *
 *  Created on: Oct 29, 2014
 *      Author: yuczhou
 */

#include "Shape.h"

namespace BioChip {

Shape::Shape(std::string name_) : name(std::move(name_)) {
    // TODO Auto-generated constructor stub
}

Shape::~Shape() {
    // TODO Auto-generated destructor stub
}

std::string Shape::toString() const {
    return name;
}

RectangularShape::RectangularShape(std::string name_, Coord dimension_)
        : Shape(name_), dimension(std::move(dimension_)) {
}

RectangularShape::~RectangularShape() {
}

bool RectangularShape::isValid(Coord lowerLeft, Coord upperRight) {
    Coord shiftedDimension(dimension.x - 1, dimension.y - 1, dimension.z - 1);
    return lowerLeft.add(shiftedDimension) <= upperRight;
}

const Coord &RectangularShape::getDimension() const {
    return dimension;
}

} /* namespace BioChip */
