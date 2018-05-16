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
	rm runTimes10.csv
	cp res/$dataset/forest.csv res/
	cp res/$dataset/testObservations.csv res/
	cp res/$dataset/traversal.csv res/

	./bin/packerWriteTime 9 1 $numBins $iDepth 64
	for j in 1 2 4 8 16 32
	do
		for i in `seq 1 $runTimes`;
		do
			#        echo -n "$dataset , $j , " >> runTimes.csv
			./bin/packerWriteTime 10 1 $numBins $iDepth $j
		done
	done
	mv runTimes10.csv results/figure7$dataset.csv
done

mv runTimes.csv results/figure7.csv
