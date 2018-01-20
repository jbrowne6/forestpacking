#include <stdio.h>
#include "reverseNode.h"

void reverseNode::printReverseNode(){
    printf("cutVal %f, feat %d, l %d, r %d, depth %d, pn %d\n", returnCutValue(), returnFeature(), returnLeftNode(), returnRightNode(), returnDepthOfNode(), returnParentNode());
}

int reverseNode::returnDepthOfNode(){
return depthOfNode;
}

int reverseNode::returnParentNode(){
return parentNode;
}

void reverseNode::setDepthOfNode(int depth){
depthOfNode = depth;
}

void reverseNode::setParentNode(int parentNodeIndex){
parentNode = parentNodeIndex;
}
