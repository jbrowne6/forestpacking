#include "padNode.h"
#include <stdio.h>

void padNode::setNode(double cVal, uint32_t feat, uint32_t l, uint32_t r){
    cutValue = cVal;
    feature = feat;
    left = l;
    right = r;
}

void padNode::printNode(){
    printf("cutValue %f, feature %d, left %d, right %d\n", cutValue, feature, left, right);
}

//double padNode::returnCutValue(){
 //   return cutValue;
//}


int padNode::returnLeftNode(){
    return left;
}


void padNode::setClass(int classNum){
right = classNum;
left = 0;
}

int padNode::returnClass(){
    return right;
}

bool padNode::goLeft(double featureValue){
    return featureValue < cutValue;
}

void padNode::setLeftValue(uint32_t LVal){
    left = LVal;
}
void padNode::setRightValue(uint32_t RVal){
    right = RVal;
}

