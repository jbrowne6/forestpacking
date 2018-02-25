#include "interleavedForest.h"
#include "perTreeForest.h"
#include "topBinForest.h"
#include "topBinForestWBatch.h"
#include "improv1.h"
#include "naive.h"

class forestFactory
{
    public:
       padForest* makeForest(int choice, const std::string& forestFileName){
if(choice == 0){
    return new naive(forestFileName,1);
}else if(choice == 1){
    return new naive(forestFileName,1);
}
return NULL;
       }
};
