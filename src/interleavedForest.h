#include "baseForest.h"

class interleavedForest : public baseForest {

    baseNode * forest = NULL;
    public:
    void createForestFromCSV(const std::string& forestCSVFileName);
    void makePredictions(const std::string& testFile);
};
