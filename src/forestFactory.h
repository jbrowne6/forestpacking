#include "interleavedForest.h"
#include "perTreeForest.h"
#include "topBinForest.h"

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
}

return NULL;
       }
};
