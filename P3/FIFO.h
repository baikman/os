#ifndef _FIFO_H
#define _FIFO_H

#include <iostream>
#include <vector>
#include "ReplacementAlgorithm.h"

class FIFO : public ReplacementAlgorithm {
public:
    FIFO(int numPageFrames);
    void insert(int pageNumber) override;

private:
    // Declare a data structure representing the page frames in memory
    // <data type> frameList;
    std::vector<int> frameList; // I like vectors
};

#endif