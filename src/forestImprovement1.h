//This is improvement 1.  It takes the naive forest and batches the inferences 
//instead of doing one inference at a time.  By batches I mean that multiple 
//test observations are run through a tree before moving on to the next tree.  
//The upside is that you get the locality of the tree, but at the expense of 
//storing all predictions for the batch.

#ifndef forestImprovement1_h
#define forestImprovement1_h

#include "padForest.h"
#include "inferenceSamples.h"
#include "batchPredictions.h"


class forestImprovement1 : public padForest 
{
    private:
    padNode ** forestRoots = NULL;

    public:
forestImprovement1(const std::string& forestCSVFileName, int source);
~forestImprovement1();
    void makePredictions(const inferenceSamples& observations, int batchSize, int startPosition);
    void makePredictions(const inferenceSamples& observations, int batchSize);
};


#endif //forestImprovement1_h
