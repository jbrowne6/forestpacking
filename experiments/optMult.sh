#!/bin/bash
runTimes=10
binDepth=5
#bExp=4
numTrees=2048
numLevels=5


cd ..

cp res/higgs/forest.csv res/
cp res/higgs/testObservations.csv res/
cp res/higgs/traversal.csv res/
#run once to load in cache
./bin/packerWriteTime 6 1 32 3
rm runTimes.csv

for i in `seq 1 $runTimes`;
do
    for q in 16 32 64 128 256 512
    do
        nbins=`expr $numTrees / $q`
        for j in `seq 0 $binDepth`;
        do
            echo -n "$q , $j , " >> runTimes.csv
            ./bin/packerWriteTime 8 1 $nbins $j 32
        done
    done
    cp runTimes.csv results/optMult.csv
done

mv runTimes.csv results/optMult.csv
