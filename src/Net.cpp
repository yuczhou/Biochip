/*
 * Net.cpp
 *
 *  Created on: Feb 27, 2015
 *      Author: yuczhou
 */

#ifndef NET_CPP
#define NET_CPP

#include "Utility.h"
#include "Net.h"
#include "LpSolve.h"

namespace BioChip {

    Pin::Pin(ModulePointer module_) : module(module_) {
        buildPins();
    }

    void Pin::moveUp(int displacement) {
        std::set<Coord> newPins;
        for (auto &pin : pins) {
            newPins.insert(Coord(pin.x, pin.y, pin.z + displacement));
        }
        std::swap(newPins, pins);
    }

    const std::set<Coord> &Pin::getPins() const {
        return pins;
    }

    void Pin::buildPins() {
        auto const &lowerLeft = module->getLowerLeft();
        auto const &shape = module->getShape()->getDimension();
        pins.clear();
        for (int x = 0; x < shape.x; ++x) {
            for (int y = 0; y < shape.y; ++y) {
                Coord absPin(x, y, 0);
                pins.insert(lowerLeft + absPin);
            }
        }
    }

    SourcePin::SourcePin(ModulePointer module_) : Pin(module_) {
    }

    TargetPin::TargetPin(ModulePointer module_) : Pin(module_) {
        this->buildPins();
    }

    void TargetPin::buildPins() {
        Pin::buildPins();
        moveUp(module->getShape()->getDimension().z - 1);
    }

    void Net::addPin(ptr(Pin) &pin) {
        targets.add(pin);
    }

    int Net::getNumberOfPins() const {
        return (int) targets.size();
    }

    void NetList::addNet(ptr(Net) &net) {
        netList.add(net);
    }

    const ArrayList<std::shared_ptr<Net> > &NetList::getNetList() const {
        return netList;
    }

    NetListFactory::NetListFactory() : netList(Utility::getPointer(new NetList())), placement(NULL) {
    }

    NetListFactory &NetListFactory::getInstance() {
        static NetListFactory instance;
        return instance;
    }

    ptr(NetList) NetListFactory::createNetList(DirectedAcyclicGraph &graph, ptr(ModulePlacement) placement) {
        this->placement = placement;
        for (const auto &module : graph) {
            createNet(module);
        }
        return netList;
    }

    void NetListFactory::createNet(const ModuleNodePointer &module) {
        auto net = Utility::getPointer(new Net());
        ptr(Pin) source = createPin(module, true);
        if (!source) {
            return;
        }
        net->addPin(source);
        auto node = std::dynamic_pointer_cast<GraphNode>(module);
        for (const auto &predecessor : node->getParents()) {
            auto moduleType = std::dynamic_pointer_cast<ModuleNodePointer>(predecessor);
            ptr(Pin) target = createPin(module, false);
            if (target) {
                net->addPin(target);
            }
        }
        if (net->getNumberOfPins() > 1) {
            netList->addNet(net);
        }
    }

    ptr(Pin) NetListFactory::createPin(const ModuleNodePointer &module, bool isSource) {
        if (placement->find(module->getName()) == placement->end()) {
            return NULL;
        }
        auto placementInfo = placement->at(module->getName());
        if (isSource) {
            return Utility::getPointer(new SourcePin(module->createModule(placementInfo.shape, placementInfo.placement)));
        }
        return Utility::getPointer(new TargetPin(module->createModule(placementInfo.shape, placementInfo.placement)));
    }
}
#endif