#include "batchPredictions.h"
#include <iostream>
#include <cstring>

batchPredictions::batchPredictions(const int bSize, const int nClasses){
    batchSize = bSize;
    numOfClasses = nClasses;
    predictions = new int*[batchSize];
    for(int i = 0; i < batchSize; i++){
predictions[i] = new int[nClasses];
    }
    if(predictions == NULL){
        printf("memory for predictions was not allocated\n");
        exit(1);
    }
}

batchPredictions::~batchPredictions(){
    for(int i = 0; i < batchSize; i++){
delete[] predictions[i];
    }
    delete[] predictions;
}


void batchPredictions::zeroizePredictions(){
    for(int i = 0; i<batchSize; i++){
        std::memset(predictions[i], 0, numOfClasses*sizeof(int));
    }
}
