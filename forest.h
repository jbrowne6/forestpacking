class Node{
    double cutValue;
    int feature;
    int left;
    int right;

    public:
    void setNode(double cVal, int feat, int l, int r);
    void printNode();
    double returnCutValue();
    int returnFeature();
    int returnLeftNode();
    int returnRightNode();
    bool isInternalNode();
    bool goLeft(double featureValue);
};

class Forest
{
    Node ** forestRoots = NULL;
    int numTreesInForest;
    int totalNumberOfNodes;
    int numLeafNodesInForest;
    int numOfClasses;
    bool debugModeOn;
    bool showAllResults;

    public:
Forest() : debugModeOn(false), showAllResults(false){}
    void printForest();
    void createForestFromCSV(const std::string& forestCSVFileName);
void makePredictions(const std::string& testFile);
void turnDebugModeOn();
void turnShowAllResultsOn();

};



