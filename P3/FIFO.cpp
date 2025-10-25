#include "FIFO.h"

FIFO::FIFO(int numPageFrames) : ReplacementAlgorithm(numPageFrames) {
    pageFaultCount = 0;
}

void FIFO::insert(int pageNumber) {
    // Implement FIFO page replacement algorithm
    // Increment pageFaultCount if a page fault occurs
    for (int i : frameList) if (i == pageNumber) return;
    pageFaultCount++;
    if (frameList.size() < pageFrameCount) {
        frameList.push_back(pageNumber);
    } else {
        frameList.erase(frameList.begin());
        frameList.push_back(pageNumber);
    }
}