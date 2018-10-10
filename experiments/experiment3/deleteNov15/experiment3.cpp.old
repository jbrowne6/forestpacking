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
	int maxDepth;
	if (argc ==2 ){
		maxDepth=atoi(argv[1]);
	}else{
		maxDepth = 10;
	}
	std::ofstream outfile;
	outfile.open("experiments/experiment3/experiment3.csv");

	auto start_time = std::chrono::high_resolution_clock::now();
	auto stop_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> diffMilli;

	float percentRight = 0;
	int numTimes = 3;



	if(doesExist("res/higgs/forest.csv") && true){//begin higgs test namespace
		const std::string forestFileName1 = "res/higgs/forest.csv";
		const std::string testFileName1 = "res/higgs/testObservations.csv";
		const std::string traversalFileName1 = "res/higgs/traversal.csv";
		inferenceSamples travs(traversalFileName1);
		inferenceSamples observations(testFileName1);


		{//start improv8 namespace
			//////improv8/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv8 Test"; 

			for(int numDepth = 0; numDepth <= maxDepth; numDepth+=5){	
				for(int numBins = 4; numBins <= 2048; numBins *= 2){	
					improv8 tester(forestFileName1,1,travs, numBins, numDepth);
					tester.printForest();
					printf("size of a node is %d\n",(int) sizeof(padNode));
					printf("starting run\n");
					int treesPerBin = 2048/numBins;

					for(int numCores = 1; numCores <= 4; numCores *= 2){	
						for(int runNum = 0; runNum < numTimes; ++runNum){
							start_time = std::chrono::high_resolution_clock::now();
							tester.makePredictionsMultiTree(observations,numCores);
							stop_time = std::chrono::high_resolution_clock::now();
							diffMilli = stop_time - start_time;
							outfile << std::fixed << "experiment3, Bin+, Higgs, MultiTree, " << treesPerBin << ", " << numDepth << ", " << diffMilli.count()<< ", " << numCores <<std::endl;
							std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
							std::cout << std::fixed << "experiment3, Bin+, Higgs, MultiTree, " << treesPerBin << ", " << numDepth << ", " << diffMilli.count()<< std::endl;
						}
					}
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


		{//start improv8 namespace
			//////improv8/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv8 Test"; 
			for(int numDepth = 0; numDepth <= maxDepth; numDepth+=5){	
				for(int numBins = 4; numBins <= 2048; numBins *= 2){	
					improv8 tester(forestFileName2,1,travs, numBins, numDepth);
					tester.printForest();
					printf("size of a node is %d\n",(int) sizeof(padNode));
					printf("starting run\n");
					int treesPerBin = 2048/numBins;

					for(int numCores = 1; numCores <= 4; numCores *= 2){	
						for(int runNum = 0; runNum < numTimes; ++runNum){
							start_time = std::chrono::high_resolution_clock::now();
							tester.makePredictionsMultiTree(observations,numCores);
							stop_time = std::chrono::high_resolution_clock::now();
							diffMilli = stop_time - start_time;
							outfile << std::fixed << "experiment3, Bin+, MNIST, MultiTree, " << treesPerBin << ", " << numDepth << ", " << diffMilli.count()<< ", " << numCores << std::endl;
							std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
							std::cout << std::fixed << "experiment3, Bin+, MNIST, MultiTree, " << treesPerBin << ", " << numDepth << ", " << diffMilli.count()<< std::endl;
						}
					}
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


		{//start improv8 namespace
			//////improv8/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv8 Test"; 


			for(int numDepth = 0; numDepth <= maxDepth; numDepth+=5){	
				for(int numBins = 4; numBins <= 2048; numBins *= 2){	
					improv8 tester(forestFileName1,1,travs, numBins, numDepth);
					tester.printForest();
					printf("size of a node is %d\n",(int) sizeof(padNode));
					printf("starting run\n");
					int treesPerBin = 2048/numBins;

					for(int numCores = 1; numCores <= 4; numCores *= 2){	
						for(int runNum = 0; runNum < numTimes; ++runNum){
							start_time = std::chrono::high_resolution_clock::now();
							tester.makePredictionsMultiTree(observations,numCores);
							stop_time = std::chrono::high_resolution_clock::now();
							diffMilli = stop_time - start_time;
							outfile << std::fixed << "experiment3, Bin+, Allstate, MultiTree, " << treesPerBin << ", " << numDepth << ", " << diffMilli.count()<< ", " << numCores << std::endl;
							std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
							std::cout << std::fixed << "experiment3, Bin+, Allstate, MultiTree, " << treesPerBin << ", " << numDepth << ", " << diffMilli.count()<< std::endl;
						}
					}
				}
			}

		}//end improv8 namespace


	}//end Allstate test namespace



	outfile.close();
	return 0;
}
