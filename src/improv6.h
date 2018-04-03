//This is improvement 6.  Builds on improv4. Build tree depth first based on usage stats instead of pre-order.
//This improv bins top levels then does a pseudo pre-order.

#ifndef improv6_h
#define improv6_h

#include "padForest.h"
#include "inferenceSamples.h"
#include "padNodeStat.h"
#include "treeBin2.h"

class improv6: public padForest 
{
    private:
    treeBin2** forestRoots = NULL;
    int numOfBins;
    //int intDepth;

    public:
improv6(const std::string& forestCSVFileName, int source, const inferenceSamples& observations, int numberBins, int depthIntertwined);
~improv6();
    void makePredictions(const inferenceSamples& observations);
};


#endif //improv6_h
