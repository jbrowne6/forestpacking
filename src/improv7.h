//This is improvement 6.  Builds on improv4. Build tree depth first based on usage stats instead of pre-order.
//This improv bins top levels then does a pseudo pre-order.

#ifndef improv7_h
#define improv7_h

#include "padForest.h"
#include "inferenceSamples.h"
//#include "batchPredictions.h"
#include "padNodeStat.h"
#include "treeBin2.h"

class improv7: public padForest 
{
    private:
    treeBin2** forestRoots = NULL;
    int numOfBins;

    public:
improv7(const std::string& forestCSVFileName, int source, const inferenceSamples& observations, int numberBins, int depthIntertwined);
~improv7();
    void makePredictions(const inferenceSamples& observations);
};


#endif //improv7_h
