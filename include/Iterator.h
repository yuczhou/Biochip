/*
 * AbstractIterator.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef ITERATOR_H_
#define ITERATOR_H_

#include "Global.h"

namespace BioChip {

template<class T, class Container>
class AbstractIterator {
public:
    virtual ~AbstractIterator() {
    }

    virtual bool hasNext() const = 0;

    virtual T &next() {
        std::cerr << "should not be called!" << std::endl;
        exit(-1);
    }

    virtual const T &next() const {
        std::cerr << "should not be called!" << std::endl;
        exit(-1);
    }
};

template<class T, class Container>
class Iterator : public AbstractIterator<T, Container> {
private:
    Container &container;

    class Container::iterator innerIterator;

public:
    Iterator(Container &container_) :
            container(container_), innerIterator(container.begin()) {
    }

    virtual ~Iterator() {
    }

    bool hasNext() const {
        return innerIterator != container.end();
    }

    T &next() {
        return *innerIterator++;
    }
};

template<class T, class Container>
class ConstIterator : public AbstractIterator<T, Container> {
private:
    const Container &container;
    mutable class Container::const_iterator innerIterator;
public:
    ConstIterator(const Container &container_) :
            container(container_), innerIterator(container.begin()) {
    }

    virtual ~ConstIterator() {
    }

    bool hasNext() const {
        return innerIterator != container.end();
    }

    const T &next() const {
        return *innerIterator++;
    }
};

} /* namespace BioChip */

#endif /* ABSTRACTITERATOR_H_ */
