/*
 * Parser.h
 *
 *  Created on: Oct 23, 2014
 *      Author: yuczhou
 */

#ifndef PARSER_H
#define PARSER_H

#include "Global.h"
#include "Container.h"
#include "ModuleNode.h"
#include "Utility.h"

namespace BioChip {

    class GraphManager {
    private:
        DirectedAcyclicGraph &graph;
        std::unordered_map<std::string, ModuleNodePointer> graphNodeTracker;
        Coord gridSize;
    public:
        GraphManager(DirectedAcyclicGraph &);

        void add(const std::string &);

        ModuleNodePointer getNode(const std::string &);

        void setGridSize(const Coord);

        const Coord &getGridSize() const;
    };

    class Parser {
    private:
        std::ifstream file;
        GraphManager graph;
    private:
        Coord parseCoord(const std::string &);

        void parseModuleNodes(const int);

        void parseSingleModule();

        void parsePrecedence();

    public:
        Parser(const char *, DirectedAcyclicGraph &);

        void parse();

        const Coord &getGridSize() const;
    };

}

#endif