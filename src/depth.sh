#!/bin/bash
runTimes=10
numInBin=16
numTrees=2048
numBins=`expr $numTrees / $numInBin`
iDepth=3

cd ../
rm runTimes.csv

for dataset in "mnist" "allstate" "higgs"
do
	rm depth.csv
	cp res/$dataset/forest.csv res/
	cp res/$dataset/testObservations.csv res/
	cp res/$dataset/traversal.csv res/

	./bin/packerWriteTime 14 1 
		mv depth.csv depthtest/depth$dataset.csv

done
