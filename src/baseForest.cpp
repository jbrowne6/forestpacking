#include <iostream>
#include <fstream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <typeinfo>
#include <vector>
#include "baseForest.h"

void baseForest::printForest(){
    printf("\nThere are %d trees in the forest.\n", numTreesInForest);  
    printf("The mean number of nodes per tree is %f\n", (float)totalNumberOfNodes/(float)numTreesInForest);
    printf("\nThere are %d leaves in the forest.\n", numLeafNodesInForest); 
}

void baseForest::createForestFromCSV(const std::string& forestCSVFileName){
    printf("not implemented in base class\n");
}


void baseForest::makePredictions(const std::string& testFile){
    printf("not implemented in base class\n");
}

void baseForest::turnDebugModeOn(){
    debugModeOn = true;
}

void baseForest::turnShowAllResultsOn(){
    showAllResults = true;
}

int baseForest::returnClassPrediction(int *classTotals){
    int predictMaxValue = -1;
    int predictMaxClass = -1;
    for(int m=0; m<numOfClasses; m++){
        if(classTotals[m] > predictMaxValue){
            predictMaxClass = m;
            predictMaxValue = classTotals[m];
        }
    }
    return predictMaxClass;
}
