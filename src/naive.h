//This is the simplest implementation.  Stores tree in breadth first order.

#ifndef naive_h
#define naive_h

#include "padForest.h"
#include "inferenceSamples.h"


class naive: public padForest 
{
    private:
    padNode ** forestRoots = NULL;

    public:
naive(const std::string& forestCSVFileName, int source);
~naive();
    void makePredictions(const inferenceSamples& observations);
    void makePredictionsMultiObs(const inferenceSamples& observations, int numCores);
    void makePredictionsMultiTree(const inferenceSamples& observations, int numCores);
};


#endif //naive_h
