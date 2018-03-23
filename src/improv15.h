//This is the simplest implementation.  Stores tree in breadth first order.

#ifndef improv15_h
#define improv15_h

#include "padForest.h"
#include "inferenceSamples.h"
#include "batchPredictions.h"


class improv15: public padForest 
{
    private:
    padNode ** forestRoots = NULL;

    public:
improv15(const std::string& forestCSVFileName, int source);
~improv15();
    void makePredictions(const inferenceSamples& observations);
};


#endif //improv15_h
