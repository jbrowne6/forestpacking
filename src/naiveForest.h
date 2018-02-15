#ifndef naiveForest_h
#define naiveForest_h

#include "padForest.h"
#include "inferenceSamples.h"


class naiveForest : public padForest 
{
    private:
    padNode ** forestRoots = NULL;

    public:
naiveForest(const std::string& forestCSVFileName, int source);
~naiveForest();
    void makePredictions(const inferenceSamples& observations, int batchSize, int startPosition);
};


#endif //naiveForest_h
