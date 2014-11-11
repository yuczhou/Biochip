/*
 * Qualifier.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef QUALIFIER_H
#define QUALIFIER_H

namespace BioChip {

template<class T>
class Qualifier {
public:
    ~Qualifier() {
    }

    virtual bool operator()(const T &) const = 0;
};

template<class T>
class DummyQualifier : public Qualifier<T> {
public:
    virtual bool operator()(const T &element) const override {
        return true;
    }
};

}

#endif