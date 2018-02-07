#include <iostream>
#include <fstream>
#include <queue>
#include <stdlib.h>
#include <cstring>
#include "topBinForest.h"

void topBinForest::printForest(){
    baseForest::printForest();
    printf("There are %d bins.  The first %d levels are interleaved.\n",numOfBins, treeTopDepth);  
}


void topBinForest::makePredictions(const std::string& testFile){

    int numObservations;
    int numCorrectPredictions = 0;
    int numFeatures;
  //  int currentNode;
  int treesInBin;
  int i,j,currBinNum,q,m,n,k,p;
    int predictions[numOfBins][numOfClasses];
    std::priority_queue<int, std::vector<int>, std::greater<int> > nodesToProcess;
    double currentNumberFromFile; 
    int nodeFeature,leftNode,rightNode;
    double cutValueCurr;
    std::ifstream fin(testFile.c_str());

    fin >> currentNumberFromFile;
    numObservations = (int) currentNumberFromFile;
    fin >> currentNumberFromFile;
    numFeatures = (int) currentNumberFromFile;
    printf("\nThere are %d observations to test\n", numObservations);
    printf("There are %d features in each observation\n", numFeatures);

    int observationClasses[numObservations];
    int predictionClasses[numObservations];
    //TODO this was an int.  Should be doubles
    double observationFeatures[numFeatures] = {};

    int treesPerBin = numTreesInForest / numOfBins;
    int  binRemainder = numTreesInForest % numOfBins;
            int multiCurrentNode[treesPerBin+1];

    for( i = 0; i < numObservations; i++){
        memset(predictions, 0, sizeof(predictions));
        fin >> currentNumberFromFile;
        observationClasses[i] = (int)currentNumberFromFile;
        for( j=0; j < numFeatures; j++){
            fin >> currentNumberFromFile;
            observationFeatures[j] = currentNumberFromFile;
        }

        for( currBinNum = 0; currBinNum < numOfBins; currBinNum++){
            treesInBin = (currBinNum < binRemainder)? treesPerBin+1 : treesPerBin;
            for( q = 0; q < treesInBin; q++){multiCurrentNode[q] = q;}
            for( m = 0; m < treeTopDepth; m++){
                for( n = 0; n < treesInBin; n++){
nodeFeature=forest[currBinNum][multiCurrentNode[n]].returnFeature();
leftNode=forest[currBinNum][multiCurrentNode[n]].returnLeftNode();
    rightNode=forest[currBinNum][multiCurrentNode[n]].returnRightNode();
     cutValueCurr=forest[currBinNum][multiCurrentNode[n]].returnCutValue();
if(leftNode>0){
if(observationFeatures[nodeFeature]<cutValueCurr){
                        multiCurrentNode[n] =leftNode;
                    }else{
                        multiCurrentNode[n] =rightNode;
                    }
}
                }
            }
            // make predictions one tree at a time
            for( k=0; k < treesInBin; k++){
               // currentNode = k;
               nodeFeature=forest[currBinNum][multiCurrentNode[k]].returnFeature();
leftNode=forest[currBinNum][multiCurrentNode[k]].returnLeftNode();
    rightNode=forest[currBinNum][multiCurrentNode[k]].returnRightNode();
     cutValueCurr=forest[currBinNum][multiCurrentNode[k]].returnCutValue();
                while(leftNode>0){
                    if(observationFeatures[nodeFeature]<cutValueCurr){
                        multiCurrentNode[k] =leftNode;
                    }else{
                        multiCurrentNode[k] =rightNode;
                    }
nodeFeature=forest[currBinNum][multiCurrentNode[k]].returnFeature();
leftNode=forest[currBinNum][multiCurrentNode[k]].returnLeftNode();
    rightNode=forest[currBinNum][multiCurrentNode[k]].returnRightNode();
     cutValueCurr=forest[currBinNum][multiCurrentNode[k]].returnCutValue();
                }
                predictions[currBinNum][rightNode]++;
            }
        }
        ///////////////////////////////////////////////////////
        for( p=1; p < numOfBins; p++){//TODO this should be SIMD
            //#pragma omp simd
            for( q=0; q < numOfClasses; q++){
                predictions[0][q] += predictions[p][q];
            }
        }
        predictionClasses[i] = returnClassPrediction(predictions[0]);
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

void topBinForest::createForestFromCSV(const std::string& forestCSVFileName){

    std::ifstream fin(forestCSVFileName.c_str());
    int numValuesForTree;
    int numInnerNodes;
    totalNumberOfNodes = 0;
    numLeafNodesInForest = 0;
    double numFromCSV;
    int maxDepth = 0;

    int treesPerBin;
    int binRemainder;

    int firstPassNumberOfNodes = 0;
    int* numNodesInEachTree;
    int* startLocationOfEachTree = NULL;
    reverseNode * tempForest = NULL;

    //First pass through the csv file tells how much memory is needed.
    //First number in csv is the number of trees
    fin >> numFromCSV;
    numTreesInForest = (int)numFromCSV;
    numNodesInEachTree = new int[numTreesInForest];
    startLocationOfEachTree = new int[numTreesInForest];
    //Second number in csv is the number of classes
    fin >> numFromCSV;
    numOfClasses = (int)numFromCSV;

    for(int i = 0; i < numTreesInForest;i++){
        fin >> numFromCSV;
        numNodesInEachTree[i] = (int)numFromCSV;
        numInnerNodes = (numNodesInEachTree[i]-1)/2;
        numValuesForTree = numNodesInEachTree[i]*2+numInnerNodes;
        for(int j = 0; j < numValuesForTree;j++){
            fin >> numFromCSV;
        }
        firstPassNumberOfNodes+=numNodesInEachTree[i];
    }
    fin >> numFromCSV;
    if(!fin.eof()){
        printf("csv not exausted during first pass %d\n", firstPassNumberOfNodes);
        exit(1);
    }
    fin.clear();
    fin.seekg(0, std::ios::beg);

    //starting second pass to load data contiguously
    tempForest = new reverseNode[firstPassNumberOfNodes];
    if(tempForest == NULL){
        printf("memory for temp forest was not allocated");
        exit(1);
    }

    //Second pass over data
    //read first and second values and ignore
    fin >> numFromCSV;
    fin >> numFromCSV;

    //Create each tree one at a time.
    for(int i =0; i < numTreesInForest; i++){
        std::vector<double> numbers;
        //First number in each tree is the number of nodes 
        //in the current tree * 2 (map and nodes)
        fin >> numFromCSV;
        numInnerNodes = (numNodesInEachTree[i]-1)/2;
        numValuesForTree = numNodesInEachTree[i]*2+numInnerNodes;
        if(numNodesInEachTree[i]%2 == 0){
            printf("num of nodes is even"); 
            exit(1);
        }
        startLocationOfEachTree[i] =totalNumberOfNodes; 
        //Put all values pertaining to current tree in a vector
        for(int j = 0; j < numValuesForTree; j++){
            fin >> numFromCSV;
            numbers.push_back(numFromCSV);  // store the number 
        }
        //set root depth to 0
        tempForest[startLocationOfEachTree[i]].setDepthOfNode(0);
        //set root parent to -1
        tempForest[startLocationOfEachTree[i]].setParentNode(-1);

        for(int k = 0; k < numNodesInEachTree[i]; k++){
            if(numbers[k] > 0){
                tempForest[k+startLocationOfEachTree[i]].setNode(numbers[numNodesInEachTree[i]+numbers[k]-1],
                        int(numbers[numNodesInEachTree[i]*2+numbers[k]-1]),
                        startLocationOfEachTree[i] + int(numbers[k])*2-1,
                        startLocationOfEachTree[i] + int(numbers[k])*2);
                //set parent and depth of left node
                tempForest[startLocationOfEachTree[i]+ int(numbers[k])*2-1].setDepthOfNode(tempForest[k+startLocationOfEachTree[i]].returnDepthOfNode()+1);
                tempForest[startLocationOfEachTree[i]+ int(numbers[k])*2-1].setParentNode(k+startLocationOfEachTree[i]);
                //set parent and depth of right node
                tempForest[startLocationOfEachTree[i]+ int(numbers[k])*2].setDepthOfNode(tempForest[k+startLocationOfEachTree[i]].returnDepthOfNode()+1);
                tempForest[startLocationOfEachTree[i]+ int(numbers[k])*2].setParentNode(k+startLocationOfEachTree[i]);

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
    fin >> numFromCSV;
    if(!fin.eof()){
        printf("csv not exausted during second pass");
        exit(1);
    }else{
        fin.close();
    }

    //////////////////////////////////////////////////////////////////////////////////
    //At this point all nodes are in one contiguous data structure.
    //Start binning and rearranging trees
    forest = new baseNode*[numOfBins];
    treesPerBin = numTreesInForest / numOfBins;
    binRemainder = numTreesInForest % numOfBins;

    if(treesPerBin*numOfBins + binRemainder != numTreesInForest){
        printf("not all trees are binned.\n");
        exit(1);
    }

    int numOfNodesProcessed = 0;
    int numOfNodesPlacedInBins = 0;
    int startTree = 0;
    int endTree = treesPerBin;
    int nextUnusedNodeInBin;
    int currentNodeToProcess;
    int nodesInBin;

    for(int i = 0; i < numOfBins;i++){
        nextUnusedNodeInBin = 0;
        currentNodeToProcess = 0;
        if(i < binRemainder){endTree++;}

        nodesInBin = 0;
        for(int j = startTree; j < endTree; j++){
            nodesInBin += numNodesInEachTree[j];
        }
        numOfNodesPlacedInBins += nodesInBin;
        forest[i] = new baseNode[nodesInBin];

        //until processed, left and right pertain to tempForest locations.  These need to be changed when processed.  left is location in temp forest
        //start with all roots
        for(int j = startTree; j < endTree; j++){
            forest[i][nextUnusedNodeInBin++].setNode( 
                    tempForest[startLocationOfEachTree[j]].returnCutValue(),
                    tempForest[startLocationOfEachTree[j]].returnFeature(),
                    startLocationOfEachTree[j],
                    tempForest[startLocationOfEachTree[j]].returnRightNode());
        }
        while( tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnDepthOfNode() < treeTopDepth && currentNodeToProcess <= nextUnusedNodeInBin){
            if(tempForest[forest[i][currentNodeToProcess].returnLeftNode()].isInternalNode()){
                //create left node
                forest[i][nextUnusedNodeInBin].setNode(
                        tempForest[tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnLeftNode()].returnCutValue(),
                        tempForest[tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnLeftNode()].returnFeature(),
                        tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnLeftNode(),
                        0);
                //create right node
                forest[i][nextUnusedNodeInBin+1].setNode(
                        tempForest[tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnRightNode()].returnCutValue(),
                        tempForest[tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnRightNode()].returnFeature(),
                        tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnRightNode(),
                        0);

                forest[i][currentNodeToProcess].setLeftValue(nextUnusedNodeInBin++);
                forest[i][currentNodeToProcess].setRightValue(nextUnusedNodeInBin++);
            }else{
                forest[i][currentNodeToProcess].setNode(
                        -1,
                        -1,
                        -1,
                        tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnRightNode());
            }
            currentNodeToProcess++;
        }

        int startOfDepthFirst = currentNodeToProcess;
        int endOfDepthFirst = nextUnusedNodeInBin;

        for(int j = startOfDepthFirst; j < endOfDepthFirst; j++){
            //check to make sure the depth of each node at this stage is less greater than top depth.
            if(tempForest[forest[i][j].returnLeftNode()].returnDepthOfNode() < treeTopDepth){
                printf("A top level node is being processed where it shouldn't be.\n");
                printf("node depth: %d\nmin depth: %d\n", tempForest[forest[i][j].returnLeftNode()].returnDepthOfNode(), treeTopDepth);
                exit(1);
            }
            
            if(tempForest[forest[i][j].returnLeftNode()].isInternalNode()){
                //create left node
                forest[i][nextUnusedNodeInBin].setNode(
                        tempForest[tempForest[forest[i][j].returnLeftNode()].returnLeftNode()].returnCutValue(),
                        tempForest[tempForest[forest[i][j].returnLeftNode()].returnLeftNode()].returnFeature(),
                        tempForest[forest[i][j].returnLeftNode()].returnLeftNode(),
                        0);
                //create right node
                forest[i][nextUnusedNodeInBin+1].setNode(
                        tempForest[tempForest[forest[i][j].returnLeftNode()].returnRightNode()].returnCutValue(),
                        tempForest[tempForest[forest[i][j].returnLeftNode()].returnRightNode()].returnFeature(),
                        tempForest[forest[i][j].returnLeftNode()].returnRightNode(),
                        0);

                currentNodeToProcess = nextUnusedNodeInBin;
                forest[i][j].setLeftValue(nextUnusedNodeInBin++);
                forest[i][j].setRightValue(nextUnusedNodeInBin++);
            }else{
                forest[i][j].setNode(
                        -1,
                        -1,
                        -1,
                        tempForest[forest[i][j].returnLeftNode()].returnRightNode());
                continue;
            }

            while(currentNodeToProcess < nextUnusedNodeInBin){
if(maxDepth < tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnDepthOfNode()){
maxDepth = tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnDepthOfNode();
            }
                if(tempForest[forest[i][currentNodeToProcess].returnLeftNode()].isInternalNode()){
                    //create left node
                    forest[i][nextUnusedNodeInBin].setNode(
                            tempForest[tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnLeftNode()].returnCutValue(),
                            tempForest[tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnLeftNode()].returnFeature(),
                            tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnLeftNode(),
                            0);
                    //create right node
                    forest[i][nextUnusedNodeInBin+1].setNode(
                            tempForest[tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnRightNode()].returnCutValue(),
                            tempForest[tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnRightNode()].returnFeature(),
                            tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnRightNode(),
                            0);

                    forest[i][currentNodeToProcess].setLeftValue(nextUnusedNodeInBin++);
                    forest[i][currentNodeToProcess].setRightValue(nextUnusedNodeInBin++);
                }else{
                    forest[i][currentNodeToProcess].setNode(
                            -1,
                            -1,
                            -1,
                            tempForest[forest[i][currentNodeToProcess].returnLeftNode()].returnRightNode());
                }
                currentNodeToProcess++;
            }
        }
        if(nextUnusedNodeInBin != nodesInBin){
            printf("Not all nodes were processed for this bin.\n");
            printf("nodes in bins: %d\nnodes processed: %d\n", nodesInBin, nextUnusedNodeInBin);
            printf("This is bin #%d\n", i);
            exit(1);
        }
        numOfNodesProcessed += nextUnusedNodeInBin;
        startTree= endTree;
        endTree= startTree+treesPerBin;
    }


    if(numOfNodesPlacedInBins != firstPassNumberOfNodes){
        printf("all nodes were not placed in bins.\n");
        printf("nodes in bins: %d\ntotal number of nodes: %d\n", numOfNodesPlacedInBins, firstPassNumberOfNodes);
        exit(1);
    }

    if(numOfNodesProcessed != firstPassNumberOfNodes){
        printf("all nodes were not processed in final forest.\n");
        printf("nodes used: %d\nfirst pass: %d\n", numOfNodesProcessed, firstPassNumberOfNodes);
        exit(1);
    }
    printf("the maximum depth in this forest is %d.\n", maxDepth);

}

