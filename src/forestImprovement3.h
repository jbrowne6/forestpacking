//This is improvement 3, builds on improvements 1 and 2.  This improvement
//stores the test observations as rows of features and columns of observations.
//This is the opposite of previous improvements.  
//
//Also, batches now keep track of which nodes in a batch stay together in a 
//tree in order to process them together.
//
//Improvement 2.  It builds on improvement 1.  This improvement
//focuses on removing leaf nodes from being interleaved with internal
//nodes.
//
//Improvement 1:It takes the naive forest and batches the inferences 
//instead of doing one inference at a time.  By batches I mean that multiple 
//test observations are run through a tree before moving on to the next tree.  
//The upside is that you get the locality of the tree, but at the expense of 
//storing all predictions for the batch.

#ifndef forestImprovement3_h
#define forestImprovement3_h

#include "padForest.h"
#include "inferenceSamples3.h"
#include "batchPredictions.h"

class forestImprovement3 : public padForest 
{
    private:
    padNode ** forestRoots = NULL;
    void traverseTree(std::vector<int>& obsInNode, const inferenceSamples3& obsMatrix, batchPredictions& batchPreds, int treeNum, int nodeNum, int startPos);

    public:
forestImprovement3(const std::string& forestCSVFileName, int source);
~forestImprovement3();
    void makePredictions(const inferenceSamples3& observations, int batchSize);
};

#endif //forestImprovement3_h
