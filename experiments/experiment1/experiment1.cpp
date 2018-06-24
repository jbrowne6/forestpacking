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
//#include "../improv1.h"
//#include "improv3.h"
//#include "improv7.h"
//#include "improv4.h"
//#include "improv5.h"
//#include "improv6.h"
//#include "improv2.h"
//#include "improv8.h"
#include "naive.h"

int main(int argc, char* argv[]) {
	int maxCores;
	if (argc ==2 ){
		maxCores=atoi(argv[1]);
	}else{
		maxCores = std::thread::hardware_concurrency();
	}
	std::ofstream outfile;
	outfile.open("experiment1.csv", std::ios_base::app);

	auto start_time = std::chrono::high_resolution_clock::now();
	auto stop_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> diffMilli;

	float percentRight;
	int numTimes = 2;
	{//begin namespace
		const std::string forestFileName1 = "res/higgs/forest.csv";
		const std::string testFileName1 = "res/higgs/testObservations.csv";
		const std::string traversalFileName1 = "res/higgs/traversal.csv";
		inferenceSamples travs(traversalFileName1);
		inferenceSamples observations(testFileName1);

		std::cout << "running naive Test"; 
		naive tester(forestFileName1,1);
		tester.printForest();
		printf("size of a node is %d\n",(int) sizeof(padNode));
		printf("starting run\n");

		tester.makePredictionsMultiTree(observations,3);
		percentRight = observations.returnPercentRight();


		std::cout << "MultiTree\n"; 
		for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
			std::cout << "MultiTree, numCores=" << numCores << "\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictionsMultiTree(observations,numCores);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, naive, higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
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
				outfile << std::fixed << "experiment1, naive, higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}

		std::cout << "SingleCore\n"; 
		for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictions(observations);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, naive, higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
				std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
		}
	}//end namespace

	const std::string forestFileName2 = "res/mnist/forest.csv";
	const std::string testFileName2 = "res/mnist/testObservations.csv";
	const std::string traversalFileName2 = "res/mnist/traversal.csv";


	return 0;
}
