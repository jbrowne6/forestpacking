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
#include "improv3.h"
#include "improv7.h"
#include "improv4.h"
#include "improv5.h"
#include "improv6.h"
#include "improv2.h"
#include "improv8.h"
#include "testDepth.h"
#include "naive.h"
#include <likwid.h>

inline bool doesExist(const std::string& name) {
  std::ifstream f(name.c_str());
  return f.good();
}

int main(int argc, char* argv[]) {
  LIKWID_MARKER_INIT;

  double percentRight =0;
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

      LIKWID_MARKER_START("naive");
		tester.makePredictionsMultiTree(observations,1);
      LIKWID_MARKER_STOP("naive");
		percentRight = observations.returnPercentRight();
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";
		
}//end naive test


{//start improv1 namespace
	//////improv1/////////
	std::cout << "running improv1 Test"; 
	improv1 tester(forestFileName2,1);

      LIKWID_MARKER_START("improv1");
tester.makePredictionsMultiTree(observations,1);
      LIKWID_MARKER_STOP("improv1");
		percentRight = observations.returnPercentRight();
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";

}//end improv1 namespace


{//start improv2 namespace
	//////improv2/////////
	std::cout << "running improv2 Test"; 
	improv2 tester(forestFileName2,1);

      LIKWID_MARKER_START("improv2");
	tester.makePredictionsMultiTree(observations,1);
      LIKWID_MARKER_STOP("improv2");
		percentRight = observations.returnPercentRight();
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";

}//end improv2 namespace


{//start improv4 namespace
	//////improv4/////////
	std::cout << "running improv4 Test"; 
	improv4 tester(forestFileName2,1,travs);

      LIKWID_MARKER_START("improv4");
tester.makePredictionsMultiTree(observations,1);
      LIKWID_MARKER_STOP("improv4");
		percentRight = observations.returnPercentRight();
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";

	}//end improv4 namespace


{//start improv6 namespace
	//////improv6/////////
	std::cout << "running improv6 Test"; 

			improv6 tester(forestFileName2,1,travs, 32, 3);
      LIKWID_MARKER_START("improv6");
			tester.makePredictionsMultiTree(observations,1);
      LIKWID_MARKER_STOP("improv6");
percentRight = observations.returnPercentRight();
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";

		}//end improv6 namespace




{//start improv8 namespace
	//////improv8/////////
	std::cout << "running improv8 Test"; 

			improv8 tester(forestFileName2,1,travs,32, 3);
      LIKWID_MARKER_START("improv8");
tester.makePredictionsMultiTree(observations,1);
      LIKWID_MARKER_STOP("improv8");
percentRight = observations.returnPercentRight();
					std::cout << "percentRight does not match: " << percentRight << " : " << observations.returnPercentRight() << "\n";

}	
}//end mnist test namespace

LIKWID_MARKER_CLOSE;
    return 0;

}
