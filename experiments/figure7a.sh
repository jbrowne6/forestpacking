#!/bin/bash
runTimes=3
numInBin=16
numTrees=2048
numBins=`expr $numTrees / $numInBin`
iDepth=0

cd ../

for dataset in "mnist" "higgs" "allstate"
do

  rm runTimes75.csv
  cp res/$dataset/forest.csv res/
  cp res/$dataset/testObservations.csv res/
  cp res/$dataset/traversal.csv res/

# This gets run multiple times, which is hardcoded into packerWriteTime 75, which will be changed to 9.  Will also change the way 9 is run so the cores aren't hardcoded.
  ./bin/packerWriteTime 75 1 $numBins $iDepth $j

  mv runTimes75.csv results/figure7$dataset.csv
done



