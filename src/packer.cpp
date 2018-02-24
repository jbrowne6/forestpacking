#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <ctime>
#include "forestFactory.h"
#include "inferenceSamples.h"
//#include "naiveForest.h"
#include "improv1.h"
#include "improv3.h"
#include "improv4.h"
#include "improv5.h"
#include "improv2.h"
#include "naive.h"

int main(int argc, char* argv[]) {
    if (argc != 2){
        printf("packer requires 1 argument: 1 or 2\n");
        return -1;
    }

    int algorithmToRun = atoi(argv[1]);
    const std::string forestFileName = "res/forest.csv";
    const std::string testFileName = "res/testObservations.csv";
    std::clock_t    start;
    
    inferenceSamples observations(testFileName);
    //naiveForest tester(forestFileName);
    //improv4 tester(forestFileName,1, observations);
    //improv5 tester(forestFileName,1, observations,200);
    improv3 tester(forestFileName,1, observations);
    //improv2 tester(forestFileName,1);
    //improv1 tester(forestFileName,1);
    //naive tester(forestFileName,1);
    tester.printForest();
    printf("size of a node is %d\n",(int) sizeof(padNode));

    printf("starting run\n");
    start = std::clock();

   // tester.makePredictions(observations, observations.numObservations);
    tester.makePredictions(observations);

std::cout << "Time to test observations: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

    observations.percentRight();
    /*
    printf("starting run\n");

    start = std::clock();

    forestFactory FF;
    baseForest* forest = FF.makeForest(algorithmToRun);
    //forest->turnDebugModeOn();
    //forest->turnShowAllResultsOn();

    forest->createForestFromCSV(forestFileName);

    std::cout << "Time to read and manipulate the tree: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

    forest->printForest();

    start = std::clock();
    forest->makePredictions(testFileName);
    std::cout << "Time to make predictions: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;
*/
    return 0;
}
