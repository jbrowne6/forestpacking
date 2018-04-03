//This is improvement 4.  Builds on improv2. Build tree depth first based on usage stats 
//instead of pre-order.

#ifndef improv4_h
#define improv4_h

#include "padForest.h"
#include "inferenceSamples.h"
#include "padNodeStat.h"


class improv4: public padForest 
{
    private:
    padNode ** forestRoots = NULL;

    public:
improv4(const std::string& forestCSVFileName, int source, const inferenceSamples& observations);
~improv4();
    void makePredictions(const inferenceSamples& observations);
};


#endif //improv4_h
