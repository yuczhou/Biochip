/*
 * Container.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_
#include "Iterator.h"
#include <utility>

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
	virtual void add(T element) = 0;
};

template<class T>
class ArrayList : public Container<T, std::vector<T> > {
public:
	void add(T element) override final {
		this->container.push_back(std::move(element));
	}
};

template<class T>
class LinkedList : public Container<T, std::list<T> > {
public:
	void add(T element) override final {
		this->container.push_back(std::move(element));
	}
};

template<class T>
class HashSet : public Container<T, std::unordered_set<T> > {
public:
	void add(T element) override final {
		this->container.insert(std::move(element));
	}
};

} /* namespace BioChip */

#endif /* CONTAINER_H_ */
