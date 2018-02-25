#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <ctime>
#include "inferenceSamples.h"
#include "improv1.h"
#include "improv3.h"
#include "improv4.h"
#include "improv5.h"
#include "improv6.h"
#include "improv2.h"
#include "naive.h"

int main(int argc, char* argv[]) {
    if (argc < 3){
        printf("packer requires at least 2 arguments.\n");
        return -1;
    }
    int numOfBatches;
    int depthIntertwined;
    if (argc < 5){
        numOfBatches =0;
        depthIntertwined =0;
    }else{
        numOfBatches =atoi(argv[3]);
        depthIntertwined =atoi(argv[4]);
    }

    int algorithmToRun = atoi(argv[1]);
    int runPrediction = atoi(argv[2]);
    const std::string forestFileName = "res/forest.csv";
    const std::string testFileName = "res/testObservations.csv";
    std::clock_t    start;

    inferenceSamples observations(testFileName);

    if(algorithmToRun == 0){
        printf("running naive src=csv, pred=%d\n",runPrediction);
        naive tester(forestFileName,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        start = std::clock();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        std::cout << "Time to test observations: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

    }else if(algorithmToRun ==1){
        printf("running improv1 src=csv, pred=%d\n",runPrediction);
        improv1 tester(forestFileName,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        start = std::clock();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        std::cout << "Time to test observations: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

    }else if(algorithmToRun ==2){
        printf("running improv2 src=csv, pred=%d\n",runPrediction);
    improv2 tester(forestFileName,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        start = std::clock();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        std::cout << "Time to test observations: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

    }else if(algorithmToRun ==3){
        printf("running improv3 src=csv, pred=%d\n",runPrediction);
    improv3 tester(forestFileName,1, observations);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        start = std::clock();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        std::cout << "Time to test observations: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

    }else if(algorithmToRun ==4){
        printf("running improv4 src=csv, pred=%d\n",runPrediction);
    improv4 tester(forestFileName,1, observations);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        start = std::clock();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        std::cout << "Time to test observations: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

    }else if(algorithmToRun ==5){
        printf("running improv5 src=csv, pred=%d, batches=%d, head=3\n",runPrediction,numOfBatches );
    improv5 tester(forestFileName,1, observations,numOfBatches);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        start = std::clock();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        std::cout << "Time to test observations: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;

    }else if(algorithmToRun ==6){
        printf("running improv5 src=csv, pred=%d, batches=%d, head=%d\n",runPrediction,numOfBatches,depthIntertwined );
      improv6 tester(forestFileName,1, observations,numOfBatches,depthIntertwined);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        start = std::clock();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        std::cout << "Time to test observations: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC) << " s" << std::endl;
    }
        observations.percentRight();
    return 0;
}
