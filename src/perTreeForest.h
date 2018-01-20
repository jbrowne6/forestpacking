#include "baseForest.h"

class perTreeForest : public baseForest 
{
    baseNode ** forestRoots = NULL;
    public:
    void createForestFromCSV(const std::string& forestCSVFileName);
    void makePredictions(const std::string& testFile);
};
