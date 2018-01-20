#ifndef reverseNode_h
#define reverseNode_h

#include "baseNode.h"

class reverseNode : public baseNode 
{
    int depthOfNode;
    int parentNode;

    public:
    int returnDepthOfNode();
    int returnParentNode();
    void setDepthOfNode(int depth);
    void setParentNode(int parentNodeIndex);
    void printReverseNode();
};
#endif //reverseNode_h
