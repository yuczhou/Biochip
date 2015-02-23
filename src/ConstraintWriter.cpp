/*
 * ConstraintWriter.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef CONSTRAINT_WRITER_CPP
#define CONSTRAINT_WRITER_CPP

#include "ConstraintWriter.h"

namespace BioChip {

    ConstraintWriter::ConstraintWriter(const std::shared_ptr<LinkedList<ConstraintPointer> > equations_, const std::shared_ptr<LinkedList<ModulePointer> > modules_, const char *file_)
            : equations(equations_), modules(modules_), file(file_) {
    }

    void ConstraintWriter::write() {
        file << "min:;" << std::endl << std::endl;
        for (auto &equation : *equations) {
            file << equation->toString() << ";" << std::endl;
        }
        file << std::endl;

        file << "bin ";
        for (auto &module : *modules) {
            file << module->toString() << ", ";
        }
        file << "dummy;" << std::endl;
    }

}

#endif