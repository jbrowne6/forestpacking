#include <iostream>
#include <fstream>
#include <queue>
#include <stdlib.h>
#include <string.h>
#include "interleavedForest.h"

void interleavedForest::makePredictions(const std::string& testFile){
    int numObservations;
    int numCorrectPredictions = 0;
    int numFeatures;
    int currentNode;
    int predictions[numOfClasses];
    int completedTrees;
    std::priority_queue<int, std::vector<int>, std::greater<int> > nodesToProcess;
    double currentNumberFromFile; 
    std::ifstream fin(testFile.c_str());
    int *observationClasses;
    int *predictionClasses;
    int *observationFeatures;

    fin >> currentNumberFromFile;
    numObservations = (int) currentNumberFromFile;
    fin >> currentNumberFromFile;
    numFeatures = (int) currentNumberFromFile;
    printf("\nThere are %d observations to test\n", numObservations);
    printf("There are %d features in each observation\n", numFeatures);

    observationClasses = new int[numObservations];
    predictionClasses = new int[numObservations];
    observationFeatures = new int[numFeatures];

    for(int i = 0; i < numObservations; i++){
        fin >> currentNumberFromFile;
        observationClasses[i] = (int)currentNumberFromFile;
        for(int j=0; j < numFeatures; j++){
            fin >> currentNumberFromFile;
            observationFeatures[j] = (int)currentNumberFromFile;
        }

            memset(predictions, 0, sizeof(predictions));
        ////////////////////////////////////////////////////////
        if(1){ // make predictions one tree at a time
            for(int k=0; k < numTreesInForest; k++){
                currentNode = k;
                while(forest[currentNode].isInternalNode()){
                    if(forest[currentNode].goLeft(observationFeatures[forest[currentNode].returnFeature()])){
                        currentNode = forest[currentNode].returnLeftNode(); 
                    }else{
                        currentNode = forest[currentNode].returnRightNode(); 
                    }
                }
                predictions[forest[currentNode].returnRightNode()]++;
            }

        }else{// make predictions in order of memory access 
            completedTrees = 0;
            for(int k=0; k < numTreesInForest; k++){
                nodesToProcess.push(k);
            }
            while(completedTrees < numTreesInForest){
                currentNode = nodesToProcess.top();
                nodesToProcess.pop();
                if(forest[currentNode].isInternalNode()){
                    if(forest[currentNode].goLeft(observationFeatures[forest[currentNode].returnFeature()])){
                        nodesToProcess.push(forest[currentNode].returnLeftNode());
                    }else{
                        nodesToProcess.push(forest[currentNode].returnRightNode());
                    }

                }else{
                    predictions[forest[currentNode].returnRightNode()]++;
                    completedTrees++;
                }

            }
            if(!nodesToProcess.empty()){
                printf("the priority queue was not emptied.\n");
                exit(1);
            }
        }
        ///////////////////////////////////////////////////////
        predictionClasses[i] = returnClassPrediction(predictions);
        if(showAllResults){
            printf("observation%d actual %d predicted %d\n", i, observationClasses[i],predictionClasses[i]);
        }
        if(observationClasses[i] == predictionClasses[i]){
            numCorrectPredictions++;
        }
    }

    //Pull one more float so that eof is TRUE.
    fin >> currentNumberFromFile;
    if(!fin.eof()){
        printf("test csv not exausted");
        exit(1);
    }else{
        fin.close();
    }
    printf("%f%% of the predictions were correct\n",100.0*(float)numCorrectPredictions/(float)numObservations);

}


