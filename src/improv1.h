//This is improvement 1.  Store each tree in pre-order format.

#ifndef improv1_h
#define improv1_h

#include "padForest.h"
#include "inferenceSamples.h"


class improv1: public padForest 
{
    private:
    padNode ** forestRoots = NULL;

    public:
improv1(const std::string& forestCSVFileName, int source);
~improv1();
    void makePredictions(const inferenceSamples& observations);
};


#endif //improv1_h
