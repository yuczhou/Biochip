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
protected:
    Container &container;

    class Container::iterator innerIterator;

public:
    Iterator(Container &container_) :
            container(container_), innerIterator(container.begin()) {
    }

    virtual ~Iterator() {
    }

    virtual bool hasNext() const override {
        return innerIterator != container.end();
    }

    virtual T &next() override {
        return *innerIterator++;
    }
};

template<class T, class Container>
class ConstIterator : public AbstractIterator<T, Container> {
protected:
    const Container &container;
    mutable class Container::const_iterator innerIterator;
public:
    ConstIterator(const Container &container_) :
            container(container_), innerIterator(container.begin()) {
    }

    virtual ~ConstIterator() {
    }

    virtual bool hasNext() const override {
        return innerIterator != container.end();
    }

    virtual const T &next() const override {
        return *innerIterator++;
    }
};

template<class T, class Container, class Condition>
class ConditionedIterator : public Iterator<T, Container> {
private:
    const Condition &condition;
public:
    ConditionedIterator(Container &container_, const Condition &condition_)
            : Iterator<T, Container>(container_), condition(condition_) {
    }

    virtual ~ConditionedIterator() {
    }

    virtual bool hasNext() const override {
        while (Iterator<T, Container>::hasNext() && !condition(*(this->innerIterator))) {
            const_cast<ConditionedIterator *>(this)->Iterator<T, Container>::next();
        }
        return Iterator<T, Container>::hasNext();
    }

    virtual T &next() override {
        hasNext();
        return Iterator<T, Container>::next();
    }
};

template<class T, class Container, class Condition>
class ConstConditionedIterator : public ConstIterator<T, Container> {
private:
    const Condition &condition;
public:
    ConstConditionedIterator(const Container &container_, const Condition &condition_)
            : ConstIterator<T, Container>(container_), condition(condition_) {
    }

    virtual ~ConstConditionedIterator() {
    }

    virtual bool hasNext() const override {
        while (ConstIterator<T, Container>::hasNext() && !condition(*ConstIterator<T, Container>::innerIterator)) {
            ConstIterator<T, Container>::next();
        }
        return ConstIterator<T, Container>::hasNext();
    }

    virtual const T &next() const override {
        hasNext();
        return ConstIterator<T, Container>::next();
    }
};

} /* namespace BioChip */

#endif /* ABSTRACTITERATOR_H_ */
