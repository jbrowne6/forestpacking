#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <ctime>
//#include "baseForest.h"
//#include "perTreeForest.h"
#include "interleavedForest.h"

int main(int argc, char* argv[]) {
    if (argc != 2){
        printf("packer requires 1 argument: 1 or 2\n");
        return -1;
    }

    int algorithmToRun = atoi(argv[1]);
    const std::string forestFileName = "res/forest.csv";
    const std::string testFileName = "res/testObservations.csv";

    printf("starting run\n");

    std::clock_t    start;
    start = std::clock();
  //  baseForest forest;
  //perTreeForest forest;
  interleavedForest forest;
  forest.createForestFromCSV(forestFileName);

/*    switch(algorithmToRun){
        case 1:
            forest.createForestFromCSV(forestFileName);
            break;
        case 2:
            forest.createInterleavedForestFromCSV(forestFileName);
            break;
        default:
            printf("Put 1 or 2\n");
            return -1;
    }
    */

    std::cout << "Time to read and manipulate the tree: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

    forest.printForest();

    start = std::clock();
    forest.makePredictions(testFileName);
    std::cout << "Time to make predictions: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

    return 0;
}
