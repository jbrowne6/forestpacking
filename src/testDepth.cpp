#include <queue>
#include <iostream>
#include <fstream>
#include <vector>
#include "testDepth.h"

namespace {
    int maxDepth = 0;
    double bias = 0;
    double numForBias = 0;
						std::vector<int> depthRecord;

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

            padNodeStat* tree;
            padNode* realTree;
            int repackTree(int workingNode, int depth);
            repack( int eP, padNodeStat* tTree, padNode* rTree): endPosition(eP), tree(tTree), realTree(rTree) {};
    };

    int repack::repackTree(int workingNode, int depth){

        int currDepth = depth+1;
        if(maxDepth < currDepth){
            maxDepth = currDepth;
        }
        if(tree[workingNode].isInternalNode()){

            int thisNodesLocation = ++currentNode;
            if(thisNodesLocation > endPosition){
                printf("Moving into class node area\nendP:%d\n", endPosition);
                exit(1);
            }
            int leftFreq = tree[tree[workingNode].returnLeftNode()].returnFreq();
            int rightFreq = tree[tree[workingNode].returnRightNode()].returnFreq();
            int leftNodeNum;
            int rightNodeNum;
            if(rightFreq > leftFreq){
                rightNodeNum = repackTree(tree[workingNode].returnRightNode(), currDepth);
                leftNodeNum = repackTree(tree[workingNode].returnLeftNode(), currDepth);
            }else{
                leftNodeNum = repackTree(tree[workingNode].returnLeftNode(), currDepth);
                rightNodeNum = repackTree(tree[workingNode].returnRightNode(), currDepth);
            }

                ++numForBias; 
            if(!((rightFreq == 0) && (leftFreq == 0)) ){
                bias += abs((double)(rightFreq - leftFreq)/(double)(rightFreq+leftFreq));
                //bias += abs((double)(rightFreq - leftFreq));
            }

            realTree[thisNodesLocation].setNode(tree[workingNode].returnCutValue(),
                    tree[workingNode].returnFeature(),
                    leftNodeNum,
                    rightNodeNum
                    );

            return(thisNodesLocation);

        }else{
						//depth determination
if(depthRecord.size() < (unsigned)depth){
depthRecord.resize(depth);
}
++depthRecord[depth];
            return(endPosition + tree[workingNode].returnClass());

        }
    }
} //namespace

testDepth::testDepth(const std::string& forestCSVFileName, int source, const inferenceSamples& observations){
    if(source == 1){
        std::ifstream fin(forestCSVFileName.c_str());
        int numValuesForTree;
        int numInnerNodes;
        int numInnerNodesActual;
        totalNumberOfNodes = 0;
        int numLeafNodesInForest = 0;
        double num;
        padNodeStat ** tempForestRoots;
        double avgDepth = 0;
        //First number in csv is the number of trees
        fin >> num;
        numTreesInForest = (int)num;
        //Second number in csv is the number of classes
        fin >> num;
        numOfClasses = (int)num;

        tempForestRoots = new padNodeStat*[numTreesInForest];
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
            tempForestRoots[i] = new padNodeStat[numNodesInTree[i]];

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

        int currentNode = 0;
//#pragma omp parallel for schedule(static) private(currentNode)
        for(int i = 0; i < observations.numObservations; i++){

            for(int k=0; k < numTreesInForest; k++){
                currentNode = 0;
                while(tempForestRoots[k][currentNode].isInternalNode()){
                    ++avgDepth;
                    if(tempForestRoots[k][currentNode].goLeft(observations.samplesMatrix[i][tempForestRoots[k][currentNode].returnFeature()])){
                        currentNode = tempForestRoots[k][currentNode].returnLeftNode(); 
                        continue;
                    }
                    currentNode = tempForestRoots[k][currentNode].returnRightNode(); 
                }

            }
        }

        //TODO create new data structure and delete tempForest.
        forestRoots = new padNode*[numTreesInForest];

//#pragma omp parallel for schedule(static)
        for(int i = 0; i < numTreesInForest; i++){

            forestRoots[i] = new padNode[numOfClasses+(numNodesInTree[i]-1)/2];

            for(int j = 0; j < numOfClasses; j++){
                forestRoots[i][j+(numNodesInTree[i]-1)/2].setNode(-1.0,
                        int(0),
                        int(0),
                        int(j));
            }

            repack pack((numNodesInTree[i]-1)/2, tempForestRoots[i],forestRoots[i] );
            pack.repackTree(0, 0);

            delete[] tempForestRoots[i];
        }

std::ofstream outfile;
	outfile.open("depth.csv", std::ios_base::app);
	for (int i : depthRecord){
	outfile << i << "\n";
	}
	outfile.close();


        delete[] numNodesInTree;
        delete[] tempForestRoots;
        // forestRoots = tempForestRoots;
        printf("the average depth was %f; the average bias was %f\n", avgDepth/(double)(numTreesInForest*observations.numObservations),bias/numForBias*1000000);
        printf("the number of obs is %d\n", observations.numObservations);
        printf("the max depth of any trees is %d\n", maxDepth);
    }
    if(forestRoots == NULL){
        printf("forest is empty\n");
        exit(1);
    }

}

testDepth::~testDepth(){
    for(int i = 0; i < numTreesInForest; i++){
        delete[] forestRoots[i];
    }
    delete[] forestRoots;
}


void testDepth::makePredictions(const inferenceSamples& observations){

    int currentNode;
    int predictions[numOfClasses];

    for(int i = 0; i < observations.numObservations; i++){

        for(int p= 0; p < numOfClasses; p++){
            predictions[p]=0;
        }
        for(int k=0; k < numTreesInForest; k++){
            currentNode = 0;
            while(forestRoots[k][currentNode].isInternalNode()){

                currentNode = forestRoots[k][currentNode].nextNode(observations.samplesMatrix[i][forestRoots[k][currentNode].returnFeature()]);
            }

            ++predictions[forestRoots[k][currentNode].returnRightNode()];
        }
        observations.predictedClasses[i] = returnClassPrediction(predictions, numOfClasses);
    }

}

