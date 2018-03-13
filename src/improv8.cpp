#include <queue>
#include "improv8.h"
#include <emmintrin.h>


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
            padNodeStat* tree;
            padNode* realTree;
            int repackTree(int workingNode);
            repack( padNodeStat* tTree, padNode* rTree): tree(tTree), realTree(rTree) {};
    };

    int repack::repackTree(int workingNode){

        int thisNodesLocation = ++currentNode;

        if(tree[workingNode].isInternalNode()){
            int leftFreq = tree[tree[workingNode].returnLeftNode()].returnFreq();
            int rightFreq = tree[tree[workingNode].returnRightNode()].returnFreq();
            int leftNodeNum;
            int rightNodeNum;
            if(rightFreq > leftFreq){
                rightNodeNum = repackTree(tree[workingNode].returnRightNode());
                leftNodeNum = repackTree(tree[workingNode].returnLeftNode());
            }else{
                leftNodeNum = repackTree(tree[workingNode].returnLeftNode());
                rightNodeNum = repackTree(tree[workingNode].returnRightNode());
            }

            realTree[thisNodesLocation].setNode(tree[workingNode].returnCutValue(),
                    tree[workingNode].returnFeature(),
                    leftNodeNum,
                    rightNodeNum
                    );
        }else{
            realTree[thisNodesLocation].setNode(tree[workingNode].returnCutValue(),
                    tree[workingNode].returnFeature(),
                    tree[workingNode].returnLeftNode(),
                    tree[workingNode].returnRightNode());
        }
        return(thisNodesLocation);
    }
} //namespace

//improv6::improv6(const std::string& forestCSVFileName, int source, const inferenceSamples& observations, int numberBins){
improv8::improv8(const std::string& forestCSVFileName, int source, const inferenceSamples& observations, int numberBins, int depthIntertwined){
    if(source == 1){
        std::ifstream fin(forestCSVFileName.c_str());
        //int numNodesInTree;
        int numValuesForTree;
        int numInnerNodes;
        int numInnerNodesActual;
        totalNumberOfNodes = 0;
        int numLeafNodesInForest = 0;
        double num;
        padNodeStat ** tempForestRoots;
        numOfBins = numberBins;
        // intDepth = depthIntertwined;

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

        int currentNode = 0;
        for(int i = 0; i < observations.numObservations; i++){

            for(int k=0; k < numTreesInForest; k++){
                currentNode = 0;
                while(tempForestRoots[k][currentNode].isInternalNode()){
                    if(tempForestRoots[k][currentNode].goLeft(observations.samplesMatrix[i][tempForestRoots[k][currentNode].returnFeature()])){
                        currentNode = tempForestRoots[k][currentNode].returnLeftNode(); 
                        continue;
                    }
                    currentNode = tempForestRoots[k][currentNode].returnRightNode(); 
                }
            }
        }

        forestRoots =  new treeBin2*[numOfBins]; 
        printf("starting binning\n");
        int finalTree;
        int startTree=0;
        int binSize = numTreesInForest/numberBins;
        int binRemainder = numTreesInForest%numberBins;
        for(int q = 0; q < numberBins; q++){
            finalTree = startTree+binSize;
            if(q < binRemainder){
                finalTree++;
            }

            if(finalTree > numTreesInForest){
                finalTree = numTreesInForest;
            }
            forestRoots[q] = new treeBin2(tempForestRoots, numNodesInTree, startTree, finalTree, depthIntertwined, numOfClasses);
            startTree = finalTree;
        }

        printf("finished binning\n");
        //TODO create new data structure and delete tempForest.
        //        forestRoots = new padNode*[numTreesInForest];

        for(int i = 0; i < numTreesInForest; i++){

            //           forestRoots[i] = new padNode[numNodesInTree[i]];

            //         repack pack(tempForestRoots[i],forestRoots[i] );
            //          pack.repackTree(0);

            delete[] tempForestRoots[i];
        }

        delete[] numNodesInTree;
        delete[] tempForestRoots;
    }         //Pull one more float so that eof is TRUE.


    if(forestRoots == NULL){
        printf("forest is empty\n");
        exit(1);
    }

    printf("finished all\n");
}

improv8::~improv8(){
    for(int i = 0; i < numOfBins; i++){
        // delete[] forestRoots[i];
    }
    delete[] forestRoots;
}


void improv8::makePredictions(const inferenceSamples& observations){

    int predictions[numOfClasses];
    int currentNode[forestRoots[0]->numOfTreesInBin];
    int numberNotInLeaf;
    int i, p, k, q;

        #pragma omp parallel for reduction(+:predictions[:numOfClasses]) private(q, p, k, numberNotInLeaf, currentNode)
    for(i = 0; i < observations.numObservations; i++){
   //     for(p = 0; p < memSizeOfOneObservation; p+=increment){
//__builtin_prefetch(&observations.samplesMatrix[i][p], 0, 3);
 //       }
        

        for( p= 0; p < numOfClasses;++p){
            predictions[p]=0;
        }


        for( k=0; k < numOfBins;++k){
            for( q=0; q<forestRoots[k]->numOfTreesInBin; q++){
                currentNode[q] = q;
__builtin_prefetch(&forestRoots[k]->bin[currentNode[q]], 0, 3);
            }
            numberNotInLeaf = 1;
            while(numberNotInLeaf > 0){
                numberNotInLeaf = forestRoots[k]->numOfTreesInBin;

                for( q=0; q<forestRoots[k]->numOfTreesInBin; ++q){

                    if(forestRoots[k]->bin[currentNode[q]].isInternalNode()){
                        currentNode[q] = forestRoots[k]->bin[currentNode[q]].nextNode(observations.samplesMatrix[i][forestRoots[k]->bin[currentNode[q]].returnFeature()]);
__builtin_prefetch(&forestRoots[k]->bin[currentNode[q]], 0, 3);
                        continue;
                    }
                    --numberNotInLeaf;
                }
            }

            for( q=0; q<forestRoots[k]->numOfTreesInBin; q++){
                ++predictions[forestRoots[k]->bin[currentNode[q]].returnRightNode()];
            }

        }
        observations.predictedClasses[i] = returnClassPrediction(predictions, numOfClasses);

    }
    //  printf("there were %d nodes traversed.\n", numNodeTraversals);
}

