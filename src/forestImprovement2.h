//This is improvement 2.  It builds on improvement 1.  This improvement
//focuses on removing leaf nodes from being interleaved with internal
//nodes.
//
//Improvement 1:It takes the naive forest and batches the inferences 
//instead of doing one inference at a time.  By batches I mean that multiple 
//test observations are run through a tree before moving on to the next tree.  
//The upside is that you get the locality of the tree, but at the expense of 
//storing all predictions for the batch.

#ifndef forestImprovement2_h
#define forestImprovement2_h

#include "padForest.h"
#include "inferenceSamples.h"
#include "batchPredictions.h"

class forestImprovement2 : public padForest 
{
    private:
    padNode ** forestRoots = NULL;

    public:
forestImprovement2(const std::string& forestCSVFileName, int source);
~forestImprovement2();
    void makePredictions(const inferenceSamples& observations, int batchSize, int startPosition);
    void makePredictions(const inferenceSamples& observations, int batchSize);
};

#endif //forestImprovement1_h
