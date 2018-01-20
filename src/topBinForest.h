#include "reverseNode.h"
#include "baseForest.h"

class topBinForest : public baseForest {

    reverseNode ** forest = NULL;
    int bins;
    public:
    topBinForest(int numBins) : bins(numBins){}
    void createForestFromCSV(const std::string& forestCSVFileName);
    void makePredictions(const std::string& testFile);
};
