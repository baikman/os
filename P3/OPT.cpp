#include "OPT.h"

OPT::OPT(int numPageFrames, std::vector<int> referenceString) : ReplacementAlgorithm(numPageFrames) {
    workingList = referenceString;
    pageFaultCount = 0;
    currIndex = 0;
    pageCount = referenceString.size();
}

void OPT::insert(int pageNumber) {
    // Implement OPT page replacement algorithm
    // Increment pageFaultCount if a page fault occurs
    for (int i : frameList) {
        if (i == pageNumber) {
            currIndex++;
            return;
        }
    }
    pageFaultCount++;
    if (frameList.size() < pageFrameCount) {
        frameList.push_back(pageNumber);
        currIndex++;
        return;
    } else {
        int farIndex = -1;
        int indexToRemove = -1;

        for (int i = 0; i < frameList.size(); i++) {
            int framePage = frameList[i];
            bool found = false;
            for (int j = currIndex+1; j < pageCount; j++) {
                if (workingList[j] == framePage) {
                    found = true;
                    if (j > farIndex) {
                        farIndex = j;
                        indexToRemove = i;
                    }
                    break;
                }
            }
            if (!found) {
                indexToRemove = i;
                break;
            }
        }

        frameList.erase(frameList.begin() + indexToRemove);
        frameList.push_back(pageNumber);

        currIndex++;
    }
}