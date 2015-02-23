/*
 * Module.h
 *
 *  Created on: Oct 29, 2014
 *      Author: yuczhou
 */

#ifndef MODULE_H_
#define MODULE_H_

#include "Shape.h"

namespace BioChip {

    typedef std::shared_ptr<Shape> ShapePointer;

    class Module {
    private:
        const std::string name;
        const Coord lowerLeft;
        ShapePointer shape;
    public:
        Module(const char *, const Coord, ShapePointer);

        const std::string &getName() const {
            return name;
        }

        const Coord &getLowerLeft() const {
            return lowerLeft;
        }

        const ShapePointer &getShape() const {
            return shape;
        }

        ShapePointer &getShape() {
            return shape;
        }

        int getCompletionTime() const {
            return lowerLeft.z + shape->getDimension().z;
        }

        bool isValid(const Coord &upperRight) const {
            return shape->isValid(lowerLeft, upperRight);
        }

        std::string toString() const {
            return std::move(name + "_" + lowerLeft.toString() + "_" + shape->toString());
        }
    };

    typedef std::shared_ptr<Module> ModulePointer;

} /* namespace BioChip */

#endif /* MODULE_H_ */
