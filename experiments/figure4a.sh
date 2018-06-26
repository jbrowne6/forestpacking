#!/bin/bash
runTimes=10
binDepth=6
#bExp=4
numTrees=2048

cd ..
cp res/higgs/forest.csv res/
cp res/higgs/testObservations.csv res/
cp res/higgs/traversal.csv res/

#run once to load in cache
rm runTimes.csv

for i in `seq 1 $runTimes`;
do
	for q in 1 8 16 32 64 128
	do
		nbins=`expr $numTrees / $q`
		for j in `seq 0 $binDepth`;
		do
			echo -n "$q , $j , " >> runTimes.csv
			./bin/packerWriteTime 6 1 $nbins $j
		done
	done
	cp runTimes.csv results/figure4a.csv
done

mv runTimes.csv results/figure4a.csv
