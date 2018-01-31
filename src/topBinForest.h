#include "reverseNode.h"
#include "baseForest.h"

class topBinForest : public baseForest {

    baseNode ** forest = NULL;
    int numOfBins;
    int treeTopDepth;
    public:
    topBinForest(int numBins) : numOfBins(numBins), treeTopDepth(4){}
    void createForestFromCSV(const std::string& forestCSVFileName);
    void makePredictions(const std::string& testFile);
    void printForest();
};
