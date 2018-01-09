#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <ctime>
#include "forest.h"

int main() {
const std::string forestFileName = "forest.csv";
const std::string testFileName = "testObservations.csv";

std::clock_t    start;
    start = std::clock();
    Forest forest;
    //forest.turnDebugModeOn();
    //forest.turnShowAllResultsOn();
    forest.createForestFromCSV(forestFileName);
 std::cout << "Time to read and manipulate the tree: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

        forest.printForest();

    start = std::clock();
    forest.makePredictions(testFileName);
    std::cout << "Time to make predictions: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

    return 0;
}
