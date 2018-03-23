#!/bin/bash
#!/bin/bash
runTimes=10
binDepth=7
#bExp=4
numTrees=2048
numLevels=5

for q in 1 2 4 8 16 32
do
    nbins=`expr $numTrees / $q`
    for j in `seq 0 $binDepth`;
    do
        for i in `seq 1 $runTimes`;
        do
            echo  "$q , $j , $nbins " 
        done
    done
done

