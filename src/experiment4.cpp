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


//This experiment tests the intertwined depth and bin size to find optimal for each dataset.


inline bool doesExist(const std::string& name) {
	std::ifstream f(name.c_str());
	return f.good();
}

int main(int argc, char* argv[]) {
	/*
		 int maxCores;
		 if (argc ==2 ){
		 maxCores=atoi(argv[1]);
		 }else{
		 maxCores = std::thread::hardware_concurrency();
		 }
		 */
	std::ofstream outfile;
	outfile.open("experiments/experiment4/experiment4.csv");



	auto start_time = std::chrono::high_resolution_clock::now();
	auto stop_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> diffMilli;

	float percentRight = 0;
	int numTimes = 11;


	if(doesExist("res/higgs/forest.csv") && true){//begin higgs test namespace
		const std::string forestFileName1 = "res/higgs/forest.csv";
		const std::string testFileName1 = "res/higgs/testObservations.csv";
		const std::string traversalFileName1 = "res/higgs/traversal.csv";
		inferenceSamples travs(traversalFileName1);
		inferenceSamples observations(testFileName1);


		{//start naive namespace
			//////Naive/////////
			std::cout << "running naive Test"; 
			naive tester(forestFileName1,1);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");


			/*
				 tester.makePredictionsMultiTree(observations,2);
				 percentRight = observations.returnPercentRight();

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, BF, Higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//          outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, BF, Higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, BF, Higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					// outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}

		}//end naive test


		{//start improv1 namespace
			//////improv1/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv1 Test"; 
			improv1 tester(forestFileName1,1);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");


			/*
				 tester.makePredictionsMultiTree(observations,2);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, DF, Higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//  outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, DF, Higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

*/
			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, DF, Higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//  outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv1 namespace


		{//start improv2 namespace
			//////improv2/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv2 Test"; 
			improv2 tester(forestFileName1,1);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,3);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, DF-, Higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//  outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, DF-, Higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

*/
			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, DF-, Higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					// outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv2 namespace


		{//start improv4 namespace
			//////improv4/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv4 Test"; 
			improv4 tester(forestFileName1,1,travs);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,3);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, Stat, Higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, Stat, Higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

*/
			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, Stat, Higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					// outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv4 namespace


		{//start improv6 namespace
			//////improv6/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv6 Test"; 
			improv6 tester(forestFileName1,1,travs, 32, 10);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,3);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, Bin, Higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, Bin, Higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, Bin, Higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					// outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv6 namespace




		{//start improv8 namespace
			//////improv8/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv8 Test"; 
			improv8 tester(forestFileName1,1,travs, 32, 10);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,3);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, Bin+, Higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, Bin+, Higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, Bin+, Higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv8 namespace


	}//end higgs test namespace


	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////

	if (doesExist("res/mnist/forest.csv") && true){//begin mnist test namespace
		const std::string forestFileName2 = "res/mnist/forest.csv";
		const std::string testFileName2 = "res/mnist/testObservations.csv";
		const std::string traversalFileName2 = "res/mnist/traversal.csv";

		inferenceSamples travs(traversalFileName2);
		inferenceSamples observations(testFileName2);


		{//start naive namespace
			//////Naive/////////
			std::cout << "running naive Test"; 
			naive tester(forestFileName2,1);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,2);
				 percentRight = observations.returnPercentRight();

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, BF, MNIST, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, BF, MNIST, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

*/
			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, BF, MNIST, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end naive test


		{//start improv1 namespace
			//////improv1/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv1 Test"; 
			improv1 tester(forestFileName2,1);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,2);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, DF, MNIST, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, DF, MNIST, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, DF, MNIST, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv1 namespace


		{//start improv2 namespace
			//////improv2/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv2 Test"; 
			improv2 tester(forestFileName2,1);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,3);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, DF-, MNIST, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, DF-, MNIST, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, DF-, MNIST, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv2 namespace


		{//start improv4 namespace
			//////improv4/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv4 Test"; 
			improv4 tester(forestFileName2,1,travs);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,3);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, Stat, MNIST, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, Stat, MNIST, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, Stat, MNIST, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv4 namespace


		{//start improv6 namespace
			//////improv6/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv6 Test"; 
			improv6 tester(forestFileName2,1,travs, 64, 0);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,3);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, Bin, MNIST, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, Bin, MNIST, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, Bin, MNIST, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv6 namespace




		{//start improv8 namespace
			//////improv8/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv8 Test"; 
			improv8 tester(forestFileName2,1,travs, 64, 0);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,3);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, Bin+, MNIST, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, Bin+, MNIST, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, Bin+, MNIST, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv8 namespace


	}//end mnist test namespace

	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////
	//////////////////Start Allstate//////////////////////////////
	if(doesExist("res/allstate/forest.csv") && true){//begin allstate test namespace
		const std::string forestFileName1 = "res/allstate/forest.csv";
		const std::string testFileName1 = "res/allstate/testObservations.csv";
		const std::string traversalFileName1 = "res/allstate/traversal.csv";
		inferenceSamples travs(traversalFileName1);
		inferenceSamples observations(testFileName1);


		{//start naive namespace
			//////Naive/////////
			std::cout << "running naive Test"; 
			naive tester(forestFileName1,1);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,2);
				 percentRight = observations.returnPercentRight();

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, BF, Allstate, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, BF, Allstate, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, BF, Allstate, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end naive test


		{//start improv1 namespace
			//////improv1/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv1 Test"; 
			improv1 tester(forestFileName1,1);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,2);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, DF, Allstate, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, DF, Allstate, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, DF, Allstate, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv1 namespace


		{//start improv2 namespace
			//////improv2/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv2 Test"; 
			improv2 tester(forestFileName1,1);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,3);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, DF-, Allstate, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, DF-, Allstate, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, DF-, Allstate, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv2 namespace


		{//start improv4 namespace
			//////improv4/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv4 Test"; 
			improv4 tester(forestFileName1,1,travs);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,3);

				 std::cout << "MultiTree\n"; 
				 for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				 std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, Stat, Allstate, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}

			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, Stat, Allstate, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, Stat, Allstate, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv4 namespace


		{//start improv6 namespace
			//////improv6/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv6 Test"; 
			std::cout << "\n\n\n"; 
			std::cout << "running improv6 Test"; 
			improv6 tester(forestFileName1,1,travs, 16, 5);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,3);


				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, Bin, Allstate, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}


			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, Bin, Allstate, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, Bin, Allstate, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv6 namespace




		{//start improv8 namespace
			//////improv8/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv8 Test"; 
			std::cout << "\n\n\n"; 
			std::cout << "running improv8 Test"; 
			improv8 tester(forestFileName1,1,travs, 16, 5);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			/*
				 tester.makePredictionsMultiTree(observations,3);


				 for(int runNum = 0; runNum < numTimes; ++runNum){
				 start_time = std::chrono::high_resolution_clock::now();
				 tester.makePredictionsMultiTree(observations,numCores);
				 stop_time = std::chrono::high_resolution_clock::now();
				 diffMilli = stop_time - start_time;
				 outfile << std::fixed << "experiment1, Bin+, Allstate, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				 if (observations.returnPercentRight() != percentRight){
				 std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}


			std::cout << "MultiObs\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiObs, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiObs(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, Bin+, Allstate, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
			std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
			}
			}
			*/

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, Bin+, Allstate, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					//outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv8 namespace


	}//end Allstate test namespace



	outfile.close();
	return 0;
}
