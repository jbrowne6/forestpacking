#include "baseNode.h"
#include <stdio.h>

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
void Node::setLeftValue(int LVal){
    left = LVal;
}
void Node::setRightValue(int RVal){
    right = RVal;
}


