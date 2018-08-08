#!/bin/bash
runTimes=1
binDepth=2
#bExp=4
numTrees=2048

cd ..
cp res/mnist/forest.csv res/
cp res/mnist/testObservations.csv res/
cp res/mnist/traversal.csv res/

#run once to load in cache
rm runTimes.csv

for i in `seq 1 $runTimes`;
do
#	for q in 1 4 8 12 16 20 24 32 64 128
for ((q=4; q<=128;q=q+4)) 
	do
		nbins=`expr $numTrees / $q`
		for j in `seq 0 $binDepth`;
		do
			echo -n "$q , $j , " >> runTimes.csv
			./bin/packerWriteTime 6 1 $nbins $j
		done
	done
	cp runTimes.csv results/figure4b.csv
done

mv runTimes.csv results/figure4b.csv
