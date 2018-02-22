#include <queue>
#include "forestImprovement3.h"

namespace {

    inline int returnClassPrediction(int *classTotals, int numClasses){
        int predictMaxValue = -1;
        int predictMaxClass = -1;
        for(int m=0; m<numClasses; m++){
            if(classTotals[m] > predictMaxValue){
                predictMaxClass = m;
                predictMaxValue = classTotals[m];
            }
        }
        return predictMaxClass;
    }

    class repack 
    {
        public:
            int currentNode=-1;
            int endPosition;
            padNode* tree;
            padNode* realTree;
            int repackTree(int workingNode);
            repack( int eP, padNode* tTree, padNode* rTree): endPosition(eP), tree(tTree), realTree(rTree) {};
    };

    int repack::repackTree(int workingNode){

        if(tree[workingNode].isInternalNode()){

            int thisNodesLocation = ++currentNode;
            if(thisNodesLocation > endPosition){
                printf("Moving into class node area\nendP:%d\n", endPosition);
                exit(1);
            }
            realTree[thisNodesLocation].setNode(tree[workingNode].returnCutValue(),
                    tree[workingNode].returnFeature(),
                    repackTree(tree[workingNode].returnLeftNode()),
                    repackTree(tree[workingNode].returnRightNode()));

            return(thisNodesLocation);

        }else{
            return(endPosition + tree[workingNode].returnClass());
        }
    }

class batch {
    private:
        int batchSize;
        int lastRight;
        int firstRight;
        int currentObs;
        int* batchNums;
        int tempMover;

    public:
    batch(int bSize) {
    batchSize = bSize;
    lastRight = bSize -1;
    firstRight = bSize - 1;
    batchNums = new int[batchSize];
}
~batch(){
delete[] batchNums;
}
void moveRight(int nodeToMove){
    
    
};
void moveLeaf(int nodeToMove){
   int tempMover = batchNums[lastRight];
   batchNums[lastRight] = batchNums[nodeToMove];
batchNums[nodeToMove] = tempMover;
   --lastRight;
};
void moveLeft(){
++currentObs;    
};
};

} //namespace

void forestImprovement3::traverseTree(std::vector<int>& obsInNode, const inferenceSamples3& obsMatrix, batchPredictions& batchPreds, int treeNum, int nodeNum, int startPos){
    std::vector<int> leftObs(obsInNode.size());
    std::vector<int> rightObs(obsInNode.size());

    
    //if its a leaf node
    if(!forestRoots[treeNum][nodeNum].isInternalNode()){
        for(unsigned int i = 0; i < obsInNode.size(); i++){
            ++batchPreds.predictions[obsInNode[i]-startPos][forestRoots[treeNum][nodeNum].returnClass()];
        }
        return;
    }
    //if its an internal node
    for(unsigned int i = 0; i < obsInNode.size(); i++){
        if(forestRoots[treeNum][nodeNum].goLeft(obsMatrix.samplesMatrix[forestRoots[treeNum][nodeNum].returnFeature()][obsInNode[i]])){
            leftObs.push_back(obsInNode[i]);
        }else{
            rightObs.push_back(obsInNode[i]);
        }
    }

   /* while(!leftObs.empty()){
printf("%d ", leftObs.back());
leftObs.pop_back();
        }
     while(!rightObs.empty()){
printf("%d ", rightObs.back());
rightObs.pop_back();
        }
  */ 
    traverseTree(leftObs, obsMatrix, batchPreds, treeNum, forestRoots[treeNum][nodeNum].returnLeftNode(), startPos);
        traverseTree(rightObs, obsMatrix, batchPreds, treeNum, forestRoots[treeNum][nodeNum].returnRightNode(), startPos);
}