void interleavedForest::createForestFromCSV(const std::string& forestCSVFileName){
    std::ifstream fin(forestCSVFileName.c_str());
    int numValuesForTree;
    int numInnerNodes;
    int firstPassNumberOfNodes = 0;
    int* numNodesInEachTree;
    int* startLocationOfEachTree = NULL;
    // int currentNodeInForest;
    totalNumberOfNodes = 0;
    numLeafNodesInForest = 0;
    double num;
    baseNode * tempForest = NULL;

    //First pass through the csv file tells how much memory is needed.
    //First number in csv is the number of trees
    fin >> num;
    numTreesInForest = (int)num;
    numNodesInEachTree = new int[numTreesInForest];
    startLocationOfEachTree = new int[numTreesInForest];
    //Second number in csv is the number of classes
    fin >> num;
    numOfClasses = (int)num;

    for(int i = 0; i < numTreesInForest;i++){
        fin >> num;
        numNodesInEachTree[i] = (int)num;
        numInnerNodes = (numNodesInEachTree[i]-1)/2;
        numValuesForTree = numNodesInEachTree[i]*2+numInnerNodes;
        for(int j = 0; j < numValuesForTree;j++){
            fin >> num;
        }
        firstPassNumberOfNodes+=numNodesInEachTree[i];
    }
    fin >> num;
    if(!fin.eof()){
        printf("csv not exausted during first pass %d\n", firstPassNumberOfNodes);
        exit(1);
    }
    fin.clear();
    fin.seekg(0, std::ios::beg);

    forest = new baseNode[firstPassNumberOfNodes];
    tempForest = new baseNode[firstPassNumberOfNodes];
    if(forest == NULL || tempForest == NULL){
        printf("memory for forest was not allocated");
        exit(1);
    }

    //Second pass over data
    //read first and second values and ignore
    fin >> num;
    fin >> num;

    //Create each tree one at a time.
    for(int i =0; i < numTreesInForest; i++){
        std::vector<double> numbers;
        //First number in each tree is the number of nodes 
        //in the current tree * 2 (map and nodes)
        fin >> num;
        numInnerNodes = (numNodesInEachTree[i]-1)/2;
        numValuesForTree = numNodesInEachTree[i]*2+numInnerNodes;
        if(numNodesInEachTree[i]%2 == 0){
            printf("num of nodes is even"); 
            exit(1);
        }
        startLocationOfEachTree[i] =totalNumberOfNodes; 
        //Put all values pertaining to current tree in a vector
        for(int j = 0; j < numValuesForTree; j++){
            fin >> num;
            numbers.push_back(num);  // store the number 
        }
        for(int k = 0; k < numNodesInEachTree[i]; k++){
            if(numbers[k] > 0){
                tempForest[k+startLocationOfEachTree[i]].setNode(numbers[numNodesInEachTree[i]+numbers[k]-1],
                        int(numbers[numNodesInEachTree[i]*2+numbers[k]-1]),
                        startLocationOfEachTree[i] + int(numbers[k])*2-1,
                        startLocationOfEachTree[i] + int(numbers[k])*2);
            }else{
                tempForest[k+startLocationOfEachTree[i]].setNode(-1.0,
                        -1,
                        -1,
                        int(numbers[numNodesInEachTree[i]+ numInnerNodes +(-1*numbers[k])-1]));
                numLeafNodesInForest++;
            }
        }
        if(debugModeOn){
            if(i == 0){
                for(int p = 0; p < numNodesInEachTree[i]; p++){
                    tempForest[p+totalNumberOfNodes].printNode();
                }
            }
        }
        //Print current tree.  Just for checking.
        if(debugModeOn && 0){
            printf("start of tree %d.\n", i);
            for (unsigned int z=0; z<numbers.size(); z++)
                std::cout << numbers[z] << '\n';
        }

        totalNumberOfNodes += numNodesInEachTree[i]; 
    }
    if(totalNumberOfNodes != firstPassNumberOfNodes){
        printf("number of nodes differs between passes.\n");
        printf("First pass: %d\nSecond pass: %d\n", firstPassNumberOfNodes, totalNumberOfNodes);
        exit(1);
    }
    //Pull one more float so that eof is TRUE.
    fin >> num;
    if(!fin.eof()){
        printf("csv not exausted during second pass");
        exit(1);
    }else{
        fin.close();
    }

    //Now the entire forest is in forestTemp.  Reorganize for locality.
    int nextUnusedNodeInForest = 0;
    int currentNodeToProcess = 0;
    //until processed, left denotes origional tree and right denotes location in tree

    //start with all the roots
    for(int i = 0; i < numTreesInForest; i++){
        forest[nextUnusedNodeInForest++] = tempForest[startLocationOfEachTree[i]];
    }

    //loop through each of the trees interleaving the nodes
    while(currentNodeToProcess < firstPassNumberOfNodes){
        if(forest[currentNodeToProcess].isInternalNode()){//current node is interior node
            forest[nextUnusedNodeInForest] = tempForest[forest[currentNodeToProcess].returnLeftNode()];
            forest[currentNodeToProcess].setLeftValue(nextUnusedNodeInForest++);
            forest[nextUnusedNodeInForest] = tempForest[forest[currentNodeToProcess].returnRightNode()];
            forest[currentNodeToProcess].setRightValue(nextUnusedNodeInForest++);
        }
        currentNodeToProcess++;
    }
}

