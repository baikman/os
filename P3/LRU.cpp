#include "LRU.h"

LRU::LRU(int numPageFrames) : ReplacementAlgorithm(numPageFrames) {
    pageFaultCount = 0;
    time = 0;
    lastUsed.resize(100, 0);
}

void LRU::insert(int pageNumber) {
    // Implement LRU page replacement algorithm
    // Increment pageFaultCount if a page fault occurs
    time++;
    for (int i : frameList) {
        if (i == pageNumber) {
            lastUsed[pageNumber] = time;
            return;
        }
    }

    pageFaultCount++;

    if (frameList.size() < pageFrameCount) {
        frameList.push_back(pageNumber);
        lastUsed[pageNumber] = time;
        return;
    } else {
        int index = 0;
        int lastTime = lastUsed[frameList[0]];
        for (int i = 1; i < frameList.size(); i++) {
            int j = frameList[i];
            if (lastUsed[j] < lastTime) {
                lastTime = lastUsed[j];
                index = i;
            }
        }
        frameList.erase(frameList.begin() + index);
        frameList.push_back(pageNumber);
        lastUsed[pageNumber] = time;
    }
}