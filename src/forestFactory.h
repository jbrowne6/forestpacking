#include "interleavedForest.h"
#include "perTreeForest.h"
#include "topBinForest.h"
#include "topBinForestWBatch.h"

class forestFactory
{
    public:
       baseForest* makeForest(int choice){
if(choice == 1){
    return new perTreeForest();
}else if(choice == 2){
    return new interleavedForest();
}else if(choice == 3){
    return new topBinForest(16);
}else if(choice == 4){
    return new topBinForestWBatch(16);
}


return NULL;
       }
};
