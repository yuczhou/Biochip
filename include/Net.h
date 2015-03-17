/*
 * Parser.h
 *
 *  Created on: Feb 25, 2015
 *      Author: yuczhou
 */

#ifndef NET_H
#define NET_H

#include "ModuleNode.h"
#include "LpSolve.h"
#include "Global.h"

namespace BioChip {
    class Pin {
    private:
        std::set<Coord> pins;
    protected:
        ModulePointer module;
    protected:
        virtual void buildPins();

    public:
        Pin(ModulePointer);

        void moveUp(int displacement = 0);

        const std::set<Coord> &getPins() const;
    };

    class SourcePin : public Pin {
    public:
        SourcePin(ModulePointer);
    };

    class TargetPin : public Pin {
    protected:
        virtual void buildPins();

    public:
        TargetPin(ModulePointer);
    };

    typedef std::shared_ptr<Pin> PinPointer;

    class Net {
    private:
        LinkedList<PinPointer> targets;
    public:
        void addPin(PinPointer &);

        const LinkedList<PinPointer> &getPins() const;

        int getNumberOfPins() const;
    };

    class NetList {
    private:
        ArrayList<std::shared_ptr<Net> > netList;
    public:
        void addNet(std::shared_ptr<Net> &);

        const ArrayList<std::shared_ptr<Net> > &getNetList() const;
    };

    class NetListFactory {
    private:
        ptr(NetList) netList;
        ptr(ModulePlacement) placement;
    private:
        NetListFactory();

        NetListFactory(const NetListFactory &);

        void createNet(const ModuleNodePointer &);

        ptr(Pin) createPin(const ModuleNodePointer &, bool);

    public:
        static NetListFactory &getInstance();

        ptr(NetList) createNetList(DirectedAcyclicGraph &, ptr(ModulePlacement));
    };
}

#endif