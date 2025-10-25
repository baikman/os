#ifndef _OPT_H
#define _OPT_H

#include <iostream>
#include <vector>
#include "ReplacementAlgorithm.h"

class OPT : public ReplacementAlgorithm {
public:
    OPT(int numPageFrames, std::vector<int> referenceString);
    void insert(int pageNumber) override;

private:
    // Declare a data structure representing the page frames in memory
    // <data type> frameList;
    std::vector<int> workingList; // I like vectors
    std::vector<int> frameList;
    int pageCount;
    int currIndex;
};

#endif