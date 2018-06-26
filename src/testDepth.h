#ifndef testDepth_h
#define testDepth_h

#include "padForest.h"
#include <vector>
#include "inferenceSamples.h"
#include "padNodeStat.h"


class testDepth: public padForest 
{
    private:
    padNode ** forestRoots = NULL;

    public:
testDepth(const std::string& forestCSVFileName, int source, const inferenceSamples& observations);
~testDepth();
    void makePredictions(const inferenceSamples& observations);
};


#endif //testDepth_h
