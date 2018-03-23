#!/bin/bash
runTimes=10
numInBin=16
numTrees=2048
numBins=`expr $numTrees / $numInBin`
iDepth=3

cd ../

for dataset in "mnist" "allstate" "higgs"
do

    rm runTimes.csv
    cp res/$dataset/forest.csv res/
    cp res/$dataset/testObservations.csv res/
    cp res/$dataset/traversal.csv res/

    for j in 0 1 2 4 6
    do
        for i in `seq 1 $runTimes`;
        do
            echo -n "$dataset , actual , " >> runTimes.csv
            if [ $j -lt 6 ]
            then
                ./bin/packerWriteTime $j 1
            else
                ./bin/packerWriteTime $j 1 $numBins $iDepth 
            fi
        done
    done
    mv runTimes.csv results/figure5$dataset.csv
done

