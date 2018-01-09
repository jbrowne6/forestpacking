class Node
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

class Forest
{
    Node ** forestRoots = NULL;
    Node * forest = NULL;
    int numTreesInForest;
    int totalNumberOfNodes;
    int numLeafNodesInForest;
    int numOfClasses;
    int forestType;
    bool debugModeOn;
    bool showAllResults;
    int returnClassPrediction(int *classTotals);

    public:
    Forest() : debugModeOn(false), showAllResults(false){}
    void printForest();
    void createForestFromCSV(const std::string& forestCSVFileName);
    void createInterleavedForestFromCSV(const std::string& forestCSVFileName);
    void makePredictions(const std::string& testFile);
    void turnDebugModeOn();
    void turnShowAllResultsOn();
};

