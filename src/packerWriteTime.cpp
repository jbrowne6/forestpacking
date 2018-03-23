#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <ctime>
#include <chrono>
#include "inferenceSamples.h"
#include "improv1.h"
#include "improv3.h"
#include "improv7.h"
#include "improv8.h"
#include "improv4.h"
#include "improv5.h"
#include "improv6.h"
#include "improv2.h"
#include "improv15.h"
#include "improv9.h"
#include "naive.h"
#include <omp.h>

int main(int argc, char* argv[]) {
    if (argc < 3){
        printf("packer requires at least 2 arguments.\n");
        return -1;
    }
    int numOfBatches;
    int depthIntertwined;

    omp_set_num_threads(4);
    if (argc < 4){
        numOfBatches =0;
        depthIntertwined =0;
    }else if(argc == 4){
        numOfBatches =atoi(argv[3]);
        depthIntertwined = 0;
    }else if(argc == 5){
        numOfBatches =atoi(argv[3]);
        depthIntertwined =atoi(argv[4]);
    }else if(argc == 6){
        numOfBatches =atoi(argv[3]);
        depthIntertwined =atoi(argv[4]);
        omp_set_num_threads(atoi (argv[5]) );
    }


    int algorithmToRun = atoi(argv[1]);
    int runPrediction = atoi(argv[2]);
    const std::string forestFileName = "res/forest.csv";
    const std::string testFileName = "res/testObservations.csv";
    const std::string traversalFileName = "res/traversal.csv";
    std::chrono::duration<double> diff;
    auto startTime = std::chrono::steady_clock::now();
    auto stopTime = std::chrono::steady_clock::now();

    inferenceSamples travs(traversalFileName);
    inferenceSamples observations(testFileName);

    if(algorithmToRun == 0){
        printf("running naive src=csv, pred=%d\n",runPrediction);
        naive tester(forestFileName,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        startTime = std::chrono::steady_clock::now();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        stopTime = std::chrono::steady_clock::now();
    }else if(algorithmToRun ==1){
        printf("running improv1 src=csv, pred=%d\n",runPrediction);
        improv1 tester(forestFileName,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        startTime = std::chrono::steady_clock::now();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        stopTime = std::chrono::steady_clock::now();
    }else if(algorithmToRun ==2){
        printf("running improv2 src=csv, pred=%d\n",runPrediction);
        improv2 tester(forestFileName,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        startTime = std::chrono::steady_clock::now();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        stopTime = std::chrono::steady_clock::now();
    }else if(algorithmToRun ==3){
        printf("running improv3 src=csv, pred=%d\n",runPrediction);
        improv3 tester(forestFileName,1, travs);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        startTime = std::chrono::steady_clock::now();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        stopTime = std::chrono::steady_clock::now();
    }else if(algorithmToRun ==4){
        printf("running improv4 src=csv, pred=%d\n",runPrediction);
        improv4 tester(forestFileName,1, travs);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        startTime = std::chrono::steady_clock::now();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        stopTime = std::chrono::steady_clock::now();

    }else if(algorithmToRun ==5){
        printf("running improv5 src=csv, pred=%d, batches=%d, head=3\n",runPrediction,numOfBatches );
        improv5 tester(forestFileName,1, observations,numOfBatches);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        startTime = std::chrono::steady_clock::now();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        stopTime = std::chrono::steady_clock::now();
    }else if(algorithmToRun ==6){
        printf("running improv6 src=csv, pred=%d, batches=%d, head=%d\n",runPrediction,numOfBatches,depthIntertwined );
        improv6 tester(forestFileName,1, observations,numOfBatches,depthIntertwined);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        startTime = std::chrono::steady_clock::now();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        stopTime = std::chrono::steady_clock::now();
    }else if(algorithmToRun ==7){
        printf("running improv7 src=csv, pred=%d, batches=%d, head=%d\n",runPrediction,numOfBatches,depthIntertwined );
        improv7 tester(forestFileName,1, observations,numOfBatches,depthIntertwined);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        startTime = std::chrono::steady_clock::now();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        stopTime = std::chrono::steady_clock::now();

    }else if(algorithmToRun ==8){
        printf("running improv8 src=csv, pred=%d, batches=%d, head=%d\n",runPrediction,numOfBatches,depthIntertwined );
        improv8 tester(forestFileName,1, observations,numOfBatches,depthIntertwined);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        startTime = std::chrono::steady_clock::now();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        stopTime = std::chrono::steady_clock::now();
    }else if(algorithmToRun ==9){
        printf("running improv9 src=csv, pred=%d, batches=%d, head=%d\n",runPrediction,numOfBatches,depthIntertwined );
        improv9 tester(forestFileName,1, observations,numOfBatches,depthIntertwined);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");

        if(runPrediction){
            int currentPred;
            double totalTime = 0;

            for(int q=0; q<observations.numObservations;q++){
                startTime = std::chrono::steady_clock::now();
                currentPred = tester.makePrediction(observations.samplesMatrix[q]);
                stopTime = std::chrono::steady_clock::now();
                diff = stopTime-startTime;
                totalTime+=diff.count();
                observations.predictedClasses[q] = currentPred;
            }
            std::cout<<"Time to test observations: "<<totalTime<<" s"<<std::endl;
        }
    }else if(algorithmToRun ==10){
        printf("running improv9 multirun src=csv, pred=%d, batches=%d, head=%d\n",runPrediction,numOfBatches,depthIntertwined );
        improv9 tester(forestFileName,1, observations,numOfBatches,depthIntertwined);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");

        if(runPrediction){
            int numTimes = 10;
            double totalTime = 0;
            std::ofstream outfileX;
            outfileX.open("runTimesX.csv", std::ios_base::app);
            for(int numC = 1; numC < 64; numC*=2){

                omp_set_num_threads(numC);
                outfileX << numC << " , ";
                for(int z = 0; z < numTimes; z++){

                    totalTime = 0;
                    int currentPred;
                    for(int q=0; q<observations.numObservations;q++){
                        startTime = std::chrono::steady_clock::now();
                        currentPred = tester.makePrediction(observations.samplesMatrix[q]);
                        stopTime = std::chrono::steady_clock::now();
                        diff = stopTime-startTime;
                        totalTime+=diff.count();
                        observations.predictedClasses[q] = currentPred;
                    }
                    outfileX << totalTime << " , ";
                }
                outfileX << 0 << std::endl;
            }
            std::cout<<"Time to test observations: "<<totalTime<<" s"<<std::endl;
        }
    }else if(algorithmToRun ==11){
        printf("running improv9 multirun src=csv, pred=%d, batches=%d, head=%d\n",runPrediction,numOfBatches,depthIntertwined );
        improv9 tester(forestFileName,1, observations,numOfBatches,depthIntertwined);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");

        if(runPrediction){
            double totalTime = 0;
            for(int numC = 1; numC < 64; numC*=2){

                omp_set_num_threads(numC);

                totalTime = 0;
                int currentPred;

                for(int q = 0; q < 2; q++){
                    startTime = std::chrono::steady_clock::now();
                    currentPred = tester.makeTest(observations.samplesMatrix[q]);
                    stopTime = std::chrono::steady_clock::now();
                    diff = stopTime-startTime;
                    totalTime+=diff.count();
                    observations.predictedClasses[q] = currentPred;
                }

                std::cout << std::endl << std::endl;
            }
        }
    }else if(algorithmToRun ==15){
        printf("running improv15 src=csv, pred=%d, batches=%d, head=%d\n",runPrediction,numOfBatches,depthIntertwined );
        improv15 tester(forestFileName,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");
        startTime = std::chrono::steady_clock::now();
        if(runPrediction){
            tester.makePredictions(observations);
        }
        stopTime = std::chrono::steady_clock::now();
    }else if(algorithmToRun ==40){
        printf("running naive src=csv, pred=%d\n",runPrediction);
        naive tester(forestFileName,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting multiple runs\n");

        int numTimes = 10;
        std::ofstream outfileX;
        outfileX.open("runTimes40.csv", std::ios_base::app);

        outfileX << 0 << " , ";
        for(int z = 0; z < numTimes; z++){
            startTime = std::chrono::steady_clock::now();
            tester.makePredictions(observations);
            stopTime = std::chrono::steady_clock::now();
            diff = stopTime-startTime;
            outfileX << diff.count() << " , ";
        }
        outfileX << 0 << std::endl;
    }else if(algorithmToRun ==41){
        printf("running improv1 src=csv, pred=%d\n",runPrediction);
        improv1 tester(forestFileName,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting multiple runs\n");

        int numTimes = 10;
        std::ofstream outfileX;
        outfileX.open("runTimes41.csv", std::ios_base::app);

        outfileX << 1 << " , ";
        for(int z = 0; z < numTimes; z++){
            startTime = std::chrono::steady_clock::now();
            tester.makePredictions(observations);
            stopTime = std::chrono::steady_clock::now();
            diff = stopTime-startTime;
            outfileX << diff.count() << " , ";
        }
        outfileX << 0 << std::endl;
    }else if(algorithmToRun ==42){
        printf("running improv1 src=csv, pred=%d\n",runPrediction);
        improv2 tester(forestFileName,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting multiple runs\n");

        int numTimes = 10;
        std::ofstream outfileX;
        outfileX.open("runTimes42.csv", std::ios_base::app);

        outfileX << 1 << " , ";
        for(int z = 0; z < numTimes; z++){
            startTime = std::chrono::steady_clock::now();
            tester.makePredictions(observations);
            stopTime = std::chrono::steady_clock::now();
            diff = stopTime-startTime;
            outfileX << diff.count() << " , ";
        }
        outfileX << 0 << std::endl;
    }else if(algorithmToRun ==46){
        printf("running improv6 multi src=csv, pred=%d\n",runPrediction);

        std::ofstream outfileX;
        outfileX.open("runTimes46.csv", std::ios_base::app);
        int numBatches = 2048;
        for(int j = 0; j < 6; j++){

            for(int k = 0; k < 8; k++){
                improv6 tester(forestFileName,1, observations,numBatches,k);

                tester.printForest();
                printf("size of a node is %d\n",(int) sizeof(padNode));
                printf("starting multiple runs\n");

                int numTimes = 10;

                for(int z = 0; z < numTimes; z++){
                outfileX << 2048/numBatches << " , " << k << " , " << 6 << " , ";
                    startTime = std::chrono::steady_clock::now();
                    tester.makePredictions(observations);
                    stopTime = std::chrono::steady_clock::now();
                    diff = stopTime-startTime;
                    outfileX << diff.count() << std::endl;
                }
            }
            numBatches = numBatches / 2;
        }

    }




    diff = stopTime - startTime;
    std::cout<<"Time to test observations: "<<diff.count()<<" s"<<std::endl;

    std::ofstream outfile;
    outfile.open("runTimes.csv", std::ios_base::app);
    outfile << algorithmToRun <<  " , " << diff.count()<< std::endl;


    observations.percentRight();
    return 0;
}
