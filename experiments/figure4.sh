#!/bin/bash
runTimes=1
binDepth=8
#bExp=4
numTrees=2048
numLevels=5

#log base2 function
#log(){ local x=$1 n=2 l=-1;if [ "$2" != "" ];then n=$x;x=$2;fi;while((x));do let l+=1 x/=n;done;echo $l; } 
#bExp=$(log $numTrees)
#mExp=`expr $bExp - $numLevels + 1`
cd ..

#cp res/higgs/forest.csv res/
#cp res/higgs/testObservations.csv res/
#cp res/higgs/traversal.csv res/
cp res/mnist/forest.csv res/
cp res/mnist/testObservations.csv res/
cp res/mnist/traversal.csv res/

#run once to load in cache
rm runTimes.csv
for i in `seq 1 $runTimes`;
do
    for q in 1 2 4 8 16 32 64 128
    do
        nbins=`expr $numTrees / $q`
        for j in `seq 0 $binDepth`;
        do
            echo -n "$q , $j , " >> runTimes.csv
            ./bin/packerWriteTime 6 1 $nbins $j
        done
    cp runTimes.csv results/figure4.csv
    done
done

mv runTimes.csv results/figure4.csv
