#include "baseNode.h"
#include <stdio.h>

void baseNode::setNode(double cVal, int feat, int l, int r){
    cutValue = cVal;
    feature = feat;
    left = l;
    right = r;
}

void baseNode::printNode(){
    printf("cutValue %f, feature %d, left %d, right %d\n", cutValue, feature, left, right);
}

double baseNode::returnCutValue(){
    return cutValue;
}
int baseNode::returnFeature(){
    return feature;
}
int baseNode::returnLeftNode(){
    return left;
}
int baseNode::returnRightNode(){
    return right;
}
bool baseNode::isInternalNode(){
    return left > 0;
}
bool baseNode::goLeft(double featureValue){
    return featureValue < cutValue;
}
void baseNode::setLeftValue(int LVal){
    left = LVal;
}
void baseNode::setRightValue(int RVal){
    right = RVal;
}


