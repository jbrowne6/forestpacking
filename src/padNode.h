#ifndef padNode_h
#define padNode_h
#include <cstdint>

class padNode
{
    public:
    uint32_t feature;
    uint32_t left;
    uint32_t right;
   // uint32_t pad1;
    double cutValue;
  //  double pad2;

//    public:
    void setNode(double cVal, uint32_t feat, uint32_t l, uint32_t r);
    void virtual printNode();
    double returnCutValue();
    int returnFeature();
    int returnLeftNode(); //should have been Value instead of Node
    int returnRightNode();//should have been Value instead of Node
    int returnClass();//should have been Value instead of Node
    void setLeftValue(uint32_t LVal);
    void setRightValue(uint32_t RVal); 
    bool isInternalNode();
    bool goLeft(double featureValue);
};
#endif //padNode_h
