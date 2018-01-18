#include "baseForest.h"

class perTreeForest : public baseForest {

    Node ** forestRoots = NULL;
    public:
    void createForestFromCSV(const std::string& forestCSVFileName);
    void makePredictions(const std::string& testFile);
};
