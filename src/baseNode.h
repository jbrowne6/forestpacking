#ifndef baseNode_h
#define baseNode_h

class baseNode
{
    double cutValue;
    int feature;
    int left;
    int right;

    public:
    void setNode(double cVal, int feat, int l, int r);
    void printNode();
    double returnCutValue();
    int returnFeature();
    int returnLeftNode(); //should have been Value instead of Node
    int returnRightNode();//should have been Value instead of Node
    void setLeftValue(int LVal);
    void setRightValue(int RVal); 
    bool isInternalNode();
    bool goLeft(double featureValue);
};
#endif //baseNode_h
