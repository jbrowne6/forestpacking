#include "baseForest.h"

class interleavedForest : public baseForest {

    Node * forest = NULL;
    public:
    void createForestFromCSV(const std::string& forestCSVFileName);
    void makePredictions(const std::string& testFile);
};
