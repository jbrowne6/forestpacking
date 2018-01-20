#ifndef baseForest_h
#define baseForest_h

#include "baseNode.h"

class baseForest
{
    public:
    int numTreesInForest;
    int totalNumberOfNodes;
    int numLeafNodesInForest;
    int numOfClasses;
    bool debugModeOn;
    bool showAllResults;
    int returnClassPrediction(int *classTotals);

    baseForest() : debugModeOn(false), showAllResults(false){}
    void printForest();
    void virtual createForestFromCSV(const std::string& forestCSVFileName);
    void virtual makePredictions(const std::string& testFile);
    void turnDebugModeOn();
    void turnShowAllResultsOn();
};
#endif //baseForest.h
