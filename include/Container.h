/*
 * Container.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "Iterator.h"
#include "Qualifier.h"

namespace BioChip {

    template<class T, class ContainerT>
    class Container {
    protected:
        typedef std::shared_ptr<Iterator<T, ContainerT> > IteratorPointer;
        typedef std::shared_ptr<ConstIterator<T, ContainerT> > ConstIteratorPointer;
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

        IteratorPointer getIterator(const Qualifier<T> &condition) {
            return IteratorPointer(new ConditionedIterator<T, ContainerT, Qualifier<T> >(container, condition));
        }

        ConstIteratorPointer getIterator(const Qualifier<T> &condition) const {
            return ConstIteratorPointer(new ConstConditionedIterator<T, ContainerT, Qualifier<T> >(container, condition));
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

        virtual void addAll(const Container &other) = 0;

        virtual bool contains(const T &element) const {
            return std::find(begin(), end(), element) != end();
        }

        size_t size() const {
            return container.size();
        }
    };

    template<class T>
    class ArrayList : public Container<T, std::vector<T> > {
    public:
        virtual void add(T element) override

        final {
            this->container.push_back(std::move(element));
        }

        T &at(size_t index) {
            return this->container.at(index);
        }

        const T &at(size_t index) const {
            return this->container.at(index);
        }

        virtual void addAll(const Container<T, std::vector<T> > &other) {
            this->container.insert(this->container.end(), other.begin(), other.end());
        }
    };

    template<class T>
    class LinkedList : public Container<T, std::list<T> > {
    public:
        virtual void add(T element) override

        final {
            this->container.push_back(std::move(element));
        }

        virtual void addAll(const Container<T, std::list<T> > &other) {
            this->container.insert(this->container.end(), other.begin(), other.end());
        }
    };

    template<class T>
    class HashSet : public Container<T, std::unordered_set<T> > {
    public:
        virtual void add(T element) override

        final {
            this->container.insert(std::move(element));
        }

        virtual bool contains(const T &element) const override

        final {
            return this->container.find(element) != this->end();
        }

        virtual void addAll(const Container<T, std::unordered_set<T> > &other) {
            this->container.insert(other.begin(), other.end());
        }
    };

} /* namespace BioChip */

#endif /* CONTAINER_H_ */
