#ifndef treeBin_h
#define treeBin_h

#include "padForest.h"
#include "inferenceSamples.h"
#include "batchPredictions.h"
#include "padNodeStat.h"
#include "padNode.h"


class treeBin   
{
    private:
    padNode * bin = NULL;
    int numOfTreesInBin;
    int depth;
    int firstFreeNode = -1;
    int currProcess = -1;

    public:
treeBin(padNodeStat**& forest, int*& treeLength, int startTree, int finalTree, int headDepth);
~treeBin();
};


#endif //treeBin_h
