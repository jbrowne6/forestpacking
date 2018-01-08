#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include "forest.h"

void Node::setNode(double cVal, int feat, int l, int r){
    cutValue = cVal;
    feature = feat;
    left = l;
    right = r;
}

void Node::printNode(){
    printf("\ncutValue %f, feature %d, left %d, right %d", cutValue, feature, left, right);
}

double Node::returnCutValue(){
    return cutValue;
}
int Node::returnFeature(){
    return feature;
}
int Node::returnLeftNode(){
    return left;
}
int Node::returnRightNode(){
    return right;
}
bool Node::isInternalNode(){
    return left > 0;
}
bool Node::goLeft(double featureValue){
return featureValue < cutValue;
}

//Forest() : debugModeOn(false), showAllResults(false){}

void Forest::printForest(){
printf("\nThere are %d trees in the forest.\n", numTreesInForest);  
    printf("The mean number of nodes per tree is %f\n", (float)totalNumberOfNodes/(float)numTreesInForest);
    printf("\nThere are %d leaves in the forest.\n", numLeafNodesInForest); 
}

void Forest::createForestFromCSV(const std::string& forestCSVFileName){
std::ifstream fin(forestCSVFileName.c_str());
    int numNodesInTree;
    int numValuesForTree;
    int numInnerNodes;
    totalNumberOfNodes = 0;
    numLeafNodesInForest = 0;
    double num;

    //First number in csv is the number of trees
    fin >> num;
    numTreesInForest = (int)num;
    //Second number in csv is the number of classes
    fin >> num;
    numOfClasses = (int)num;

    forestRoots = new Node*[numTreesInForest];
    if(forestRoots == NULL){
        printf("memory for forest was not allocated");
        exit(1);
    }

    //Create each tree one at a time.
    for(int i =0; i < numTreesInForest; i++){
        std::vector<double> numbers;

        //First number in each tree is the number of nodes 
        //in the current tree * 2 (map and nodes)
        fin >> num;
        numNodesInTree = (int)num;
        numInnerNodes = (numNodesInTree-1)/2;
        numValuesForTree = numNodesInTree*2+numInnerNodes;
        totalNumberOfNodes += numNodesInTree; 

        if(numNodesInTree%2 == 0){
            printf("num of nodes is even"); 
            exit(1);
        }
        //Put all values pertaining to current tree in a vector
        for(int j = 0; j < numValuesForTree; j++){
            fin >> num;
            numbers.push_back(num);  // store the number 
        }
        //Allocate space for this tree
        forestRoots[i] = new Node[numNodesInTree];
        if(forestRoots[i] == NULL){
            printf("memory not allocated for tree");
            exit(1);
        }
        for(int k = 0; k < numNodesInTree; k++){
            if(numbers[k] > 0){
                forestRoots[i][k].setNode(numbers[numNodesInTree+numbers[k]-1],
                        int(numbers[numNodesInTree*2+numbers[k]-1]),
                        int(numbers[k])*2-1,
                        int(numbers[k])*2);
            }else{
                forestRoots[i][k].setNode(-1.0,
                        int(-1),
                        int(-1),
                        int(numbers[numNodesInTree+ numInnerNodes +(-1*numbers[k])-1]));
                numLeafNodesInForest++;
            }
        }
        if(debugModeOn){
            if(i == 0){
                for(int p = 0; p < numNodesInTree; p++){
                    forestRoots[i][p].printNode();
                }
            }
        }


        //Print current tree.  Just for checking.
        if(debugModeOn){
            printf("start of tree %d.\n", i);
            for (unsigned int z=0; z<numbers.size(); z++)
                std::cout << numbers[z] << '\n';
        }
    }

    //Pull one more float so that eof is TRUE.
    fin >> num;
    if(!fin.eof()){
        printf("csv not exausted");
        exit(1);
    }else{
        fin.close();
    }
    if(forestRoots == NULL){
        printf("forest is empty\n");
        exit(1);
    }
}

void Forest::makePredictions(const std::string& testFile){

    int numObservations;
    int numCorrectPredictions = 0;
    int numFeatures;
    int currentNode;
   // int maxNumberOfClasses = 10;
    int predictions[numOfClasses];
    int predictMaxValue;
    int predictMaxClass = 0;
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

        for(int p= 0; p < numOfClasses; p++){
            predictions[p]=0;
        }
        for(int k=0; k < numTreesInForest; k++){
            currentNode = 0;
            while(forestRoots[k][currentNode].isInternalNode()){
                if(forestRoots[k][currentNode].goLeft(observationFeatures[forestRoots[k][currentNode].returnFeature()])){
                    currentNode = forestRoots[k][currentNode].returnLeftNode(); 
                }else{
                    currentNode = forestRoots[k][currentNode].returnRightNode(); 
                }
            }

            predictions[forestRoots[k][currentNode].returnRightNode()]++;
        }

        predictMaxValue = -1;
        for(int m=0; m<numOfClasses; m++){
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
    printf("%f%% of the predictions were correct\n", 100.0*(float)numCorrectPredictions/(float)numObservations);
}


void Forest::turnDebugModeOn(){
debugModeOn = true;
}

void Forest::turnShowAllResultsOn(){
    showAllResults = true;
}
