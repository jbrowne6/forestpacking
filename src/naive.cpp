#include <queue>
#include "naive.h"

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
} //namespace

naive::naive(const std::string& forestCSVFileName, int source){
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
    }

    if(forestRoots == NULL){
        printf("forest is empty\n");
        exit(1);
    }

}

naive::~naive(){
    for(int i = 0; i < numTreesInForest; i++){
        delete[] forestRoots[i];
    }
    delete[] forestRoots;
}


void naive::makePredictions(const inferenceSamples& observations){

    int currentNode;
    int predictions[numOfClasses];

    for(int i = 0; i < observations.numObservations; i++){

        for(int p= 0; p < numOfClasses; p++){
            predictions[p]=0;
        }
        bool leftGo;
        for(int k=0; k < numTreesInForest; k++){
            currentNode = 0;
            while(forestRoots[k][currentNode].isInternalNode()){
              //  leftGo = forestRoots[k][currentNode].goLeft(observations.samplesMatrix[i][forestRoots[k][currentNode].returnFeature()]);
               //     currentNode = forestRoots[k][currentNode].returnLeftNode()*leftGo + forestRoots[k][currentNode].returnRightNode()*!leftGo; 
                if(forestRoots[k][currentNode].goLeft(observations.samplesMatrix[i][forestRoots[k][currentNode].returnFeature()])){
                    currentNode = forestRoots[k][currentNode].returnLeftNode(); 
                   continue;
                }
                    currentNode = forestRoots[k][currentNode].returnRightNode(); 
            }

            ++predictions[forestRoots[k][currentNode].returnRightNode()];
        }
        observations.predictedClasses[i] = returnClassPrediction(predictions, numOfClasses);
    }

}

