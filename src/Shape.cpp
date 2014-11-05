/*
 * Shape.cpp
 *
 *  Created on: Oct 29, 2014
 *      Author: yuczhou
 */

#include "Shape.h"

namespace BioChip {

Shape::Shape() {
    // TODO Auto-generated constructor stub

}

Shape::~Shape() {
    // TODO Auto-generated destructor stub
}

RectangularShape::RectangularShape(Coord dimension_) : dimension(std::move(dimension_)) {
}

RectangularShape::~RectangularShape() {
}

bool RectangularShape::isValid(Coord lowerLeft, Coord upperRight) {
    return lowerLeft.add(dimension) <= upperRight;
}

const Coord &RectangularShape::getDimension() const {
    return dimension;
}

} /* namespace BioChip */
