/*
 * ConstraintWriter.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef CONSTRAINT_WRITER_H
#define CONSTRAINT_WRITER_H

#include "FormulateILP.h"
#include "Global.h"

namespace BioChip {

    class ConstraintWriter {
    private:
        const std::shared_ptr<LinkedList<ConstraintPointer> > equations;
        const std::shared_ptr<LinkedList<ModulePointer> > modules;
        std::ofstream file;
    public:
        ConstraintWriter(const std::shared_ptr<LinkedList<ConstraintPointer> >, const std::shared_ptr<LinkedList<ModulePointer> >, const char *);

        void write();
    };

}

#endif