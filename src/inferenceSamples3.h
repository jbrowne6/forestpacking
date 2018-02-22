
#ifndef inferenceSamples3_h
#define inferenceSamples3_h

#include <stdlib.h>
#include <iostream>
#include <fstream>

//TODO Each observation should be cache line aligned.
class inferenceSamples3
{
    public:
        int numObservations;
        int numFeatures;
        int* observationClasses = NULL;
        int* predictedClasses = NULL;
        double** samplesMatrix = NULL;

        void percentRight();

        inferenceSamples3(const std::string& testFile);
        ~inferenceSamples3();
};
#endif //inferenceSamples3_h