forestImprovement3::forestImprovement3(const std::string& forestCSVFileName, int source){
    if(source == 1){ //source==1 is csv
        std::ifstream fin(forestCSVFileName.c_str());
        int numNodesInTree;
        int numValuesForTree;
        int numInnerNodes;
        totalNumberOfNodes = 0;
        int numLeafNodesInForest = 0;
        double num;

        //First number in csv is the number of trees
        fin >> num;
        numTreesInForest = (int)num;
        //Second number in csv is the number of classes
        fin >> num;
        numOfClasses = (int)num;

        forestRoots = new padNode*[numTreesInForest];
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
            forestRoots[i] = new padNode[numNodesInTree];
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
                            int(0),
                            int(0),
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
    }else if (source == 2){
        std::ifstream fin(forestCSVFileName.c_str());
        //int numNodesInTree;
        int numValuesForTree;
        int numInnerNodes;
        int numInnerNodesActual;
        totalNumberOfNodes = 0;
        int numLeafNodesInForest = 0;
        double num;
        padNode ** tempForestRoots;

        //First number in csv is the number of trees
        fin >> num;
        numTreesInForest = (int)num;
        //Second number in csv is the number of classes
        fin >> num;
        numOfClasses = (int)num;

        tempForestRoots = new padNode*[numTreesInForest];
        if(tempForestRoots == NULL){
            printf("memory for forest was not allocated");
            exit(1);
        }
        int* numNodesInTree = new int[numTreesInForest];
        //Create each tree one at a time.
        for(int i =0; i < numTreesInForest; i++){
            std::vector<double> numbers;

            //First number in each tree is the number of nodes 
            //in the current tree * 2 (map and nodes)
            fin >> num;
            numNodesInTree[i] = (int)num;
            numInnerNodes = (numNodesInTree[i]-1)/2;
            numValuesForTree = numNodesInTree[i]*2+numInnerNodes;
            totalNumberOfNodes += numNodesInTree[i]; 

            if(numNodesInTree[i]%2 == 0){
                printf("num of nodes is even"); 
                exit(1);
            }
            //Put all values pertaining to current tree in a vector
            for(int j = 0; j < numValuesForTree; j++){
                fin >> num;
                numbers.push_back(num);  // store the number 
            }
            //Allocate space for this tree
            tempForestRoots[i] = new padNode[numNodesInTree[i]];
            // forestRoots[i] = new padNode[numInnerNodes+numOfClasses];
            if(tempForestRoots[i] == NULL){
                printf("memory not allocated for tree");
                exit(1);
            }
            numInnerNodesActual = 0;
            for(int k = 0; k < numNodesInTree[i]; k++){
                if(numbers[k] > 0){
                    tempForestRoots[i][k].setNode(numbers[numNodesInTree[i]+numbers[k]-1],
                            int(numbers[numNodesInTree[i]*2+numbers[k]-1]),
                            int(numbers[k])*2-1,
                            int(numbers[k])*2);
                    ++numInnerNodesActual;
                }else{
                    tempForestRoots[i][k].setNode(-1.0,
                            int(0),
                            int(0),
                            int(numbers[numNodesInTree[i]+ numInnerNodes +(-1*numbers[k])-1]));
                    ++numLeafNodesInForest;
                }
            }

            if(numInnerNodesActual != numInnerNodes ){
                printf("miscalculated inner Nodes: calc-%d, act-%d ", numInnerNodes, numInnerNodesActual);
                exit(1);
            }


            if(debugModeOn){
                if(i == 0){
                    for(int p = 0; p < numNodesInTree[i]; p++){
                        tempForestRoots[i][p].printNode();
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

        //TODO create new data structure and delete tempForest.
        forestRoots = new padNode*[numTreesInForest];

        for(int i = 0; i < numTreesInForest; i++){

            forestRoots[i] = new padNode[numOfClasses+(numNodesInTree[i]-1)/2];

            for(int j = 0; j < numOfClasses; j++){
                forestRoots[i][j+(numNodesInTree[i]-1)/2].setNode(-1.0,
                        int(0),
                        int(0),
                        int(j));
            }

            repack pack((numNodesInTree[i]-1)/2, tempForestRoots[i],forestRoots[i] );
            pack.repackTree(0);

            delete[] tempForestRoots[i];
        }

        delete[] numNodesInTree;
        delete[] tempForestRoots;
        // forestRoots = tempForestRoots;
    }

    if(forestRoots == NULL){
        printf("forest is empty\n");
        exit(1);
    }

}

forestImprovement3::~forestImprovement3(){
    for(int i = 0; i < numTreesInForest; i++){
        delete[] forestRoots[i];
    }
    delete[] forestRoots;
}


void forestImprovement3::makePredictions(const inferenceSamples3& observations, int batchSize){
    batchPredictions bPreds(batchSize,numOfClasses);
    int observationNum; 
    int stopPosition = batchSize;

    for(int startPosition = 0; startPosition < observations.numObservations;){
        if(stopPosition > observations.numObservations){
            stopPosition = observations.numObservations;
        }
        bPreds.zeroizePredictions();
        std::vector<int> initialSamples (stopPosition-startPosition);
        for(int p =0; p < (stopPosition-startPosition); p++){
initialSamples[p] = p + startPosition;
        }
        
        for(int k=0; k < numTreesInForest; k++){
            traverseTree(initialSamples, observations, bPreds, k,0, startPosition);
        }

        observationNum = -1;
        for(int i = startPosition; i < stopPosition; i++){
            observations.predictedClasses[i] = returnClassPrediction(bPreds.predictions[++observationNum], numOfClasses);
        }
        startPosition += batchSize;
        stopPosition += batchSize;
    }
}
