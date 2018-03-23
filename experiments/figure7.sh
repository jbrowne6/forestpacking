#!/bin/bash
runTimes=1
numInBin=16
numTrees=2048
numBins=`expr $numTrees / $numInBin`
iDepth=3

cd ../
rm runTimes.csv

for dataset in "mnist" "allstate" "higgs"
do
    cp res/$dataset/forest.csv res/
    cp res/$dataset/testObservations.csv res/
    cp res/$dataset/traversal.csv res/

    for j in 1 2 4 8 16 32 48
    do
        for i in `seq 1 $runTimes`;
        do
            echo -n "$dataset , $j , " >> runTimes.csv
                ./bin/packerWriteTime 8 1 $numBins $iDepth $j
        done
    done
done

mv runTimes.csv results/figure7.csv
