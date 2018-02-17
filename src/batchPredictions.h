#ifndef batchPredictions_h
#define batchPredictions_h

#include <stdlib.h>
#include <iostream>
//#include <fstream>


class batchPredictions
{
    public:
        batchPredictions(const int bSize, const int nClasses);
        ~batchPredictions();
        void zeroizePredictions();

   // protected:
        int batchSize;
        int numOfClasses;
        int** predictions = NULL; 

};
#endif //batchPredictions.h
