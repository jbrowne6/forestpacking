//This is improvement 6.  Builds on improv4. Build tree depth first based on usage stats instead of pre-order.
//This improv bins top levels then does a pseudo pre-order.

#ifndef improv9_h
#define improv9_h

#include "padForest.h"
#include "inferenceSamples.h"
//#include "batchPredictions.h"
#include "padNodeStat.h"
#include "treeBin2.h"

class improv9: public padForest 
{
    private:
    treeBin2** forestRoots = NULL;
    int numOfBins;

    public:
improv9(const std::string& forestCSVFileName, int source, const inferenceSamples& observations, int numberBins, int depthIntertwined);
~improv9();
    void makePredictions(const inferenceSamples& observations);
    int makePrediction(double*& observation);
    int makeTest(double*& observation);
};


#endif //improv9_h
