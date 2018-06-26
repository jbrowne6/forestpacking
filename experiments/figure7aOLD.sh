#!/bin/bash
runTimes=2
numInBin=16
numTrees=2048
numBins=`expr $numTrees / $numInBin`
iDepth=3

cd ../

for dataset in "mnist" "higgs" "allstate"
do

	rm runTimes10.csv
	cp res/$dataset/forest.csv res/
	cp res/$dataset/testObservations.csv res/
	cp res/$dataset/traversal.csv res/

	# This gets run multiple times, which is hardcoded into packerWriteTime 75, which will be changed to 9.  Will also change the way 9 is run so the cores aren't hardcoded.

			./bin/packerWriteTime 9 1 $numBins $iDepth $j
	for j in 1 2 4 8 16 32 48
	do
		for i in `seq 1 $runTimes`;
		do
			./bin/packerWriteTime 10 
		done
	done

	mv runTimes10.csv results/figure7$dataset.csv
done



