//This is improvement 3.  Builds on improv1. Build tree depth first based on usage stats 
//instead of pre-order.

#ifndef improv3_h
#define improv3_h

#include "padForest.h"
#include "inferenceSamples.h"
#include "padNodeStat.h"


class improv3: public padForest 
{
    private:
    padNode ** forestRoots = NULL;

    public:
improv3(const std::string& forestCSVFileName, int source, const inferenceSamples& observations);
~improv3();
    void makePredictions(const inferenceSamples& observations);
};


#endif //improv3_h
