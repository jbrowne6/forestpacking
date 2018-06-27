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
//#include "improv3.h"
//#include "improv7.h"
#include "improv4.h"
//#include "improv5.h"
#include "improv6.h"
#include "improv2.h"
#include "improv8.h"
#include "naive.h"

int main(int argc, char* argv[]) {
	int maxCores;
	if (argc ==2 ){
		maxCores=atoi(argv[1]);
	}else{
		maxCores = std::thread::hardware_concurrency();
	}
	std::ofstream outfile;
	outfile.open("experiments/experiment1/experiment1.csv");//, std::ios_base::app);

	auto start_time = std::chrono::high_resolution_clock::now();
	auto stop_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> diffMilli;

	float percentRight = 0;
	int numTimes = 3;
	{//begin higgs test namespace
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
					outfile << std::fixed << "experiment1, BF, higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
					if (observations.returnPercentRight() != percentRight){
						std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
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
					outfile << std::fixed << "experiment1, BF, higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
					if (observations.returnPercentRight() != percentRight){
						std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					}
				}
			}

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, BF, higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end naive test

    if(false){

		{//start improv1 namespace
			//////improv1/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv1 Test"; 
			improv1 tester(forestFileName1,1);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			tester.makePredictionsMultiTree(observations,2);

			std::cout << "MultiTree\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				for(int runNum = 0; runNum < numTimes; ++runNum){
					start_time = std::chrono::high_resolution_clock::now();
					tester.makePredictionsMultiTree(observations,numCores);
					stop_time = std::chrono::high_resolution_clock::now();
					diffMilli = stop_time - start_time;
					outfile << std::fixed << "experiment1, DF, higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
					if (observations.returnPercentRight() != percentRight){
						std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
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
					outfile << std::fixed << "experiment1, DF, higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
					if (observations.returnPercentRight() != percentRight){
						std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					}
				}
			}

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, DF, higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
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

			tester.makePredictionsMultiTree(observations,3);

			std::cout << "MultiTree\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				for(int runNum = 0; runNum < numTimes; ++runNum){
					start_time = std::chrono::high_resolution_clock::now();
					tester.makePredictionsMultiTree(observations,numCores);
					stop_time = std::chrono::high_resolution_clock::now();
					diffMilli = stop_time - start_time;
					outfile << std::fixed << "experiment1, DF-, higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
					if (observations.returnPercentRight() != percentRight){
						std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
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
					outfile << std::fixed << "experiment1, DF-, higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
					if (observations.returnPercentRight() != percentRight){
						std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					}
				}
			}

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, DF-, higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
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

			tester.makePredictionsMultiTree(observations,3);

			std::cout << "MultiTree\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				for(int runNum = 0; runNum < numTimes; ++runNum){
					start_time = std::chrono::high_resolution_clock::now();
					tester.makePredictionsMultiTree(observations,numCores);
					stop_time = std::chrono::high_resolution_clock::now();
					diffMilli = stop_time - start_time;
					outfile << std::fixed << "experiment1, Stat, higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
					if (observations.returnPercentRight() != percentRight){
						std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
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
					outfile << std::fixed << "experiment1, Stat, higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
					if (observations.returnPercentRight() != percentRight){
						std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					}
				}
			}

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, Stat, higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv4 namespace

}
{//start improv6 namespace
			//////improv6/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv6 Test"; 
			improv6 tester(forestFileName1,1,travs, 16, 3);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			tester.makePredictionsMultiTree(observations,3);

			std::cout << "MultiTree\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				for(int runNum = 0; runNum < numTimes; ++runNum){
					start_time = std::chrono::high_resolution_clock::now();
					tester.makePredictionsMultiTree(observations,numCores);
					stop_time = std::chrono::high_resolution_clock::now();
					diffMilli = stop_time - start_time;
					outfile << std::fixed << "experiment1, Bin, higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
					if (observations.returnPercentRight() != percentRight){
						std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
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
					outfile << std::fixed << "experiment1, Bin, higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
					if (observations.returnPercentRight() != percentRight){
						std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					}
				}
			}

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, Bin, higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv6 namespace




{//start improv8 namespace
			//////improv8/////////
			std::cout << "\n\n\n"; 
			std::cout << "running improv8 Test"; 
			improv8 tester(forestFileName1,1,travs, 16, 3);
			tester.printForest();
			printf("size of a node is %d\n",(int) sizeof(padNode));
			printf("starting run\n");

			tester.makePredictionsMultiTree(observations,3);

			std::cout << "MultiTree\n"; 
			for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
				std::cout << "MultiTree, numCores=" << numCores << "\n"; 
				for(int runNum = 0; runNum < numTimes; ++runNum){
					start_time = std::chrono::high_resolution_clock::now();
					tester.makePredictionsMultiTree(observations,numCores);
					stop_time = std::chrono::high_resolution_clock::now();
					diffMilli = stop_time - start_time;
					outfile << std::fixed << "experiment1, Bin+, higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
					if (observations.returnPercentRight() != percentRight){
						std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
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
					outfile << std::fixed << "experiment1, Bin+, higgs, MultiObs, " << numCores << ", " << diffMilli.count()<< std::endl;
					if (observations.returnPercentRight() != percentRight){
						std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
					}
				}
			}

			std::cout << "SingleCore\n"; 
			for(int runNum = 0; runNum < numTimes; ++runNum){
				start_time = std::chrono::high_resolution_clock::now();
				tester.makePredictions(observations);
				stop_time = std::chrono::high_resolution_clock::now();
				diffMilli = stop_time - start_time;
				outfile << std::fixed << "experiment1, Bin+, higgs, SingleCore, 1, " << diffMilli.count()<< std::endl;
				if (observations.returnPercentRight() != percentRight){
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
						outfile << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
				}
			}
		}//end improv8 namespace


	}//end higgs test namespace

	const std::string forestFileName2 = "res/mnist/forest.csv";
	const std::string testFileName2 = "res/mnist/testObservations.csv";
	const std::string traversalFileName2 = "res/mnist/traversal.csv";


	outfile.close();
	return 0;
}
