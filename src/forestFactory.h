#include "interleavedForest.h"
#include "perTreeForest.h"

class forestFactory
{
    public:
       baseForest* makeForest(int choice){
if(choice == 1)
    return new perTreeForest();
if(choice == 2)
    return new interleavedForest();
return NULL;
       }
};
