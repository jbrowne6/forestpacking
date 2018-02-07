#include "reverseNode.h"
#include "baseForest.h"

class topBinForestWBatch : public baseForest {

    baseNode ** forest = NULL;
    int numOfBins;
    int treeTopDepth;
    int batchSize;
    public:
    topBinForestWBatch(int numBins) : numOfBins(numBins), treeTopDepth(4), batchSize(2500){}
    void createForestFromCSV(const std::string& forestCSVFileName);
    void makePredictions(const std::string& testFile);
    void printForest();
};
