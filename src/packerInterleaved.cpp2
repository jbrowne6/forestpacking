#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <queue>
#include <ctime>
#include "forest.h"

//bool debugModeOn = false;
//bool showAllResults = false;

//Node * forest = NULL;
//int numTreesInForest;
//int totalNumberOfNodes;
//int numLeafNodesInForest;

/////////////////////////////////////////////////////
//void printForest(){
//    printf("\nThere are %d trees in the forest.\n", numTreesInForest);  
//    printf("The mean number of nodes per tree is %f\n", (float)totalNumberOfNodes/(float)numTreesInForest);
//    printf("There are %d leaves in the forest.\n", numLeafNodesInForest);  
//}
///////////////////////////////////////////////////////
//void printNode(Node currNode){
//    printf("\ncutValue %f, feature %d, left %d, right %d", currNode.cutValue,currNode.feature,currNode.left,currNode.right);
//}

///////////////////////////////////////////////////////////////////
/*void makePredictions(const std::string& testFile){

    int numObservations;
    int numCorrectPredictions = 0;
    int numFeatures;
    int currentNode;
    int maxNumberOfClasses = 10;
    int predictions[maxNumberOfClasses];
    int predictMaxValue;
    int predictMaxClass = 0;
    int completedTrees;
    std::priority_queue<int, std::vector<int>, std::greater<int> > nodesToProcess;
    double currentNumberFromFile; 
    std::ifstream fin(testFile.c_str());

    fin >> currentNumberFromFile;
    numObservations = (int) currentNumberFromFile;
    fin >> currentNumberFromFile;
    numFeatures = (int) currentNumberFromFile;
    printf("\nThere are %d observations to test\n", numObservations);
    printf("There are %d features in each observation\n", numFeatures);

    int observationClasses[numObservations];
    int predictionClasses[numObservations];
    int observationFeatures[numFeatures];

    for(int i = 0; i < numObservations; i++){
        fin >> currentNumberFromFile;
        observationClasses[i] = (int)currentNumberFromFile;
        for(int j=0; j < numFeatures; j++){
            fin >> currentNumberFromFile;
            observationFeatures[j] = (int)currentNumberFromFile;
        }

        for(int p= 0; p < maxNumberOfClasses; p++){
            predictions[p]=0;
        }
        ////////////////////////////////////////////////////////
        if(0){
            for(int k=0; k < numTreesInForest; k++){
                currentNode = k;
                while(forest[currentNode].left > 0){
                    if(observationFeatures[forest[currentNode].feature] < forest[currentNode].cutValue){
                        currentNode = forest[currentNode].left; 
                    }else{
                        currentNode = forest[currentNode].right; 
                    }
                }
                predictions[forest[currentNode].right]++;
            }

        }else{
            completedTrees = 0;
            for(int k=0; k < numTreesInForest; k++){
                nodesToProcess.push(k);
            }
            while(completedTrees < numTreesInForest){
                currentNode = nodesToProcess.top();
                nodesToProcess.pop();
                if(forest[currentNode].left > 0){
                    if(observationFeatures[forest[currentNode].feature] < forest[currentNode].cutValue){
                        nodesToProcess.push(forest[currentNode].left);
                    }else{
                        nodesToProcess.push(forest[currentNode].right);
                    }

                }else{
                    predictions[forest[currentNode].right]++;
                    completedTrees++;
                }

            }
            if(!nodesToProcess.empty()){
                printf("the priority queue was not emptied.\n");
                exit(1);
            }
        }
        ///////////////////////////////////////////////////////
        predictMaxValue = -1;
        for(int m=0; m<maxNumberOfClasses; m++){
            if(predictions[m] > predictMaxValue){
                predictMaxClass = m;
                predictMaxValue = predictions[m];
            }
        }
        predictionClasses[i] = predictMaxClass;
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

/////////////////////////////////////////////////////////////////
void createInterleavedForestFromCSV(const std::string& forestCSVFileName){
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
    Node * tempForest = NULL;

    //First pass through the csv file tells how much memory is needed.
    //First number in csv is the number of trees
    fin >> num;
    numTreesInForest = (int)num;
    numNodesInEachTree = new int[numTreesInForest];
    startLocationOfEachTree = new int[numTreesInForest];
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

    forest = new Node[firstPassNumberOfNodes];
    tempForest = new Node[firstPassNumberOfNodes];
    if(forest == NULL || tempForest == NULL){
        printf("memory for forest was not allocated");
        exit(1);
    }

    //Second pass over data
    //read first value and ignore
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
                tempForest[k+startLocationOfEachTree[i]].cutValue = numbers[numNodesInEachTree[i]+numbers[k]-1];
                tempForest[k+startLocationOfEachTree[i]].feature = int(numbers[numNodesInEachTree[i]*2+numbers[k]-1]);
                tempForest[k+startLocationOfEachTree[i]].left = startLocationOfEachTree[i] + int(numbers[k])*2-1;
                tempForest[k+startLocationOfEachTree[i]].right = startLocationOfEachTree[i] + int(numbers[k])*2;
            }else{
                tempForest[k+startLocationOfEachTree[i]].cutValue = -1.0;
                tempForest[k+startLocationOfEachTree[i]].feature =int(-1);
                tempForest[k+startLocationOfEachTree[i]].left = int(-1);
                tempForest[k+startLocationOfEachTree[i]].right = int(numbers[numNodesInEachTree[i]+ numInnerNodes +(-1*numbers[k])-1]);
                numLeafNodesInForest++;
            }
        }
        if(debugModeOn){
            if(i == 0){
                for(int p = 0; p < numNodesInEachTree[i]; p++){
                    printNode(tempForest[p+totalNumberOfNodes]);
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
        if(forest[currentNodeToProcess].feature != -1){//current node is interior node
            forest[nextUnusedNodeInForest] = tempForest[forest[currentNodeToProcess].left];
            forest[currentNodeToProcess].left = nextUnusedNodeInForest++;
            forest[nextUnusedNodeInForest] = tempForest[forest[currentNodeToProcess].right];
            forest[currentNodeToProcess].right = nextUnusedNodeInForest++;
        }
        currentNodeToProcess++;
    }
}


*/

int main() {
const std::string forestFileName = "forest.csv";
const std::string testFileName = "testObservations.csv";
    std::clock_t    start;
    start = std::clock();
    Forest forest;
    forest.createInterleavedForestFromCSV(forestFileName);
    std::cout << "Time to read and manipulate the tree: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;
         
    forest.printForest();


    start = std::clock();
    forest.makePredictions(testFileName);
    std::cout << "Time to make predictions: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

    return 0;
}
