//This is improvement 2.  Store each tree in pre-order format and remove leaf nodes.

#ifndef improv2_h
#define improv2_h

#include "padForest.h"
#include "inferenceSamples.h"
//#include "batchPredictions.h"


class improv2: public padForest 
{
    private:
    padNode ** forestRoots = NULL;

    public:
improv2(const std::string& forestCSVFileName, int source);
~improv2();
    void makePredictions(const inferenceSamples& observations);
};


#endif //improv2_h
