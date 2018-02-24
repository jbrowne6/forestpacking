//This is improvement 5.  Builds on improv3. Groups trees into bins while 
//maintaining previous optimizations.

#ifndef improv5_h
#define improv5_h

#include "padForest.h"
#include "inferenceSamples.h"
#include "batchPredictions.h"
#include "padNodeStat.h"
#include "treeBin.h"


class improv5: public padForest 
{
    private:
    treeBin** forestRoots = NULL;
    int numOfBins;

    public:
improv5(const std::string& forestCSVFileName, int source, const inferenceSamples& observations, int numberBins);
~improv5();
    void makePredictions(const inferenceSamples& observations);
};


#endif //improv5_h
