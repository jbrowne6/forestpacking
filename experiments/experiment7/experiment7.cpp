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
	int maxCores;
	if (argc ==2 ){
		maxCores=atoi(argv[1]);
	}else{
		maxCores = std::thread::hardware_concurrency();
	}
	std::ofstream outfile;
	outfile.open("experiments/experiment7/experiment7.csv");

	auto start_time = std::chrono::high_resolution_clock::now();
	auto stop_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> diffMilli;

	float percentRight = 0;
	int numTimes = 2;



	if(doesExist("res/higgs/forest.csv") && true){//begin higgs test namespace
		const std::string forestFileName1 = "res/higgs/forest.csv";
		const std::string testFileName1 = "res/higgs/testObservations.csv";
		const std::string traversalFileName1 = "res/higgs/traversal.csv";
		inferenceSamples travs(traversalFileName1);
		inferenceSamples observations(testFileName1);


		
{//start improv6 namespace
	//////improv6/////////
	std::cout << "\n\n\n"; 
	std::cout << "running improv6 Test"; 
	std::cout << "MultiTree\n"; 
	for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
//		int treesPerBin = 2048/numCores;
		improv6 tester(forestFileName1,1,travs, 128, 3);
		tester.printForest();
		printf("size of a node is %d\n",(int) sizeof(padNode));
		printf("starting run\n");

		for(int runNum = 0; runNum < numTimes; ++runNum){
			start_time = std::chrono::high_resolution_clock::now();
			tester.makePredictionsMultiTree(observations,numCores);
			stop_time = std::chrono::high_resolution_clock::now();
			diffMilli = stop_time - start_time;
			outfile << std::fixed << "experiment1, Bin, Higgs, MultiTree, " << numCores << ", " << diffMilli.count()<< std::endl;
			if (observations.returnPercentRight() != percentRight){
				std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
			}
		}
	}

	}//end improv6 namespace




{//start improv8 namespace
	//////improv8/////////
	std::cout << "\n\n\n"; 
	std::cout << "running improv8 Test"; 

	for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
	//	int treesPerBin = 2048/numCores;
		improv8 tester(forestFileName1,1,travs, 128, 3);
		tester.printForest();
		printf("size of a node is %d\n",(int) sizeof(padNode));
		printf("starting run\n");

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


	
{//start improv6 namespace
	//////improv6/////////
	std::cout << "\n\n\n"; 
	std::cout << "running improv6 Test"; 

	for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
	//	int treesPerBin = 2048/numCores;
		improv6 tester(forestFileName2,1,travs, 128, 3);
		tester.printForest();
		printf("size of a node is %d\n",(int) sizeof(padNode));
		printf("starting run\n");

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

}//end improv6 namespace




{//start improv8 namespace
	//////improv8/////////
	std::cout << "\n\n\n"; 
	std::cout << "running improv8 Test"; 

	for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
	//	int treesPerBin = 2048/numCores;
		improv8 tester(forestFileName2,1,travs,128, 3);
		tester.printForest();
		printf("size of a node is %d\n",(int) sizeof(padNode));
		printf("starting run\n");


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



{//start improv6 namespace
	//////improv6/////////
	std::cout << "\n\n\n"; 
	std::cout << "running improv6 Test"; 
	std::cout << "MultiTree\n"; 
	for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
		std::cout << "MultiTree, numCores=" << numCores << "\n"; 
	//	int treesPerBin = 2048/numCores;
		improv6 tester(forestFileName1,1,travs,128, 3);
		tester.printForest();
		printf("size of a node is %d\n",(int) sizeof(padNode));
		printf("starting run\n");

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
	}
}//end improv6 namespace




{//start improv8 namespace
	//////improv8/////////
	std::cout << "\n\n\n"; 
	std::cout << "running improv8 Test"; 

	std::cout << "MultiTree\n"; 
	for(int numCores = 1; numCores <= maxCores; numCores *= 2){	
		std::cout << "MultiTree, numCores=" << numCores << "\n"; 
	//	int treesPerBin = 2048/numCores;
		improv8 tester(forestFileName1,1,travs,128, 3);
		tester.printForest();
		printf("size of a node is %d\n",(int) sizeof(padNode));
		printf("starting run\n");

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
	}
}//end improv8 namespace


}//end Allstate test namespace



outfile.close();
return 0;
}
