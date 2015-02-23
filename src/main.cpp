/*
 * main.cpp
 *
 *  Created on: Oct 26, 2014
 *      Author: yuczhou
 */
#ifndef BIOCHIP_MAIN
#define BIOCHIP_MAIN

#include "Algorithm.h"

void printUsage() {
    std::cout << "<executable> <testcase file>" << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printUsage();
        exit(-1);
    }

    BioChip::Algorithm(argv[1]).run();
    return 0;
}

#endif

