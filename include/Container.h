/*
 * Container.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "Iterator.h"

namespace BioChip {

template<class T, class ContainerT>
class Container {
private:
    typedef std::shared_ptr<Iterator<T, ContainerT> > IteratorPointer;
    typedef std::shared_ptr<ConstIterator<T, ContainerT> > ConstIteratorPointer;
protected:
    ContainerT container;
public:
    Container() {
    }

    ~Container() {
    }

    IteratorPointer getIterator() {
        return IteratorPointer(new Iterator<T, ContainerT>(container));
    }

    ConstIteratorPointer getIterator() const {
        return ConstIteratorPointer(new ConstIterator<T, ContainerT>(container));
    }

    class ContainerT::iterator begin() {
        return container.begin();
    }

    class ContainerT::iterator end() {
        return container.end();
    }

    class ContainerT::const_iterator begin() const {
        return container.begin();
    }

    class ContainerT::const_iterator end() const {
        return container.end();
    }

    virtual void add(T element) = 0;

    virtual bool contains(T element) const {
        return std::find(begin(), end(), element) != end();
    }
};

template<class T>
class ArrayList : public Container<T, std::vector<T> > {
public:
    void add(T element) override

    final {
        this->container.push_back(std::move(element));
    }

    T &at(size_t index) {
        return this->container.at(index);
    }

    const T &at(size_t index) const {
        return this->container.at(index);
    }
};

template<class T>
class LinkedList : public Container<T, std::list<T> > {
public:
    void add(T element) override

    final {
        this->container.push_back(std::move(element));
    }
};

template<class T>
class HashSet : public Container<T, std::unordered_set<T> > {
public:
    void add(T element) override

    final {
        this->container.insert(std::move(element));
    }

    bool contains(T element) const override

    final {
        return this->container.find(element) != this->end();
    }
};

} /* namespace BioChip */

#endif /* CONTAINER_H_ */
