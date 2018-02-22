#include "treeBin.h"

namespace {

    class repack 
    {
        public:
            int currentNode;
            padNodeStat* tree;
            padNode* realTree;
            void repackTree(int workingNode);
            repack( padNodeStat* tTree, padNode* rTree,int currNode ): tree(tTree), realTree(rTree), currentNode(currNode) {};
    };

    void repack::repackTree(int workingNode){

        int nodeNumberInTree = realTree[workingNode].returnRightNode();

        if(tree[nodeNumberInTree].isInternalNode()){

            int leftFreq = tree[tree[nodeNumberInTree].returnLeftNode()].returnFreq();
            int rightFreq = tree[tree[nodeNumberInTree].returnRightNode()].returnFreq();
            int leftNodeNum;
            int rightNodeNum;

            if(rightFreq > leftFreq){
                rightNodeNum = ++currentNode;
                realTree[rightNodeNum].setNode(tree[tree[nodeNumberInTree].returnRightNode()].returnCutValue(),
                        tree[tree[nodeNumberInTree].returnRightNode()].returnFeature(),
                        0,
                        tree[nodeNumberInTree].returnRightNode());

                repackTree(rightNodeNum);

                leftNodeNum = ++currentNode;
realTree[leftNodeNum].setNode(tree[tree[nodeNumberInTree].returnLeftNode()].returnCutValue(),
                        tree[tree[nodeNumberInTree].returnLeftNode()].returnFeature(),
                        0,
                        tree[nodeNumberInTree].returnLeftNode());

                repackTree(leftNodeNum);
            }else{

                leftNodeNum = ++currentNode;
                repackTree(leftNodeNum);

                rightNodeNum = ++currentNode;
realTree[rightNodeNum].setNode(tree[tree[nodeNumberInTree].returnRightNode()].returnCutValue(),
                        tree[tree[nodeNumberInTree].returnRightNode()].returnFeature(),
                        0,
                        tree[nodeNumberInTree].returnRightNode());

                repackTree(rightNodeNum);
            }

            realTree[workingNode].setLeftValue(leftNodeNum);
            realTree[workingNode].setRightValue(rightNodeNum);

        }else{
            realTree[workingNode].setNode(tree[nodeNumberInTree].returnCutValue(),
                    tree[nodeNumberInTree].returnFeature(),
                    tree[nodeNumberInTree].returnLeftNode(),
                    tree[nodeNumberInTree].returnRightNode());
        }
    }


}//end namespace

treeBin::treeBin(padNodeStat**& forest, int*& treeLength, int startTree, int finalTree, int headDepth){
    numOfTreesInBin = finalTree-startTree;
    depth = headDepth;
    int binSize = 0;

    for(int i = startTree; i < finalTree; i++){
        binSize += treeLength[i];
    }

    bin = new padNode [binSize];

    for(int j = startTree; j < finalTree; j++){
        bin[++firstFreeNode] = forest[j][0];
        //left value is the originating tree
        bin[firstFreeNode].setLeftValue(j);
        //right value is position in originating tree
        bin[firstFreeNode].setRightValue(0);
    }

    int workingTree;
    int workingPosition;
    for(int j = 0; j < headDepth; j++){
        ++currProcess;
        workingTree =bin[currProcess].returnLeftNode();
        workingPosition =bin[currProcess].returnRightNode();

        if(forest[workingTree][workingPosition].isInternalNode()){
            bin[currProcess].setLeftValue(++firstFreeNode);
            bin[firstFreeNode] = forest[workingTree][forest[workingTree][workingPosition].returnLeftNode()];
            bin[firstFreeNode].setLeftValue(workingTree);
            bin[firstFreeNode].setRightValue(forest[workingTree][workingPosition].returnLeftNode());

            bin[currProcess].setRightValue(++firstFreeNode);
            bin[firstFreeNode] = forest[workingTree][forest[workingTree][workingPosition].returnRightNode()];
            bin[firstFreeNode].setLeftValue(workingTree);
            bin[firstFreeNode].setRightValue(forest[workingTree][workingPosition].returnRightNode());
        }else{
            bin[currProcess] = forest[workingTree][workingPosition];
        }
    }

    int finalTopLevelNode = firstFreeNode; 
int currTreeNum;
    for(int j = ++currProcess ;j <= finalTopLevelNode  ;j++){
currTreeNum = bin[currProcess].returnLeftNode();
    repack repacker(forest[currTreeNum], bin, ++firstFreeNode);
    repacker.repackTree(j);
    }

}

treeBin::~treeBin(){
    delete[] bin;    
}

