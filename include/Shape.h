/*
 * Shape.h
 *
 *  Created on: Oct 29, 2014
 *      Author: yuczhou
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Coordinate.h"

namespace BioChip {

class Shape {
public:
    Shape();

    virtual ~Shape();

    virtual bool isValid(Coord, Coord) = 0;

    virtual const Coord &getDimension() const = 0;
};

class RectangularShape : public Shape {
private:
    Coord dimension;
public:
    RectangularShape(Coord);

    ~RectangularShape();

    virtual bool isValid(Coord, Coord);

    virtual const Coord &getDimension() const override;
};

} /* namespace BioChip */

#endif /* SHAPE_H_ */
