#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <ctime>
#include <chrono>
#include <omp.h>
#include <thread>
#include "inferenceSamples.h"
#include "improv1.h"
#include "improv4.h"
#include "improv6.h"
#include "improv2.h"
#include "improv8.h"
#include "naive.h"

inline bool doesExist(const std::string& name) {
  std::ifstream f(name.c_str());
  return f.good();
}

int main(int argc, char* argv[]) {
  
  std::ofstream outfile;
  outfile.open("experiments/experiment5/experiment5d.csv");

  auto start_time = std::chrono::high_resolution_clock::now();
  auto stop_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::micro> diffMilli;

  float percentRight = 0;
  int numTimes = 10;


  const std::string testFileName1 = "res/higgs/testObservations.csv";
  const std::string traversalFileName1 = "res/higgs/traversal.csv";
  inferenceSamples travs(traversalFileName1);
  inferenceSamples observations(testFileName1);


  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  {
    const std::string forestFileName1 = "experiments/experiment5/forest-6-128-.csv";

    
{//start naive namespace
      //////Naive/////////
      std::cout << "running naive Test"; 
      naive tester(forestFileName1,1);
      tester.printForest();
      printf("size of a node is %d\n",(int) sizeof(padNode));
      printf("starting run\n");


      std::cout << "MultiTree\n"; 
      for(int runNum = 0; runNum < numTimes; ++runNum){
        start_time = std::chrono::high_resolution_clock::now();
        tester.makePredictionsMultiTree(observations,32);
        stop_time = std::chrono::high_resolution_clock::now();
        diffMilli = stop_time - start_time;
        outfile << std::fixed << "BF(MC), 6, 128, " << diffMilli.count()<< std::endl;
        std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
      }

    }//end naive test


    {//start improv8 namespace
      //////improv8/////////
      std::cout << "\n\n\n"; 
      std::cout << "running improv8 Test"; 

      improv8 tester(forestFileName1,1,travs, 4, 3);
      tester.printForest();
      printf("size of a node is %d\n",(int) sizeof(padNode));
      printf("starting run\n");

      for(int runNum = 0; runNum < numTimes; ++runNum){
        start_time = std::chrono::high_resolution_clock::now();
        tester.makePredictionsMultiTree(observations,4);
        stop_time = std::chrono::high_resolution_clock::now();
        diffMilli = stop_time - start_time;
        outfile << std::fixed << "Bin+(MC), 6, 128, " << diffMilli.count()<< std::endl;
        std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
      }

    }
  }

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    {
      const std::string forestFileName1 = "experiments/experiment5/forest-6-256-.csv";

{//start naive namespace
        //////Naive/////////
        std::cout << "running naive Test"; 
        naive tester(forestFileName1,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");


        std::cout << "MultiTree\n"; 
        for(int runNum = 0; runNum < numTimes; ++runNum){
          start_time = std::chrono::high_resolution_clock::now();
          tester.makePredictionsMultiTree(observations,32);
          stop_time = std::chrono::high_resolution_clock::now();
          diffMilli = stop_time - start_time;
          outfile << std::fixed << "BF(MC), 6, 256, " << diffMilli.count()<< std::endl;
          std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
        }


      }//end naive test


      {//start improv8 namespace
        //////improv8/////////
        std::cout << "\n\n\n"; 
        std::cout << "running improv8 Test"; 

        improv8 tester(forestFileName1,1,travs, 8, 3);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");

        for(int runNum = 0; runNum < numTimes; ++runNum){
          start_time = std::chrono::high_resolution_clock::now();
          tester.makePredictionsMultiTree(observations,8);
          stop_time = std::chrono::high_resolution_clock::now();
          diffMilli = stop_time - start_time;
          outfile << std::fixed << "Bin+(MC), 6, 256, " << diffMilli.count()<< std::endl;
          std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
        }
      }

    }



    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    {
      const std::string forestFileName1 = "experiments/experiment5/forest-6-512-.csv";

{//start naive namespace
        //////Naive/////////
        std::cout << "running naive Test"; 
        naive tester(forestFileName1,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");


        std::cout << "MultiTree\n"; 
        for(int runNum = 0; runNum < numTimes; ++runNum){
          start_time = std::chrono::high_resolution_clock::now();
          tester.makePredictionsMultiTree(observations,32);
          stop_time = std::chrono::high_resolution_clock::now();
          diffMilli = stop_time - start_time;
          outfile << std::fixed << "BF(MC), 6, 512, " << diffMilli.count()<< std::endl;
          std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
        }
      }//end naive test


      {//start improv8 namespace
        //////improv8/////////
        std::cout << "\n\n\n"; 
        std::cout << "running improv8 Test"; 

          improv8 tester(forestFileName1,1,travs, 16, 3);
          tester.printForest();
          printf("size of a node is %d\n",(int) sizeof(padNode));
          printf("starting run\n");

          for(int runNum = 0; runNum < numTimes; ++runNum){
            start_time = std::chrono::high_resolution_clock::now();
            tester.makePredictionsMultiTree(observations,16);
            stop_time = std::chrono::high_resolution_clock::now();
            diffMilli = stop_time - start_time;
            outfile << std::fixed << "Bin+(MC), 6, 512, " << diffMilli.count()<< std::endl;
            std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
          }
      }
    }
  

  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  {
    const std::string forestFileName1 = "experiments/experiment5/forest-10-128-.csv";

{//start naive namespace
      //////Naive/////////
      std::cout << "running naive Test"; 
      naive tester(forestFileName1,1);
      tester.printForest();
      printf("size of a node is %d\n",(int) sizeof(padNode));
      printf("starting run\n");


      std::cout << "MultiTree\n"; 
      for(int runNum = 0; runNum < numTimes; ++runNum){
        start_time = std::chrono::high_resolution_clock::now();
        tester.makePredictionsMultiTree(observations,32);
        stop_time = std::chrono::high_resolution_clock::now();
        diffMilli = stop_time - start_time;
        outfile << std::fixed << "BF(MC), 10, 128, " << diffMilli.count()<< std::endl;
        std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
      }

    }//end naive test


    {//start improv8 namespace
      //////improv8/////////
      std::cout << "\n\n\n"; 
      std::cout << "running improv8 Test"; 

      improv8 tester(forestFileName1,1,travs, 4, 3);
      tester.printForest();
      printf("size of a node is %d\n",(int) sizeof(padNode));
      printf("starting run\n");

      for(int runNum = 0; runNum < numTimes; ++runNum){
        start_time = std::chrono::high_resolution_clock::now();
        tester.makePredictionsMultiTree(observations,4);
        stop_time = std::chrono::high_resolution_clock::now();
        diffMilli = stop_time - start_time;
        outfile << std::fixed << "Bin+(MC), 10, 128, " << diffMilli.count()<< std::endl;
        std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
      }
    }
  }

    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    {
      const std::string forestFileName1 = "experiments/experiment5/forest-10-256-.csv";

    {//start naive namespace
        //////Naive/////////
        std::cout << "running naive Test"; 
        naive tester(forestFileName1,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");


        std::cout << "MultiTree\n"; 
        for(int runNum = 0; runNum < numTimes; ++runNum){
          start_time = std::chrono::high_resolution_clock::now();
          tester.makePredictionsMultiTree(observations,32);
          stop_time = std::chrono::high_resolution_clock::now();
          diffMilli = stop_time - start_time;
          outfile << std::fixed << "BF(MC), 10, 256, " << diffMilli.count()<< std::endl;
          std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
        }
      }//end naive test


      {//start improv8 namespace
        //////improv8/////////
        std::cout << "\n\n\n"; 
        std::cout << "running improv8 Test"; 

        improv8 tester(forestFileName1,1,travs, 8, 3);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");

        for(int runNum = 0; runNum < numTimes; ++runNum){
          start_time = std::chrono::high_resolution_clock::now();
          tester.makePredictionsMultiTree(observations,8);
          stop_time = std::chrono::high_resolution_clock::now();
          diffMilli = stop_time - start_time;
          outfile << std::fixed << "Bin+(MC), 10, 256, " << diffMilli.count()<< std::endl;
          std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
        }
      }//end improv8 namespace

    }



    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    {
      const std::string forestFileName1 = "experiments/experiment5/forest-10-512-.csv";

{//start naive namespace
        //////Naive/////////
        std::cout << "running naive Test"; 
        naive tester(forestFileName1,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");


        std::cout << "MultiTree\n"; 
        for(int runNum = 0; runNum < numTimes; ++runNum){
          start_time = std::chrono::high_resolution_clock::now();
          tester.makePredictionsMultiTree(observations,32);
          stop_time = std::chrono::high_resolution_clock::now();
          diffMilli = stop_time - start_time;
          outfile << std::fixed << "BF(MC), 10, 512, " << diffMilli.count()<< std::endl;
          std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
        }
      }//end naive test


      {//start improv8 namespace
        //////improv8/////////
        std::cout << "\n\n\n"; 
        std::cout << "running improv8 Test"; 

          improv8 tester(forestFileName1,1,travs, 16, 3);
          tester.printForest();
          printf("size of a node is %d\n",(int) sizeof(padNode));
          printf("starting run\n");

          for(int runNum = 0; runNum < numTimes; ++runNum){
            start_time = std::chrono::high_resolution_clock::now();
            tester.makePredictionsMultiTree(observations,16);
            stop_time = std::chrono::high_resolution_clock::now();
            diffMilli = stop_time - start_time;
            outfile << std::fixed << "Bin+(MC), 10, 512, " << diffMilli.count()<< std::endl;
            std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
          }
      }//end improv8 namespace

    }
  

  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  ////////////////////////////////////////////////////
  {
    const std::string forestFileName1 = "experiments/experiment5/forest-14-128-.csv";
{//start naive namespace
      //////Naive/////////
      std::cout << "running naive Test"; 
      naive tester(forestFileName1,1);
      tester.printForest();
      printf("size of a node is %d\n",(int) sizeof(padNode));
      printf("starting run\n");


      std::cout << "MultiTree\n"; 
      for(int runNum = 0; runNum < numTimes; ++runNum){
        start_time = std::chrono::high_resolution_clock::now();
        tester.makePredictionsMultiTree(observations,32);
        stop_time = std::chrono::high_resolution_clock::now();
        diffMilli = stop_time - start_time;
        outfile << std::fixed << "BF(MC), 14, 128, " << diffMilli.count()<< std::endl;
        std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
      }

    }//end naive test


    {//start improv8 namespace
      //////improv8/////////
      std::cout << "\n\n\n"; 
      std::cout << "running improv8 Test"; 

      improv8 tester(forestFileName1,1,travs, 4, 3);
      tester.printForest();
      printf("size of a node is %d\n",(int) sizeof(padNode));
      printf("starting run\n");

      for(int runNum = 0; runNum < numTimes; ++runNum){
        start_time = std::chrono::high_resolution_clock::now();
        tester.makePredictionsMultiTree(observations,4);
        stop_time = std::chrono::high_resolution_clock::now();
        diffMilli = stop_time - start_time;
        outfile << std::fixed << "Bin+(MC), 14, 128, " << diffMilli.count()<< std::endl;
        std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
      }

    }
  }


    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    {
      const std::string forestFileName1 = "experiments/experiment5/forest-14-256-.csv";

{//start naive namespace
        //////Naive/////////
        std::cout << "running naive Test"; 
        naive tester(forestFileName1,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");


        std::cout << "MultiTree\n"; 
        for(int runNum = 0; runNum < numTimes; ++runNum){
          start_time = std::chrono::high_resolution_clock::now();
          tester.makePredictionsMultiTree(observations,32);
          stop_time = std::chrono::high_resolution_clock::now();
          diffMilli = stop_time - start_time;
          outfile << std::fixed << "BF(MC), 14, 256, " << diffMilli.count()<< std::endl;
          std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
        }
      }//end naive test


      {//start improv8 namespace
        //////improv8/////////
        std::cout << "\n\n\n"; 
        std::cout << "running improv8 Test"; 

        improv8 tester(forestFileName1,1,travs, 8, 3);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");

        for(int runNum = 0; runNum < numTimes; ++runNum){
          start_time = std::chrono::high_resolution_clock::now();
          tester.makePredictionsMultiTree(observations,8);
          stop_time = std::chrono::high_resolution_clock::now();
          diffMilli = stop_time - start_time;
          outfile << std::fixed << "Bin+(MC), 14, 256, " << diffMilli.count()<< std::endl;
          std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
        }
      }//end improv8 namespace
    }



    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    {
      const std::string forestFileName1 = "experiments/experiment5/forest-14-512-.csv";

{//start naive namespace
        //////Naive/////////
        std::cout << "running naive Test"; 
        naive tester(forestFileName1,1);
        tester.printForest();
        printf("size of a node is %d\n",(int) sizeof(padNode));
        printf("starting run\n");


        std::cout << "MultiTree\n"; 
        for(int runNum = 0; runNum < numTimes; ++runNum){
          start_time = std::chrono::high_resolution_clock::now();
          tester.makePredictionsMultiTree(observations,32);
          stop_time = std::chrono::high_resolution_clock::now();
          diffMilli = stop_time - start_time;
          outfile << std::fixed << "BF(MC), 14, 512, " << diffMilli.count()<< std::endl;
          std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
        }
      }//end naive test


      {//start improv8 namespace
        //////improv8/////////
        std::cout << "\n\n\n"; 
        std::cout << "running improv8 Test"; 

          improv8 tester(forestFileName1,1,travs, 16, 3);
          tester.printForest();
          printf("size of a node is %d\n",(int) sizeof(padNode));
          printf("starting run\n");

          for(int runNum = 0; runNum < numTimes; ++runNum){
            start_time = std::chrono::high_resolution_clock::now();
            tester.makePredictionsMultiTree(observations,16);
            stop_time = std::chrono::high_resolution_clock::now();
            diffMilli = stop_time - start_time;
            outfile << std::fixed << "Bin+(MC), 14, 512, " << diffMilli.count()<< std::endl;
            std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
          }
      }//end improv8 namespace

    }
     
  outfile.close();
  return 0;
}
