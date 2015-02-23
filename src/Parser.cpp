/*
 * Parser.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#include "Parser.h"

#ifndef PARSER_CPP
#define PARSER_CPP

namespace BioChip {

    GraphManager::GraphManager(DirectedAcyclicGraph &graph_) : graph(graph_) {
    }

    void GraphManager::add(const std::string &node) {
        graphNodeTracker[node] = Utility::getPointer(new RectangularModuleFactory(node.c_str()));
        graph.add(graphNodeTracker[node]);
    }

    ModuleNodePointer GraphManager::getNode(const std::string &node) {
        auto iterator = graphNodeTracker.find(node);
        return iterator == graphNodeTracker.end() ? ModuleNodePointer() : iterator->second;
    }

    void GraphManager::setGridSize(const Coord gridSize_) {
        gridSize = std::move(gridSize_);
    }

    const Coord &GraphManager::getGridSize() const {
        return gridSize;
    }

    Parser::Parser(const char *fileName_, DirectedAcyclicGraph &graph_) : file(fileName_), graph(graph_) {
    }

    Coord Parser::parseCoord(const std::string &rawGridSize) {
        std::istringstream stream(rawGridSize);
        Coord gridSize;
        stream >> gridSize.x >> gridSize.y >> gridSize.z;
        return std::move(gridSize);
    }

    void Parser::parseModuleNodes(const int numModules) {
        for (int module = 0; module < numModules; ++module) {
            parseSingleModule();
        }
    }

    void Parser::parseSingleModule() {
        std::string raw;
        std::string module;
        int numShapes;

        std::getline(file, raw);
        module = Utility::split(raw, " ")->at(1);
        graph.add(module);

        std::getline(file, raw);
        numShapes = atoi(Utility::split(raw, " ")->at(1).c_str());
        for (int shape = 0; shape < numShapes; ++shape) {
            std::getline(file, raw);
            graph.getNode(module)->addShape(Utility::getPointer(new RectangularShape(std::to_string(shape), std::move(parseCoord(raw)))));
        }
    }

    void Parser::parsePrecedence() {
        std::string raw;
        std::getline(file, raw);

        while (!raw.empty()) {
            auto parent = std::dynamic_pointer_cast<GraphNode>(graph.getNode(Utility::split(raw, " ")->at(0)));
            auto child = std::dynamic_pointer_cast<GraphNode>(graph.getNode(Utility::split(raw, " ")->at(1)));
            parent->addChild(child);
            child->addParent(parent);
            std::getline(file, raw);
        }
    }

    void Parser::parse() {
        for (std::string line; std::getline(file, line);) {
            auto splitted = Utility::split(line, ":");
            if (splitted->empty()) {
                continue;
            }
            if (splitted->at(0) == "Fixed") {
                graph.setGridSize(parseCoord(splitted->at(1)));
                continue;
            }
            if (splitted->at(0) == "NumberOfNodes") {
                parseModuleNodes(atoi(splitted->at(1).c_str()));
                continue;
            }
            if (splitted->at(0) == "Precedence Constraint") {
                parsePrecedence();
            }
        }
    }

    const Coord &Parser::getGridSize() const {
        return graph.getGridSize();
    }

}

#endif